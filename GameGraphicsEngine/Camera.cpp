#include "Camera.h"



Camera::Camera()
{
	position = XMVectorSet(0, 0, -5, 0);
	direction = XMVectorSet(0, 0, 1, 0);
	rotX = 0.0f;
	rotY = 0.0f;
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX V = XMMatrixLookToLH(
		position,     // The position of the camera
		direction,     // Direction the camera is looking
		up);
	XMStoreFloat4x4(&viewMat, XMMatrixTranspose(V)); // Transpose for HLSL!
}


Camera::~Camera()
{
}

DirectX::XMFLOAT4X4 Camera::GetViewMat()
{
	return viewMat;
}

DirectX::XMFLOAT4X4 Camera::GetProjectionMat()
{
	return projectionMat;
}

void Camera::RotateCamera(float changeInX, float changeInY)
{
	rotX += changeInX*0.001;
	rotY += changeInY*0.001;
}

void Camera::Update(float deltaTime)
{
	DirectX::XMVECTOR upVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR rotation = DirectX::XMQuaternionRotationRollPitchYaw(rotY, rotX, 0.0f);
	direction = DirectX::XMVector3Rotate(direction, rotation);

	DirectX::XMVECTOR moveVector = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	if (GetAsyncKeyState('W') & 0x8000) { moveVector = DirectX::XMVectorAdd(moveVector, direction); }
	if (GetAsyncKeyState('S') & 0x8000) { moveVector = DirectX::XMVectorAdd(moveVector, (-1.0f * direction)); };
	if (GetAsyncKeyState('A') & 0x8000) { moveVector = DirectX::XMVectorAdd(moveVector, DirectX::XMVector3Cross(direction, upVector)); };
	if (GetAsyncKeyState('D') & 0x8000) { moveVector = DirectX::XMVectorAdd(moveVector, -1.0 * DirectX::XMVector3Cross(direction, upVector)); };
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { moveVector = DirectX::XMVectorAdd(moveVector, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)); };
	if (GetAsyncKeyState('X') & 0x8000) { moveVector = DirectX::XMVectorAdd(moveVector, DirectX::XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f)); };

	position = XMVectorAdd(moveVector * deltaTime, position);

	XMStoreFloat4x4(&viewMat, XMMatrixTranspose(DirectX::XMMatrixLookToLH(position, direction, upVector)));
	rotX = 0.0f;
	rotY = 0.0f;
}

void Camera::SetProjectionMat(float width, float height)
{
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projectionMat, XMMatrixTranspose(P)); // Transpose for HLSL!
}
