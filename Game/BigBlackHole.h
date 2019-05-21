#pragma once
#include "BlackHole.h"
#include"Game.h"

class BigBlackHole : public IGameObject
{
public:
	BigBlackHole();
	~BigBlackHole();
	bool Start();
	//���Ԑ����Ȃ��̌Œ�̂a�g(BBH);
	static void Generate(CVector3 position, float magnification, float Search, float Limit);
	void Gravity();
	void Update();
private:
	prefab::CEffect* effect;
	Game* m_game = nullptr;

	CVector3 BBHposition = { 0.0f,  0.0f,  0.0f };
	CVector3 BBHscale = { 100.0f,100.0f,100.0f };
	CVector3 position = { 0.0f,  0.0f,  0.0f };
	float BBHradius = { 100.0f };      //	��{�f���̔��a�B
	float BBHSearchment = { 15000.0f };//	BBH�̏d�͔͈͂̒����B
	float BBHG_limitar = { 100000.0f };//   BBH�̏d�́i�f�j�����B

	CVector3 scale = { 1.0f,1.0f,1.0f };
	int timer = 0;
	float radius = { 1.0f };       //	��{�f���̔��a�B
	float Searchment = { 1500.0f };//	BH�̏d�͔͈͂̒����B
	float G_limitar = { 50000.0f };//   BH�̏d�́i�f�j�����B
};

