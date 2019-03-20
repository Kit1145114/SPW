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

private:
	Enemy* m_enemy = nullptr;				//�G�l�~�[class�̃|�C���^�O�O
	Game* m_game = nullptr;					//�Q�[��class�̃|�C���^�O�O
	Player* m_player = nullptr;  
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	CCharacterController m_CharaCon;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	int m_timer = 0;
};
