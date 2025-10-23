#pragma once

struct CB_PerFrame
{
	Matrix viewMatrix;
	Matrix projMatrix;
};

struct CB_PerObject
{
	Matrix worldMatrix;
};