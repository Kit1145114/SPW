#pragma once
#include "..\..\tkEngine\physics\tkPhysicsDynamicObject.h"

enum HitType {
	NonHit,
	Center,
	Side
};

struct HitResult {
	HitType hit = NonHit;
	int rotSign = 0;
};

class BoxCollider2D{
public:
	void Init(const CVector3 & pos, const CVector2& localCenter ,CVector2 size);

	HitResult hitTest(const CVector3& pos, float radius);

	void Rotate(CQuaternion rot);

	void Move(CVector3 move);

private:
	CVector2 vertex[4];
	CVector2 shaft = {1, 0}; // ��]����Ƃ��̖_
	CVector2 m_pos;
	
	CVector2 sideVec[4];
};

class Satellite : public IGameObject{
public:
	Satellite();
	~Satellite();

	bool Start() override;
	void Update() override;

	void setArrayPointer(Satellite** arrayPointer) {
		arrayP = arrayPointer;
	}

	void setPosition(const CVector3& pos) {
		m_pos = pos;
	};

private:
	static const CVector2 colliderSize;
	static const CVector2 colliderPosition;

	static constexpr float hitRotPower = 100.0f; //�q�b�g���^�����]�́B�x/sec�B
	static constexpr float rotDamping = 5.0f; //�b�ԂɎ������]�́B�x/sec�B
	static constexpr float maxRot = 500.0f; //�ő��]�́B����ȏ�ɂ͂Ȃ�Ȃ��B�x/sec�B

	prefab::CSkinModelRender* m_modelRender = nullptr;

	BoxCollider2D collider;

	float rotPower = 0.0f;
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 m_pos = {0,1000,000};

	CVector3 m_move = { 0,0,500 };

	Satellite** arrayP = nullptr;
};

