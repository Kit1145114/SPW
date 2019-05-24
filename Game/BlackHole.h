#pragma once
#include "Planet.h"
#include "Game.h"
#include"Meteo.h"

class Game;
class Player;
class Planet;
class Draw_Player;
class BlackHole : public IGameObject
{
public:
	BlackHole();
	~BlackHole();
	bool Start();
	//���Ԑ�������̕��ʂ̂a�g;
	static void Generate(CVector3 position, float magnification); 
	//���Ԑ����Ȃ��̌Œ�̂a�g(BBH);
	static void Generate2(CVector3 position, float magnification, float Search, float Limit);
	void Move();
	void Gravity();
	void Count();
	void Death();
	void Update();
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetScale(CVector3 sca)
	{
		scale = sca;
	}
protected:
	prefab::CEffect* effect;
	Game* m_game = nullptr;
	Draw_Player* Pl1 = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 scale = { 1.0f,1.0f,1.0f };
	int timer = 0;
	float radius = { 1.0f };       //	��{�f���̔��a�B
	float Searchment = { 1500.0f };//	BH�̏d�͔͈͂̒����B
	float G_limitar = { 50000.0f };//   BH�̏d�́i�f�j�����B
	float BBHnizyou = { 1000.0f }; //   BBH�i��撲���B
	bool Countflg = false;         //   ���R���ł��邩�̃t���O�B
};

