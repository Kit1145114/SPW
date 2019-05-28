#pragma once
#include "..\Utility\BoxCollider2D.h"

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

	CVector3 getPosition() {
		return m_pos;
	}

	const BoxCollider2D* getCollider() const{
		return &collider;
	}

private:
	static const CVector2 colliderSize;
	static const CVector2 colliderPosition;

	static constexpr float hitRotPower = 100.0f; //ヒット時与える回転力。度/sec。
	static constexpr float rotDamping = 5.0f; //秒間に失われる回転力。度/sec。
	static constexpr float maxRot = 500.0f; //最大回転力。これ以上にはならない。度/sec。

	prefab::CSkinModelRender* m_modelRender = nullptr;

	BoxCollider2D collider;

	float rotPower = 0.0f;
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 m_pos = {0,1000,000};
	float firstScale = 0.0f;

	CVector3 m_move = { 0,0,500 };

	static constexpr float moveStarMax = 10000.0f;
	float moveStar = moveStarMax/2;

	Satellite** arrayP = nullptr;

	int lastBulletNum = -1;
};

