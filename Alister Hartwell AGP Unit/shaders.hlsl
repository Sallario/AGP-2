Texture2D texture0;
SamplerState sampler0;

cbuffer CBuffer0
{
	matrix WorldViewProjection; // 64 bytes (4 x 4 = 16 floats * 4 bytes)
	float red_fraction; // 4 bytes
	float scale;		// 4 bytes 
	float4 directional_light_vector; //16 Bytes
	float4 directional_light_colour; //16 Bytes
	float4 ambient_light_colour; //16 Bytes
	float2 packing;		// 2x4 bytes = 8 bytes
} // Total Size = 128 bytes


struct VOut
{
	float4 position : SV_POSITION;
	float4 color	: COLOR;
	float2 texcoord : TEXCOORD;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR, float2 texcoord: TEXCOORD, float3 normal : NORMAL)
{
	VOut output;

	output.position = mul(WorldViewProjection, position);
	
	float diffuse_amount = dot(directional_light_vector, normal);

	diffuse_amount = saturate(diffuse_amount);

	output.color = ambient_light_colour + (directional_light_colour * diffuse_amount);
	
	output.texcoord = texcoord;

	//color.r *= red_fraction;
	//output.position = position;
	/*output.position.x *= scale;
	output.position.y *= scale;*/
	return output;
}

float4 PShader(float4 position: SV_POSITION, float4 color: COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	return color * texture0.Sample(sampler0, texcoord);
}