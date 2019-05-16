#pragma once

enum HitType {
	NonHit,
	Center,
	Side
};

struct HitResult {
	HitType hit = NonHit;
	int rotSign = 0;
};

class BoxCollider2D {
public:
	void Init(const CVector3 & pos, const CVector2& localCenter, CVector2 size);

	HitResult hitTest(const CVector3& pos, float radius);

	void Rotate(CQuaternion rot);

	void Move(CVector3 move);

private:
	CVector2 vertex[4];
	CVector2 shaft = { 1, 0 }; // ‰ñ“]‚·‚é‚Æ‚«‚Ì–_
	CVector2 m_pos;

	CVector2 sideVec[4];
};