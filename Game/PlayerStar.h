#pragma once
#include"Player.h"
#include"Game.h"

class Player;
class Game;
class PlayerStar : public IGameObject
{
public:
	PlayerStar();
	~PlayerStar();
	bool Start();
	void Update();
	void Rotation();
	void Death();
	void Pop(CVector3 position);
	void DesPlayer(CVector3 position) {
		Deathplayertposition = position;
	}
	void GetPlayer(CVector3 position) {
		Getplayerposition = position;
	}
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}
	void AddPositionX(float x)
	{
		m_position.x += x;
	}
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetStarCount(int kazu)
	{
		StarCount = kazu;
	}
	int GetStarCount()
	{
		return StarCount;
	}
private:
	Player * m_player[3] = { nullptr };
	Game* m_game = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 Deathplayertposition = CVector3::Zero;
	CVector3 Getplayerposition = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 Tyuou = CVector3::Zero;
	CVector3 m_scale = { 1.0f,1.0f,1.0f };
	CQuaternion m_rotation = CQuaternion::Identity;
	CCharacterController m_CharaCon;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;
	int MaxTimer = 500;
	int ResetTimer = 0;
	int StarKazu = 0;
	int StarCount = 0;

	int SansenKazu = 0;
	float angle = 0.0f;
	float S_move = 15.0f;
};

