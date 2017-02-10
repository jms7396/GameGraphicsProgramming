#include "Material.h"



Material::Material(SimplePixelShader* pixShad, SimpleVertexShader* verShad, ID3D11ShaderResourceView* view, ID3D11SamplerState* sampler)
{
	pixelShader = pixShad;
	vertexShader = verShad;
	SetShaderResourceView(view);
	SetSamplerState(sampler);
}

Material::Material()
{
}


Material::~Material()
{
}

SimplePixelShader * Material::GetPixelShader()
{
	return pixelShader;
}

SimpleVertexShader * Material::GetVertexShader()
{
	return vertexShader;
}

ID3D11ShaderResourceView * Material::GetShaderResourceView()
{
	return shaderResourceView;
}

ID3D11SamplerState * Material::GetSamplerState()
{
	return samplerState;
}

void Material::SetShaderResourceView(ID3D11ShaderResourceView * view)
{
	shaderResourceView = view;
}

void Material::SetSamplerState(ID3D11SamplerState * state)
{
	samplerState = state;
}
