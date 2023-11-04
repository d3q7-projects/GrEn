#pragma once

namespace GrEn
{
	typedef struct rgba
	{
		float r;
		float g;
		float b;
		float a;
	} rgba;
	
	typedef unsigned int hexColor;
	hexColor rgbaToHex(rgba color);

}