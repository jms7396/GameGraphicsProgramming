#pragma once
#include "SimpleShader.h"
class Material
{
public:
	Material(SimplePixelShader* pixShad, SimpleVertexShader* verShad, ID3D11ShaderResourceView* view, ID3D11SamplerState* sampler);
	Material();
	~Material();

	SimplePixelShader* GetPixelShader();
	SimpleVertexShader* GetVertexShader();
	ID3D11ShaderResourceView* GetShaderResourceView();
	ID3D11SamplerState* GetSamplerState();
	void SetShaderResourceView(ID3D11ShaderResourceView*);
	void SetSamplerState(ID3D11SamplerState*);
	

private:
	SimplePixelShader* pixelShader;
	SimpleVertexShader* vertexShader;
	ID3D11ShaderResourceView* shaderResourceView;
	ID3D11SamplerState* samplerState;
};

