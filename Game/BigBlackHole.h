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
	void Sound();
	void Update();
private:
	prefab::CEffect* effect = nullptr;
	Game* m_game = nullptr;

	CVector3 BBHposition = { 0.0f,  0.0f,  0.0f };
	CVector3 BBHscale = { 100.0f,100.0f,100.0f };
	CVector3 position = { 0.0f,  0.0f,  0.0f };
	float BBHradius = { 9.0f };      //	î{f¯Ì¼aB
	float BBHSearchment = { 5.0f };//	BigBBHÌdÍÍÍÌ²®B
	float BBHG_limitar = { 600.0f };//   BBHÌdÍifj²®B
	float BBHnizyou = { 32000.0f }; //   BBHiñæ²®B
	CVector3 scale = { 1.0f,1.0f,1.0f };
	int timer = 0;
	float radius = { 9.0f };       //	î{f¯Ì¼aB*9(Big
	float Searchment = { 1000.0f };//	BHÌdÍÍÍÌ²®B
	float G_limitar = { 50000.0f };//   BHÌdÍifj²®B
	prefab::CSoundSource* SoundSource = nullptr;//BGMpÌTEh\[XB
};

