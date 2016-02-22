#include "precompiled.h"
#include "cppunitlite/TestHarness.h"

// Undefined to class #define vec3_t Vector
#pragma push_macro("vec3_t")
#undef vec3_t

extern void AngleQuaternion(vec_t *angles, vec_t *quaternion);

TEST(AngleQuaternion, AnimationFuncs, 10000) {
	struct testdata_t {
		vec3_t angles;
		vec4_t quaternion;
	};

	testdata_t testdata[2] = {
			{ { 21.0f, 65.0f, 162.0f }, { -0.88286f, 0.13638f, -0.33691f, 0.29740f } },
			{ { 106.0f, 142.0f, 62.0f }, { 0.65693f, -0.21134f, -0.61609f, 0.37976f } }
	};

	for (int i = 0; i < ARRAYSIZE(testdata); i++) {
		vec3_t a = { testdata[i].angles[0] * 2.0 / M_PI, testdata[i].angles[1] * 2.0 / M_PI, testdata[i].angles[2] * 2.0 / M_PI, };
		vec4_t q;
		AngleQuaternion(a, q);

		DOUBLES_EQUAL("q[0] mismatch", testdata[i].quaternion[0], q[0], 0.00001);
		DOUBLES_EQUAL("q[1] mismatch", testdata[i].quaternion[1], q[1], 0.00001);
		DOUBLES_EQUAL("q[2] mismatch", testdata[i].quaternion[2], q[2], 0.00001);
		DOUBLES_EQUAL("q[3] mismatch", testdata[i].quaternion[2], q[2], 0.00001);
	}
}

#pragma pop_macro("vec3_t")
