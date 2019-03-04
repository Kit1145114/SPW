#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}
bool Camera::Start() {

	
	m_player = FindGO<Player>("Player");

	//カメラのニアクリップ
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);
	return true;
}
void Camera::TOP() {

	target = m_player->m_position - m_CameraPos;

	//パッドの入力を使ってカメラを回す
	//float x = Pad(0).GetRStickXF();
	//float y = Pad(0).GetRStickYF();

	MainCamera().GetForward();
}
void Camera::Update() {

	TOP();
	//メインカメラに注視点と視点を設定する。
	MainCamera().SetTarget(target);
	MainCamera().SetPosition(m_CameraPos);
	//カメラの更新。
	MainCamera().Update();

}

