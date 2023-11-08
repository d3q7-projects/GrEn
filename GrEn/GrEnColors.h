#pragma once

namespace GrEn
{
	typedef unsigned char byte;

	typedef struct rgba
	{
		float r;
		float g;
		float b;
		float a;
	} rgba;

	union hexColor
	{
		struct //notice that its flipped!
		{
			byte b;
			byte g;
			byte r;
			byte a;
		} ch;
		unsigned int value;
		hexColor(unsigned int v) : value(v) {}
		hexColor(byte r, byte g, byte b, byte a) : ch({b, g, r, a}) {}
	};
	hexColor rgbaToHex(rgba color);
	rgba aOverBrgba(rgba a, rgba b);
	hexColor aOverBhex(hexColor a, hexColor b);

};

