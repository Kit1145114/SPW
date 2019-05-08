#include "stdafx.h"
#include "Camera.h"
#include "Game.h"

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

	//自分のプレイヤー番号を取得。とりあえず0番。
	m_player = Game::GetInstance()->m_player[0];

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

void Camera::Move() {
	//ズーム＆アウト

}

void Camera::Update() {
	TOP();
	//Move();
	//メインカメラに注視点と視点を設定する。
	CVector3 pos = m_player->GetPosition();
	pos.y = Syoki;
	MainCamera().SetTarget(pos);
	pos.y += up;
	MainCamera().SetPosition(pos);
	//カメラの更新。
	MainCamera().Update();
}

