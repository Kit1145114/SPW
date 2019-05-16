#pragma once
#include "BoxCollider2D.h"

class Rocket : public IGameObject{
public:
	Rocket();
	~Rocket();

	bool Start() override;
	void Update() override;

	void setPosition(const CVector3& pos) {
		m_pos = pos;
	}

	void setArrayPointer(Rocket** p) {
		arrayP = p;
	}

private:
	static const CVector2 colliderSize;
	static const CVector2 colliderPosition;

	prefab::CSkinModelRender* m_modelRender = nullptr;

	BoxCollider2D collider;

	int needBullet = 10;
	bool awaking = false;
	int ownerNum = -1;

	CVector3 m_pos = {};
	CVector3 m_move = {400.0f, 0.0f, 0.0f};
	Rocket** arrayP = nullptr;
};

