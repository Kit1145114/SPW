#pragma once
#include "BoxCollider2D.h"

class Rocket : public IGameObject{
public:
	void OnDestroy() override;

	bool Start() override;
	void Update() override;

	void setPosition(const CVector3& pos) {
		m_pos = pos;
	}

	CVector3 getPosition() const {
		return m_pos;
	}

	void setArrayPointer(Rocket** p) {
		arrayP = p;
	}

	const BoxCollider2D* getCollider() {
		return &collider;
	}

	void Explosion();

	bool isAwaking() {
		return awaking;
	}

	void damage() {
		hp--;
	}

private:
	static const CVector2 colliderSize;
	static const CVector2 colliderPosition;

	prefab::CSkinModelRender* m_modelRender = nullptr;

	BoxCollider2D collider;

	static constexpr int max_hp = 5;
	int hp = max_hp;
	bool awaking = false;
	int ownerNum = -1;

	static constexpr float controllPower = 10000.0f;

	CVector3 m_pos = {};
	CVector3 m_move = {400.0f, 0.0f, 0.0f};
	float radianRot = 0.0f;
	Rocket** arrayP = nullptr;

	prefab::CSpriteRender* arrowSprite = nullptr;

	void InitArrow(int ownerNum);
	void ArrowUpdate(const CVector3& stick);
};

