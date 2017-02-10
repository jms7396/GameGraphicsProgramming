
// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;
	float4 color		: COLOR;
	float3 normal		: NORMAL;
	float2 uv			: TEXCOORD;
};

struct DirectionalLight {
	float4 AmbientColor;
	float4 DiffuseColor;
	float3 Direction;
};

cbuffer dirLight : register(b0)
{
	DirectionalLight light;
	DirectionalLight light2;
};

// Texture Related Data
Texture2D Rocks			: register(t0);
Texture2D Wood			: register(t1);
SamplerState Sampler	: register(s0);

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	// Normalize our input normal
	input.normal = normalize(input.normal);
	
	// Calculating our First Light
	float3 dirToLight = -(light.Direction);
	float dirLightAmount = saturate(dot(input.normal, dirToLight));
	float4 light1Color = ((light.DiffuseColor * dirLightAmount) + light.AmbientColor);

	// Calculating our Second Light
	float3 dirToLight2 = -(light2.Direction);
	float dirLight2Amount = saturate(dot(input.normal, dirToLight2));
	float4 light2Color = ((light2.DiffuseColor * dirLight2Amount) + light2.AmbientColor);

	float4 rockColor = Rocks.Sample(Sampler, input.uv);
	float4 woodColor = Wood.Sample(Sampler, input.uv);


	float4 finalColor = (light1Color*woodColor) + (light2Color*woodColor);

	return finalColor;


	// Just return the input color
	// - This color (like most values passing through the rasterizer) is 
	//   interpolated for each pixel between the corresponding vertices 
	//   of the triangle we're rendering
	return float4(0, 1, 0, 1);
}