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
	s_kazu = FindGO<SansenKazu>("SansenKazu");
		//カメラのニアクリップ
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(100000.0f);

	return true;
}

void Camera::TOP() {

	m_CameraPos = m_game->GetPosition();
	m_CameraPos.y += st_kyori;
	
	target = m_game->GetPosition() - m_CameraPos;

	//カメラ
	if (Pad(0).IsPress(enButtonUp)) {
		
		xup += -100.0f;
		
	}
	if (Pad(0).IsPress(enButtonDown)) {
		
		xdn += 100.0f;
		
	}
	m_CameraPos.y += xup;
	m_CameraPos.y += xdn;
	MainCamera().SetUp(CVector3::AxisZ);
}

void Camera::Move() {
	//ズーム＆アウト

}

void Camera::Update() {
	TOP();
	//Move();
	//メインカメラに注視点と視点を設定する。
	MainCamera().SetTarget(m_game->GetPosition());
	MainCamera().SetPosition(m_CameraPos);
	//カメラの更新。
	MainCamera().Update();
}

