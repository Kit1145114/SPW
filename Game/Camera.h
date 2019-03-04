#pragma once
#include "Player.h"
class Player;
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	void TOP();
	Player* m_player;

	CVector3 m_CameraPos = { 0.0f,500.0f,0.0f, };
	//視点を計算する。
	CVector3 pos = CVector3::Zero;
	//注視点を計算する
	CVector3 target = { 0.0f,0.0f,0.0f };

};

