#pragma once
#include "..\..\tkEngine\math\tkvector.h"

namespace tkEngine {
	static const inline CVector2 operator-(const CVector2& v0, const CVector2& v1) {
		CVector2 v;
		v.x = v0.x - v1.x;
		v.y = v0.y - v1.y;
		return v;
	}

	static const inline CVector2 operator+(const CVector2& v0, const CVector2& v1) {
		CVector2 vec;
		vec.x = v0.x + v1.x;
		vec.y = v0.y + v1.y;
		return vec;
	}

	static const inline CVector2 operator/(const CVector2& v, const float& div) {
		CVector2 vec = v;
		vec.x /= div;
		vec.y /= div;
		return vec;
	}
}