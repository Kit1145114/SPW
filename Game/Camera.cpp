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
	MainCamera().SetFar(10000.0f);

	return true;
}

void Camera::TOP() {

	m_CameraPos = m_game->GetPosition();
	m_CameraPos.y += st_kyori;
	
	target = m_game->GetPosition() - m_CameraPos;

	//パッドの入力を使ってカメラを回す
	//float x = Pad(0).GetRStickXF();
	//float y = Pad(0).GetRStickYF();

	MainCamera().SetUp(CVector3::AxisZ);
}

void Camera::Move() {
	//ズーム＆アウト
	switch (s_kazu->GetKazu())
	{
	case 1:
		target = m_game->GetPosition() - m_CameraPos;
		break;
	case 2:
		p1_pos = m_player[0].GetPosition();
		target = p1_pos;
		p2_pos = m_player[1].GetPosition();
		target = p2_pos;
		break;
	case 3:
		//target = m_game->GetPosition() - m_CameraPos;
		break;
	case 4:
		//target = m_game->GetPosition() - m_CameraPos;
		break;
	}
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

