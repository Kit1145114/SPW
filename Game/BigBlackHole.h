#pragma once
#include "BlackHole.h"
#include"Game.h"

class BigBlackHole : public IGameObject
{
public:
	BigBlackHole();
	~BigBlackHole();
	bool Start();
	static void Generate();
	void Gravity();
	void Update();
private:
	prefab::CEffect* effect;
	Game* m_game = nullptr;

	CVector3 BBHposition = { 0.0f,  0.0f,  0.0f };
	CVector3 BBHscale = { 100.0f,100.0f,100.0f };
	CVector3 position = { 0.0f,  0.0f,  0.0f };
	float BBHradius = { 9.0f };      //	��{�f���̔��a�B
	float BBHSearchment = { 5.0f };//	BigBBH�̏d�͔͈͂̒����B
	float BBHG_limitar = { 600.0f };//   BBH�̏d�́i�f�j�����B

	CVector3 scale = { 1.0f,1.0f,1.0f };
	int timer = 0;
	float radius = { 9.0f };       //	��{�f���̔��a�B*9(Big
	float Searchment = { 1000.0f };//	BH�̏d�͔͈͂̒����B
	float G_limitar = { 50000.0f };//   BH�̏d�́i�f�j�����B
};

