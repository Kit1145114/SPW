#pragma once
#include "..\..\tkEngine\physics\tkPhysicsDynamicObject.h"

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
	prefab::CSkinModelRender* m_modelRender = nullptr;
	CPhysicsDynamicObject collider;

	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 m_pos = CVector3::Zero;
};

