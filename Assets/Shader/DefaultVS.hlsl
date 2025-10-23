#include "CBuffer.hlsli"
#include "struct.hlsli"

PS_IN main(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    
    float4 position = float4(input.position, 1.f);
    
    position = mul(position, WorldMatrix);
    position = mul(position, ViewMatrix);
    position = mul(position, ProjMatrix);
    
    output.position = position;
    output.uv       = input.uv;

    return output;
}