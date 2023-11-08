#include "GrEnDefinitions.h"
#define SRGB_MAX 255

GrEn::hexColor GrEn::rgbaToHex(GrEn::rgba color){
	return GrEn::hexColor(static_cast<unsigned char>(color.a * SRGB_MAX),
		static_cast<unsigned char>(color.r * SRGB_MAX),
		static_cast<unsigned char>(color.g * SRGB_MAX),
		static_cast<unsigned char>(color.b * SRGB_MAX));
}

GrEn::rgba GrEn::aOverBrgba(rgba a, rgba b)
{
	//USE the formula from the following wikipedia page:
	// https://en.wikipedia.org/wiki/Alpha_compositing#Description
	// TODO: upgrade to SIMD operations?

	if (a.a == 1.0f) {
		return a;
	}
	else if (a.a == 0.0f)
	{
		return b;
	}
	else if (a.b == 1.0f) {
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
	//USE the formula from the following wikipedia page:
	// https://en.wikipedia.org/wiki/Alpha_compositing#Description
	// TODO: upgrade to SIMD operations?
	return a;
	//if (a.a == 1.0f) {
	//	return a;
	//}
	//else if (a.a == 0.0f)
	//{
	//	return b;
	//}
	//else if (a.b == 1.0f) {
	//	//Simplifies to:	A_o = 1
	//	//					C_o = C_a*A_a + C_b*(1-A_a)
	//	return { a.r * a.a + b.r * (1 - a.a),a.g * a.a + b.g * (1 - a.a),a.b * a.a + b.b * (1 - a.a),1 };
	//}
	//GrEn::rgba c = { a.r * a.a + b.r * b.a * (1 - a.a),a.g * a.a + b.g * b.a * (1 - a.a),a.b * a.a + b.b * b.a * (1 - a.a), a.a + b.a * (1 - a.a) };
	//c.r /= c.a; c.g /= c.a; c.b /= c.a;
	//return c;
}
