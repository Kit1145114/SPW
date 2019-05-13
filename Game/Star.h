#pragma once
#include"Game.h"
#include"Player.h"

class Game;
class Player;

class Star: public IGameObject
{
public:
	Star();
	~Star();
	bool Start();
	void Update();
	void Push();
	void Rotation();
	void Death();
	void Pop(CVector3 position);
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}
private:
	Game* m_game = nullptr;					//ÉQÅ[ÉÄclassÇÃÉ|ÉCÉìÉ^ÅOÅO
	Player* m_player = nullptr;  
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_scale = { 1.0f,1.0f,1.0f };
	CQuaternion m_rotation = CQuaternion::Identity;
	CCharacterController m_CharaCon;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;
	int Limit = 300;
	float angle = 0.0f;
};

