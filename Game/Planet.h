#pragma once
#include"Game.h"
class Game;
class Player;


class Planet : public IGameObject
{
public:
	Planet();
	~Planet();
	bool Start();
	void Update();
	void Move();
	void Death();
	void explosion();
	static void Generate();
	void init(CVector3 position, prefab::CSkinModelRender* skinModelRender);

private:
	CCharacterController p_CharaCon;
	CVector3 p_position;
	CVector3 scale = { 1.0f,1.0f,1.0f };
	CVector3 p_moveSpeed = CVector3::Zero;
	CQuaternion p_rotation = CQuaternion::Identity;
	
	prefab::CSkinModelRender* p_skinModelRender0 = nullptr;
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	Planet* hoge = nullptr;
	float radius = { 30.0f };//	òfêØÇÃîºåa
	
};

