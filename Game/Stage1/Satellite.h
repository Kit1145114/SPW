#pragma once
#include "..\..\tkEngine\physics\tkPhysicsDynamicObject.h"

class BoxCollider2D{
public:
	void Init(const CVector3 & pos, const CVector2& localCenter ,CVector2 size);

	int hitTest(const CVector3& pos, float radius);

	void Rotate(CQuaternion rot);

	void Move(CVector3 move);

	CVector2 vertex[4];
	CVector2 shaft = {1, 0}; // ‰ñ“]‚·‚é‚Æ‚«‚Ì–_
private:
	CVector2 m_pos;
	
	CVector2 sideVec[4];
};

class Satellite : public IGameObject{
public:
	Satellite();
	~Satellite();

	bool Start();
	void Update();

	void setPosition(const CVector3& pos) {
		m_pos = pos;
	};

private:
	static const CVector2 colliderSize;
	static const CVector2 colliderPosition;

	static constexpr float hitRotPower = 360.0f; //ƒqƒbƒg—^‚¦‚é‰ñ“]—ÍB“x/secB
	static constexpr float rotDamping = 10.0f; //•bŠÔ‚É¸‚í‚ê‚é‰ñ“]—ÍB“x/secB

	prefab::CSkinModelRender* m_modelRender = nullptr;

	BoxCollider2D collider;

	float rotPower = 0.0f;
	CQuaternion rot = CQuaternion::Identity;
	CVector3 m_pos = {0,1000,000};

	CVector3 m_move = { 200,0,200 };


	/*prefab::CSkinModelRender* tester[4];
	prefab::CSkinModelRender* testshaft;*/
};

