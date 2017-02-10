#pragma once

#include <DirectXMath.h>;
#include "Mesh.h";
#include "Material.h"

class Entity
{
public:
	Entity();
	~Entity();

	Entity(Mesh* entityMesh, Material* entityMat);
	void SetPosition(DirectX::XMFLOAT3 pos);
	void SetRotation(DirectX::XMFLOAT3 rot);
	void SetScale(DirectX::XMFLOAT3 scal);

	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();
	DirectX::XMFLOAT4X4 GetWorldMatrix();
	Mesh* GetMesh();

	void FinalizeMatrix();
	void Move();
	void PrepareMaterial(DirectX::XMFLOAT4X4 viewMat, DirectX::XMFLOAT4X4 projMat);


private:
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	Mesh* mesh;
	Material* mat;
};

