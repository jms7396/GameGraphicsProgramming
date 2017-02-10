#pragma once
#include <d3d11.h>
#include "Vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	Mesh(Vertex*, int, unsigned*, int, ID3D11Device*);
	Mesh(char*, ID3D11Device*);
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int indicesAmount;
	void GenerateBuffers(Vertex*, int, unsigned*, int, ID3D11Device*);
};

