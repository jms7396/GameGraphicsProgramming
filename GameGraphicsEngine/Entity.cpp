#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

Entity::Entity(Mesh * entityMesh, Material * entityMat)
{
	mesh = entityMesh;
	mat = entityMat;
	position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void Entity::SetPosition(DirectX::XMFLOAT3 pos)
{
	position = pos;
}

void Entity::SetRotation(DirectX::XMFLOAT3 rot)
{
	rotation = rot;
}

void Entity::SetScale(DirectX::XMFLOAT3 scal)
{
	scale = scal;
}

DirectX::XMFLOAT3 Entity::GetPosition()
{
	return position;
}

DirectX::XMFLOAT3 Entity::GetRotation()
{
	return rotation;
}

DirectX::XMFLOAT3 Entity::GetScale()
{
	return scale;
}

DirectX::XMFLOAT4X4 Entity::GetWorldMatrix()
{
	return worldMatrix;
}

Mesh * Entity::GetMesh()
{
	return mesh;
}

void Entity::FinalizeMatrix()
{
	DirectX::XMMATRIX trans = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	DirectX::XMMATRIX rotX = DirectX::XMMatrixRotationX(rotation.x);
	DirectX::XMMATRIX rotY = DirectX::XMMatrixRotationY(rotation.y);
	DirectX::XMMATRIX rotZ = DirectX::XMMatrixRotationZ(rotation.z);
	DirectX::XMMATRIX sc = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	DirectX::XMMATRIX world = sc * rotZ * rotY * rotX * trans;
	DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixTranspose(world));
}

void Entity::Move()
{
}

void Entity::PrepareMaterial(DirectX::XMFLOAT4X4 viewMat, DirectX::XMFLOAT4X4 projMat)
{
	// Send data to shader variables
	//  - This is actually a complex process of copying data to a local buffer
	//    and then copying that entire buffer to the GPU.  
	//  - The "SimpleShader" class handles all of that for you.
	mat->GetVertexShader()->SetMatrix4x4("world", worldMatrix);
	mat->GetVertexShader()->SetMatrix4x4("view", viewMat);
	mat->GetVertexShader()->SetMatrix4x4("projection", projMat);

	// Once you've set all of the data you care to change for
	// the next draw call, you need to actually send it to the GPU
	//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	mat->GetVertexShader()->CopyAllBufferData();
	mat->GetPixelShader()->CopyAllBufferData();

	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	mat->GetVertexShader()->SetShader();
	mat->GetPixelShader()->SetShader();
}
