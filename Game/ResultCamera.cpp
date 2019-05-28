#include "stdafx.h"
#include "ResultCamera.h"
#include "Player.h"

bool ResultCamera::Start() {
	return true;
}

void ResultCamera::Update() {
	CVector3 goLookPos = player->GetPosition();
	CVector3 goCameraPos = goLookPos;
	goCameraPos.y += 5000;
	goCameraPos.z -= 5000;

	float delta = GameTime().GetFrameDeltaTime();
	CVector3 lookSpeed = (goLookPos - lookPos);
	lookPos += lookSpeed * delta * 2;
	CVector3 cameraSpeed = (goCameraPos - cameraPos);
	cameraPos += cameraSpeed * delta * 2;

	float len = (cameraPos - lookPos).Length();

	MainCamera().SetTarget(lookPos);
	MainCamera().SetPosition(cameraPos);
	MainCamera().SetNear(1.0f);
	MainCamera().SetFar(100000.0f);
	MainCamera().Update();
}

void ResultCamera::Init(const Player * go, const CVector3 & nowCamera, const CVector3 & nowLook) {
	player = go;
	/*goLookPos = go;
	goCameraPos = goLookPos;
	goCameraPos.y += 5000;
	goCameraPos.z -= 5000;*/
	lookPos = nowLook;
	cameraPos = nowCamera;
}
