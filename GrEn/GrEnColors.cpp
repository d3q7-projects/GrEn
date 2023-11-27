#include "GrEnColors.h"

#define SRGB_MAX 255

GrEn::hexColor GrEn::rgbaToHex(const GrEn::rgba& color) {
	return GrEn::hexColor(static_cast<unsigned char>(color.a * SRGB_MAX),
		static_cast<unsigned char>(color.r * SRGB_MAX),
		static_cast<unsigned char>(color.g * SRGB_MAX),
		static_cast<unsigned char>(color.b * SRGB_MAX));
}

// TODO: (priority: 1) upgrade to SIMD operations?
GrEn::rgba GrEn::aOverBrgba(const GrEn::rgba& a, const GrEn::rgba& b)
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

GrEn::hexColor GrEn::aOverBhex(const hexColor& a, const hexColor& b)
{
	//using the formula from the following wikipedia page:
	// https://en.wikipedia.org/wiki/Alpha_compositing#Description

	if (a.ch.a == SRGB_MAX) {
		return a;
	}
	else if (a.ch.a == 0)
	{
		return b;
	}
	else if (b.ch.a == SRGB_MAX) {
		//Simplifies to:	A_o = 1
		//					C_o = C_a*A_a + C_b*(1-A_a)
		//thanks to https://www.codeguru.com/cplusplus/tip-an-optimized-formula-for-alpha-blending-pixels/
		//We can optimize it further to(we muust make sure we dont have an overflow):
		//					C_o = ((C_a*A_a) + (C_b*(255-A_a))) >> 8
		return {
					static_cast<GrEn::byte>(((static_cast<unsigned int>(a.ch.r) * a.ch.a) + (static_cast<unsigned int>(b.ch.r) * (SRGB_MAX - a.ch.a))) >> 8),
					static_cast<GrEn::byte>(((static_cast<unsigned int>(a.ch.g) * a.ch.a) + (static_cast<unsigned int>(b.ch.g) * (SRGB_MAX - a.ch.a))) >> 8),
					static_cast<GrEn::byte>(((static_cast<unsigned int>(a.ch.b) * a.ch.a) + (static_cast<unsigned int>(b.ch.b) * (SRGB_MAX - a.ch.a))) >> 8),
					SRGB_MAX ,
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
		//We must use	:	A_o = A_a + A_b*(SRGB_MAX -A_a)
		//					C_o = (C_a*A_a + C_b*A_b*(SRGB_MAX -A_a))/(A_a + A_b*(SRGB_MAX -A_a))
		const GrEn::byte alpha = (b.ch.a * (SRGB_MAX  - a.ch.a) >> 8) + a.ch.a; //using previous optimizations

		return {
			static_cast<GrEn::byte>((a.ch.r * a.ch.a >> 8) + (b.ch.r * (b.ch.a) * (SRGB_MAX - a.ch.a) >> 16)),
			static_cast<GrEn::byte>((a.ch.g * a.ch.a >> 8) + (b.ch.g * (b.ch.a) * (SRGB_MAX - a.ch.a) >> 16)),
			static_cast<GrEn::byte>((a.ch.b * a.ch.a >> 8) + (b.ch.b * (b.ch.a) * (SRGB_MAX - a.ch.a) >> 16)),
			static_cast<GrEn::byte>(alpha),
		};
	}
}

void GrEn::rgbaToHex(const rgba& color, hexColor& res)
{
	res.ch.a = static_cast<unsigned char>(color.a * SRGB_MAX),
	res.ch.r = static_cast<unsigned char>(color.r * SRGB_MAX),
	res.ch.g = static_cast<unsigned char>(color.g * SRGB_MAX),
	res.ch.b = static_cast<unsigned char>(color.b * SRGB_MAX);
}

void GrEn::aOverBrgba(const rgba& a, const rgba& b, rgba& res)
{
	//using the formula from the following wikipedia page:
	// https://en.wikipedia.org/wiki/Alpha_compositing#Description

	if (a.a == 1.0f) {
		res = a;
	}
	else if (a.a == 0.0f)
	{
		res = b;
	}
	else if (b.a == 1.0f) {
		//Simplifies to:	A_o = 1
		//					C_o = C_a*A_a + C_b*(1-A_a)
		res = { a.r * a.a + b.r * (1 - a.a),a.g * a.a + b.g * (1 - a.a),a.b * a.a + b.b * (1 - a.a),1 };
	}
	res = { a.r * a.a + b.r * b.a * (1 - a.a),a.g * a.a + b.g * b.a * (1 - a.a),a.b * a.a + b.b * b.a * (1 - a.a), a.a + b.a * (1 - a.a) };
	res.r /= res.a; res.g /= res.a; res.b /= res.a;
}

void GrEn::aOverBhex(const hexColor& a, const hexColor& b, hexColor& res)
{
	//using the formula from the following wikipedia page:
	// https://en.wikipedia.org/wiki/Alpha_compositing#Description

	if (a.ch.a == SRGB_MAX) {
		res = a;
	}
	else if (a.ch.a == 0)
	{
		res = b;
	}
	else if (b.ch.a == SRGB_MAX) {
		//Simplifies to:	A_o = 1
		//					C_o = C_a*A_a + C_b*(1-A_a)
		//thanks to https://www.codeguru.com/cplusplus/tip-an-optimized-formula-for-alpha-blending-pixels/
		//We can optimize it further to(we muust make sure we dont have an overflow):
		//					C_o = ((C_a*A_a) + (C_b*(255-A_a))) >> 8
		res.ch.r = static_cast<GrEn::byte>(((static_cast<unsigned int>(a.ch.r) * a.ch.a) + (static_cast<unsigned int>(b.ch.r) * (SRGB_MAX - a.ch.a))) >> 8);
		res.ch.g = static_cast<GrEn::byte>(((static_cast<unsigned int>(a.ch.g) * a.ch.a) + (static_cast<unsigned int>(b.ch.g) * (SRGB_MAX - a.ch.a))) >> 8);
		res.ch.b = static_cast<GrEn::byte>(((static_cast<unsigned int>(a.ch.b) * a.ch.a) + (static_cast<unsigned int>(b.ch.b) * (SRGB_MAX - a.ch.a))) >> 8);
		res.ch.a = SRGB_MAX;

	}
	else if (b.ch.a == 0)
	{
		//Simplifies to:	A_o = A_a
		//					C_o = (C_a*A_a)
		res.ch.r = static_cast<GrEn::byte>(a.ch.r * a.ch.a >> 8);
		res.ch.g = static_cast<GrEn::byte>(a.ch.g * a.ch.a >> 8);
		res.ch.b = static_cast<GrEn::byte>(a.ch.b * a.ch.a >> 8);
		res.ch.a = a.ch.a;
	}
	else
	{
		//We must use	:	A_o = A_a + A_b*(SRGB_MAX -A_a)
		//					C_o = (C_a*A_a + C_b*A_b*(SRGB_MAX -A_a))/(A_a + A_b*(SRGB_MAX -A_a))
		const GrEn::byte alpha = (b.ch.a * (SRGB_MAX - a.ch.a) >> 8) + a.ch.a; //using previous optimizations

		res.ch.r = static_cast<GrEn::byte>((a.ch.r * a.ch.a >> 8) + (b.ch.r * (b.ch.a) * (SRGB_MAX - a.ch.a) >> 16));
		res.ch.g = static_cast<GrEn::byte>((a.ch.g * a.ch.a >> 8) + (b.ch.g * (b.ch.a) * (SRGB_MAX - a.ch.a) >> 16));
		res.ch.b = static_cast<GrEn::byte>((a.ch.b * a.ch.a >> 8) + (b.ch.b * (b.ch.a) * (SRGB_MAX - a.ch.a) >> 16));
		res.ch.a = static_cast<GrEn::byte>(alpha);
	}
}
