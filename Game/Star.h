#pragma once
#include"Enemy.h"
#include"Game.h"

class Enemy;
class Game;
class Star: public IGameObject
{
public:
	Star();
	~Star();
	bool Start();
	void Update();
	void Push();

	Enemy* m_enemy = nullptr;
	Game* m_game = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;

private:
	int m_timer = 0;
};

