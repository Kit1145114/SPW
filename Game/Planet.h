#pragma once
#include"Game.h"
#include"SansenKazu.h"
#include"Draw_1P.h"
#include"Draw_2P.h"
#include"Draw_3P.h"
#include"Draw_4P.h"

class Game;
class Player;
class Bullet;
class Star;
class SansenKazu;
class Draw_1P;
class Draw_2P;
class Draw_3P;
class Draw_4P;

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
	void Timer();
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
	Draw_1P* Pl1 = nullptr;
	Draw_2P* Pl2 = nullptr;
	Draw_3P* Pl3 = nullptr;
	Draw_4P* Pl4 = nullptr;
	float radius = { 30.0f };//	òfêØÇÃîºåa
	bool movecount = false;
	int myPlanetnumber;    //é©ï™ÇÃPlametÉiÉìÉoÅ[ï€ë∂óp
	int PadMaxKazu = 0;
	int time = 0;   //plametÇ™íaê∂ÇµÇƒÇ©ÇÁÇÃéûä‘
};

