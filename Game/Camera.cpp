#include "stdafx.h"
#include "Camera.h"
#include "Game.h"
#include "Network/NetManager.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

bool Camera::Start() {
	//カメラのニアクリップ
	MainCamera().SetUp(CVector3::AxisZ);
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(100000.0f);

	//自分のプレイヤー番号を取得。
	int myNum
#ifdef UseNetwork
		= NetManager::getLocalNum();
#else
		= 0;
#endif
	m_player = Game::GetInstance()->m_player[myNum];
	game = Game::GetInstance();
	return true;
}

void Camera::TOP() {
	//カメラ
	if (Pad(0).IsPress(enButtonUp)) {
		up += -100.0f;
	}else
	if (Pad(0).IsPress(enButtonDown)) {
		up += 100.0f;
	}

	if (up > MaxCamera) {
		up = MaxCamera;
	} else if (MinCamera > up) {
		up = MinCamera;
	}
}

void Camera::Move() 
{
	//ズーム＆アウト
	Saityou = -1;
	//縦
	for (Player* player : Game::GetInstance()->m_player)
	{
		if (player == nullptr) {
			continue;
		}
		float Max = fabs(player->GetPosition().z - Tyuou.z) + 10000;
		if (Saityou < Max)
		{
			Saityou = Max;
		}
	}
	float tateViewAngle = MainCamera().GetViewAngle() * 0.5f;

	float t = Saityou / max(0.1f, tan(tateViewAngle));
	//カメラの横の画角を求める。
	float yokoAngle = atanf(MainCamera().GetAspect() * tan(tateViewAngle));

	Saityou = -1;
	for (Player* player : Game::GetInstance()->m_player)
	{
		if (player == nullptr) {
			continue;
		}
		float Max = fabs(player->GetPosition().x - Tyuou.x) + 4000;
		if (Saityou < Max)
		{
			Saityou = Max;
		}
	}
	t = max( t, Saityou / max(0.1f, tan(yokoAngle )) );
	cameraUp = max(2500.0f, t );
}

void Camera::Update() {
	TOP();
	//メインカメラに注視点と視点を設定する。
#ifdef UseNetwork
	CVector3 pos = m_player->GetPosition();
	cameraUp = up;
#else
	CVector3 pos;
	if (Game::GetInstance()->GetSansenKazu() == 1) {
		pos = m_player->GetPosition();
	} else {
		int count = 0;
		for (Player* player : Game::GetInstance()->m_player) {
			if (player != nullptr) {
				pos += player->GetPosition();
				count++;
			}
		}
		pos /= count;
	}
#endif

	Tyuou = pos;
	Move();
	MainCamera().SetTarget(pos);
	pos.y += cameraUp;
	MainCamera().SetPosition(pos);
	//カメラの更新。
	MainCamera().Update();
	
}

