//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************
Texture2D    _Tex : register(t0);
SamplerState gsamPointClamp  : register(s1);

struct VSInput{
	float3 position: POSITION; 
	float4 color: COLOR;
	float3 NormalL : NORMAL;
	float2 TexC    : TEXCOORD;
};

struct PSInput {
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 TexC    : TEXCOORD;
};
cbuffer _Global : register(b0){
	float4x4 _CameraWorldToViewMatrix;
};


PSInput VSMain(VSInput input) {
	PSInput result;

	result.position = mul(_CameraWorldToViewMatrix, float4(input.position, 1));
	result.TexC = input.TexC;
	result.color = input.color;
	return result;
}

float4 PSMain(PSInput input) : SV_TARGET {
	float4 diffuseAlbedo = _Tex.Sample(gsamPointClamp, input.TexC);
	//float4 diffuseAlbedo = input.color;
	return diffuseAlbedo;
}
