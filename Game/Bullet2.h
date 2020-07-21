#pragma once
#include"Bullet.h"
class Bullet2 : public IGameObject 
{
public:
	Bullet2();
	~Bullet2();
	void Update();
	void Death();
private:
	Game * m_game = nullptr;
	int PB = 0;
	int Limit = 5.0f;
	float timer = 0.0f;
	float BulletHantei = 500.0f;
	float BulletYpos = 300.0f;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_scale = { 10.0f,10.0f,10.0f };
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	bool Kill = false;
};

