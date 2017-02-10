#pragma once
#include <DirectXMath.h>;

struct DirectionalLight {
	DirectX::XMFLOAT4 AmbietColor;
	DirectX::XMFLOAT4 DiffuseColor;
	DirectX::XMFLOAT3 Direction;
};