#include "stdafx.h"
#include "ResultCamera.h"
#include "Player.h"

ResultCamera::ResultCamera() : tiesMoveWait(Player::c_tiseMove/2){
}

bool ResultCamera::Start() {
	return true;
}

void ResultCamera::Update() {
	float delta = GameTime().GetFrameDeltaTime();

	CVector3 goLookPos;
	//同点1位ワープ終了まで平均点は求めない。
	if (tiesMoveWait <= 0) {
		for (int i = 0; i < playerNum; i++) {
			goLookPos += player[i]->GetPosition();
		}
		goLookPos /= playerNum;
	} else {
		goLookPos = player[0]->GetPosition();
		tiesMoveWait -= delta;
	}

	CVector3 goCameraPos = goLookPos;
	goCameraPos.y += 7000;
	goCameraPos.z -= 7000;

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

void ResultCamera::Init(const Player ** go, int goNum, const CVector3 & nowCamera, const CVector3 & nowLook) {
	for (int i = 0; i < goNum; i++) {
		player[i] = (*go);
		go++;
	}
	playerNum = goNum;
	lookPos = nowLook;
	cameraPos = nowCamera;
}
