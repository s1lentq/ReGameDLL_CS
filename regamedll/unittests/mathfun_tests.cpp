#include "precompiled.h"
#include "cppunitlite/TestHarness.h"

__declspec(naked) double _sin_x87(double angle) {
	__asm {
		fld qword ptr[esp+4]
		fsin
		ret
	}
}

__declspec(naked) double _cos_x87(double angle) {
	__asm {
		fld qword ptr[esp + 4]
		fcos
		ret
	}
}

TEST(SinCosPrecision, SseMathFun, 10000)
{
	char localbuf[256];

	for (double i = 0.0; i < 2 * M_PI; i += (M_PI / 10000.0)) {
		double x87_sin = _sin_x87(i);
		double x87_cos = _cos_x87(i);

		__m128 s, c, d;
		d = _mm_set1_ps((float)i);
		sincos_ps(d, &s, &c);

		double sse_sin = _mm_cvtss_f32(s);
		double sse_cos = _mm_cvtss_f32(c);

		Q_snprintf(localbuf, sizeof(localbuf), "sin precision failure for angle=%f", i);
		DOUBLES_EQUAL(localbuf, x87_sin, sse_sin, 0.000001);

		Q_snprintf(localbuf, sizeof(localbuf), "cos precision failure for angle=%f", i);
		DOUBLES_EQUAL(localbuf, x87_cos, sse_cos, 0.000001);
	}
}

/*
TEST(SinCosPerformance, SseMathFun, 400000)
{
	DWORD x87_start = GetTickCount();
	for (int i = 0; i < 100000000; i++) {
		double res =_sin_x87(0.0);
		DOUBLES_EQUAL("check", res, 0.0, 0.000001);
	}

	DWORD sse_start = GetTickCount();

	__m128 s, c, d;
	for (int i = 0; i < 100000000; i++) {
		d = _mm_set1_ps(0.0f);
		sincos_ps(d, &s, &c);

		double res = _mm_cvtss_f32(s);
		DOUBLES_EQUAL("check", res, 0.0, 0.000001);
	}

	DWORD sse_end = GetTickCount();

	printf("Time consumed: x87: %u ; sse: %u", sse_start - x87_start, sse_end - sse_start);

}
*/
