#include "GrEnDefinitions.h"
#define SRGB_MAX 255

GrEn::hexColor GrEn::rgbaToHex(GrEn::rgba color){
	return GrEn::hexColor(static_cast<unsigned char>(color.a * SRGB_MAX),
		static_cast<unsigned char>(color.r * SRGB_MAX),
		static_cast<unsigned char>(color.g * SRGB_MAX),
		static_cast<unsigned char>(color.b * SRGB_MAX));
}

// TODO: (priority: 1) upgrade to SIMD operations?
GrEn::rgba GrEn::aOverBrgba(rgba a, rgba b)
{
	//using the formula from the following wikipedia page:
	// https://en.wikipedia.org/wiki/Alpha_compositing#Description

	if (a.a == 1.0f) {
		return a;
	}
	else if (a.a == 0.0f)
	{
		return b;
	}
	else if (b.a == 1.0f) {
		//Simplifies to:	A_o = 1
		//					C_o = C_a*A_a + C_b*(1-A_a)
		return { a.r * a.a + b.r * (1 - a.a),a.g * a.a + b.g * (1 - a.a),a.b * a.a + b.b * (1 - a.a),1 };
	}
	GrEn::rgba c = { a.r * a.a + b.r * b.a * (1 - a.a),a.g * a.a + b.g * b.a * (1 - a.a),a.b * a.a + b.b * b.a * (1 - a.a), a.a + b.a * (1 - a.a) };
	c.r /= c.a; c.g /= c.a; c.b /= c.a;
	return c;
}

GrEn::hexColor GrEn::aOverBhex(hexColor a, hexColor b)
{
	//using the formula from the following wikipedia page:
	// https://en.wikipedia.org/wiki/Alpha_compositing#Description

	if (a.ch.a == 255) {
		return a;
	}
	else if (a.ch.a == 0)
	{
		return b;
	}
	else if (b.ch.a == 255) {
		//Simplifies to:	A_o = 1
		//					C_o = C_a*A_a + C_b*(1-A_a)
		//thanks to https://www.codeguru.com/cplusplus/tip-an-optimized-formula-for-alpha-blending-pixels/
		//We can optimize it further to(we muust make sure we dont have an overflow):
		//					C_o = ((C_a*A_a) + (C_b*(255-A_a))) >> 8
		return {
					((static_cast<unsigned int>(a.ch.r) * a.ch.a) + (static_cast<unsigned int>(b.ch.r) * (255 - a.ch.a))) >> 8,
					((static_cast<unsigned int>(a.ch.g) * a.ch.a) + (static_cast<unsigned int>(b.ch.g) * (255 - a.ch.a))) >> 8,
					((static_cast<unsigned int>(a.ch.b) * a.ch.a) + (static_cast<unsigned int>(b.ch.b) * (255 - a.ch.a))) >> 8,
					255,
		};

	}
	else if (b.ch.a == 0)
	{
		//Simplifies to:	A_o = A_a
		//					C_o = (C_a*A_a)
		return {
			static_cast<GrEn::byte>(a.ch.r * a.ch.a >> 8),
			static_cast<GrEn::byte>(a.ch.g * a.ch.a >> 8),
			static_cast<GrEn::byte>(a.ch.b * a.ch.a >> 8),
			static_cast<GrEn::byte>(a.ch.a),
		};
	}
	else
	{
		//We must use	:	A_o = A_a + A_b*(255-A_a)
		//					C_o = (C_a*A_a + C_b*A_b*(255-A_a))/(A_a + A_b*(255-A_a))
		const float alpha = (b.ch.a * (255 - a.ch.a) >> 8) + a.ch.a; //using previous optimizations
		return {
					//TODO: (priority: 5) optimize the division here(we can make it to 1 division and one shift)
					static_cast<GrEn::byte>((a.ch.r * a.ch.a) / 255.0f + b.ch.r * (b.ch.a) * (255 - a.ch.a) / 255.0f / 255.0f),
					static_cast<GrEn::byte>((a.ch.g * a.ch.a) / 255.0f + b.ch.g * (b.ch.a) * (255 - a.ch.a) / 255.0f / 255.0f),
					static_cast<GrEn::byte>((a.ch.b * a.ch.a) / 255.0f + b.ch.b * (b.ch.a) * (255 - a.ch.a) / 255.0f / 255.0f),
					static_cast<GrEn::byte>(alpha),
		};
	}
}
