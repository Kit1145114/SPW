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
	void Move();
	Player* m_player;
	float st_kyori = 500.0f;
	CVector3 m_CameraPos = { 0.0f,0.0f,0.0f, };
	//���_���v�Z����B
	CVector3 pos = CVector3::Zero;
	//�����_���v�Z����
	CVector3 target = { 0.0f,0.0f,0.0f };

};

