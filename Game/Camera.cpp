#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}
bool Camera::Start() {

	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(10000.0f);
	return true;
}

void Camera::Update() {

	//注視点を計算
	CVector3 target = { 0.0f,0.0f,0.0f };

	//視点を計算する。
	CVector3 pos = target + m_CameraPos;
	//メインカメラに注視点と視点を設定する。
	MainCamera().SetTarget(target);
	MainCamera().SetPosition(pos);
	//カメラの更新。
	MainCamera().Update();

}