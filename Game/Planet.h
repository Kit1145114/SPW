#pragma once
#include"Game.h"
#include"SansenKazu.h"
class Game;
class Player;
class Bullet;
class Star;
class SansenKazu;

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
	static void Generate(int Reload);
	void init(CVector3 position, prefab::CSkinModelRender* skinModelRender);

private:
	CCharacterController p_CharaCon;
	CVector3 p_position;
	CVector3 scale = { 1.0f,1.0f,1.0f };
	CVector3 p_moveSpeed = CVector3::Zero;
	CQuaternion p_rotation = CQuaternion::Identity;
	CVector3 randomspeed = CVector3::Zero;
	prefab::CSkinModelRender* p_skinModelRender0 = nullptr;
	Game* m_game = nullptr;
	SansenKazu* s_kazu = nullptr;
	Player* m_player[4] = { nullptr };
	Bullet* m_bullet = nullptr;
	SansenKazu* m_sansenkazu = nullptr;
	Planet* hoge = nullptr;
	float radius = { 30.0f };//	惑星の半径
	bool movecount = false;
	int myPlanetnumber;    //自分のPlametナンバー保存用
	int PadMaxKazu = 0;
};

