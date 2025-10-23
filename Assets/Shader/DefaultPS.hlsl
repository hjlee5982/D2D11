#include "CBuffer.hlsli"
#include "Struct.hlsli"

float4 main(PS_IN input) : SV_TARGET
{
    float4 color = gTexture_0.Sample(gLinearSampler, input.uv);
    
    //return float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    return color;
}