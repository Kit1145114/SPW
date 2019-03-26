#pragma once
#include "Player.h"
#include"Game.h"
#include"SansenKazu.h"

class Player;
class Game;
class SansenKazu;

class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	void TOP();
	void Move();
	void SetKyori(float a)
	{
		st_kyori += a;
	}
	float GetKyori()
	{
		return st_kyori;
	}
	float MaxCameraPos()
	{
		return MaxCamera;
	}
	float MinCameraPos()
	{
		return MinCamera;
	}
private:
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	SansenKazu* s_kazu = nullptr;
	float st_kyori = 2000.0f;
	CVector3 m_CameraPos = { 0.0f,0.0f,0.0f, };
	//視点を計算する。
	CVector3 pos = CVector3::Zero;
	//注視点を計算する
	CVector3 target = { 0.0f,0.0f,0.0f };
	float MaxCamera = 3000.0f;
	float MinCamera = 1500.0f;
	CVector3 p1_pos = { 0.0f, 0.0f, 0.0f };
	CVector3 p2_pos = { 0.0f, 0.0f, 0.0f };
};

