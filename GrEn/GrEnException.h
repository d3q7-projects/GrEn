#pragma once
#define CHECK(e) if (e) { std::cout << GrEn::translateExcep(e) << std::endl;}
#define CHECKFUNC(e, func) if (e = func) { std::cout << GrEn::translateExcep(e) << std::endl;}


namespace GrEn
{
	typedef int exception;

	const char* translateExcep(const exception);
}