#pragma once
#include "..\..\tkEngine\math\tkvector.h"

namespace tkEngine {
	static inline CVector2 operator-(const CVector2& v0, const CVector2& v1) {
		CVector2 v;
		v.x = v0.x - v1.x;
		v.y = v0.y - v1.y;
		return v;
	}

	static inline CVector2 operator+(const CVector2& v0, const CVector2& v1) {
		CVector2 vec;
		vec.x = v0.x + v1.x;
		vec.y = v0.y + v1.y;
		return vec;
	}

	static inline CVector2 operator/(const CVector2& v, const float& div) {
		CVector2 vec = v;
		vec.x /= div;
		vec.y /= div;
		return vec;
	}

	static inline float vec2Dot(const CVector2& v1, const CVector2& v2) {
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	static inline float vec2Cross(const CVector2& v1, const CVector2& v2) {
		return (v1.x * v2.y) - (v2.x * v1.y);
	}

	static inline float vec2Length(const CVector2& v) {
		return sqrt(v.x*v.x + v.y*v.y);
	}
}