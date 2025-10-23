#ifndef __STRUCT__
#define __STRUCT__

struct VS_IN
{
    float3 position : POSITION;
    float2 uv       : TEXCOORD0;
};

struct PS_IN
{
    float4 position : SV_Position;
    float2 uv       : TEXCOORD0;
};

#endif