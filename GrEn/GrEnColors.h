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
		hexColor(const unsigned int& v) : value(v) {}
		hexColor(const byte& r, const byte& g, const byte& b, const byte& a) : ch({b, g, r, a}) {}
	};
	
	hexColor rgbaToHex(const rgba& color);
	rgba aOverBrgba(const rgba& a, const rgba& b);
	hexColor aOverBhex(const hexColor& a, const hexColor& b);
	void rgbaToHex(const rgba& color, hexColor& res);
	void aOverBrgba(const rgba& a, const rgba& b, rgba& res);
	void aOverBhex(const hexColor& a, const hexColor& b, hexColor& res);

};

