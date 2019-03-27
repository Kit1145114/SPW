#pragma once
#include"Enemy.h"
#include"Game.h"
#include"Player.h"

class Enemy;
class Game;
class Player;

class Star: public IGameObject
{
public:
	Star();
	~Star();
	bool Start();
	void Update();
	void Hantei();
	void Push();
	void Rotation();
	void Death();
	void Init(CVector3 position)
	{
		m_position = position;
		m_skinModelRender->SetScale(m_scale);
		m_skinModelRender->SetPosition(position);
	};
	CVector3 GetPosition()
	{
		return m_position;
	}
private:
	Enemy* m_enemy = nullptr;				//エネミーclassのポインタ＾＾
	Game* m_game = nullptr;					//ゲームclassのポインタ＾＾
	Player* m_player = nullptr;  
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_scale = { 1.0f,1.0f,1.0f };
	CQuaternion m_rotation = CQuaternion::Identity;
	CCharacterController m_CharaCon;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;
	float angle = 0.0f;
};

