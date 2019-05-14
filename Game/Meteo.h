#pragma once
#include"Game.h"

class Game;
class Meteo: public IGameObject
{
public:
	Meteo();
	~Meteo();
	bool Start();
	void Update();
	void Move();
	void Death();
	void Generate();
private:
	Game* game = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 scale = CVector3::Zero;
	int timer = 0;
	bool repopflag = false;
};

