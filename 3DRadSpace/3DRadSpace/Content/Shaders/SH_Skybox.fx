/*
    A modified version of rbwhitaker's tutorial shaders.
    This shader is orignially used for the skybox cube model. 
    For some reason there are issues when drawing the model.

    Is seems fine to me, and I'll try to explain every line.

    For anyone that reads this, fixing the skybox shader would be a great contribution to this engine. - NicusorN5
*/
/*
SamplerState ss = new SamplerState() { AddressU = TextureAddressMode.Border, AddressV = TextureAddressMode.Border };
// plus any other states you want set  AddressW usually wont matter but you can also set that too.

Then after spritebatch begins(...);
GraphicsDevice.SamplerStates[index] = ss;
*/
//Platform specific #defines. C++ circular depedency traumas there we go
#if OPENGL
#define SV_POSITION POSITION
#define VS_SHADERMODEL vs_3_0
#define PS_SHADERMODEL ps_3_0
#else
#define VS_SHADERMODEL vs_4_0_level_9_1
#define PS_SHADERMODEL ps_4_0_level_9_1
#endif

float4x4 World; // world matrix.
float4x4 View; // viwe patrix
float4x4 Projection; //projection

texture ModelTexture; //texture parameter
//I don't really know what's the think above supposed to do.
sampler2D textureSampler = sampler_state {
    Texture = (ModelTexture);
    MinFilter = Linear;
    MagFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;
};

struct VertexShaderInput
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float2 TextureCoordinate : TEXCOORD0;
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;
    float3 Normal : NORMAL0;
    float2 TextureCoordinate : TEXCOORD0;
};

VertexShaderOutput VertexShaderFunction(VertexShaderInput input)
{
    VertexShaderOutput output;

    float4 worldPosition = mul(input.Position, World);
    float4 viewPosition = mul(worldPosition, View);
    output.Position = mul(viewPosition, Projection);
    output.Normal = input.Normal;
    output.TextureCoordinate = input.TextureCoordinate;
    return output;
}

float4 PixelShaderFunction(VertexShaderOutput input) : COLOR0
{
    float4 textureColor = tex2D(textureSampler, input.TextureCoordinate);
    textureColor.a = 1;
    return textureColor;
}

technique Textured
{
    pass Pass1
    {
        VertexShader = compile VS_SHADERMODEL VertexShaderFunction();
        PixelShader = compile PS_SHADERMODEL PixelShaderFunction();
    }
}