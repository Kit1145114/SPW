#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

bool Camera::Start() {
	//プレイヤーの検索
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	//カメラのニアクリップ
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);

	return true;
}
void Camera::TOP() {

	m_CameraPos = m_player->memoryPosition();
	m_CameraPos.y += st_kyori;
	
	target = m_player->memoryPosition() - m_CameraPos;

	//パッドの入力を使ってカメラを回す
	//float x = Pad(0).GetRStickXF();
	//float y = Pad(0).GetRStickYF();

	MainCamera().SetUp(CVector3::AxisZ);
}
void Camera::Move() {
	//ズーム＆アウト
	if (st_kyori>200.0) {
		//奥
		if (Pad(0).GetRStickYF() > 0.0) {
			st_kyori -= 10.0f;
		}
	}
	if (st_kyori<8000.0) {
		//手前
		if (Pad(0).GetRStickYF() < 0.0) {
			st_kyori += 10.0f;
		}
	}
}
void Camera::Update() {
	TOP();
	Move();
	//メインカメラに注視点と視点を設定する。
	MainCamera().SetTarget(m_player->memoryPosition());
	MainCamera().SetPosition(m_CameraPos);
	//カメラの更新。
	MainCamera().Update();
}

