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
	//カメラの上方向をZ軸に指定(真上から見下ろすため)
	MainCamera().SetUp(CVector3::AxisZ);

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

void Camera::shake(float power, float spring, float decay) {
	beforeDot = 1;
	shakeSpring = spring;
	shakeDecay = decay;
	shakeSpeed = { power, 0, 0 };
	CQuaternion rot;
	rot.SetRotation(CVector3::AxisY, Random().GetRandDouble() * CMath::PI2);
	rot.Apply(shakeSpeed);
}

CVector3 Camera::shakeProcess() {
	const float delta = GameTime().GetFrameDeltaTime();
	shakePos += shakeSpeed * delta;

	CVector3 oppositeVec = shakePos * -1;

	shakeSpeed += oppositeVec * delta * shakeSpring;

	float dot = shakeSpeed.Dot(shakePos);
	if (shakeSpeed.Dot(shakePos) * beforeDot <= 0) {
		float ran = Random().GetRandDouble() * 20 * 2 - 20;
		CQuaternion rot;
		rot.SetRotationDeg(CVector3::AxisY, ran);
		rot.Apply(shakeSpeed);
		shakeSpeed *= (1-shakeDecay);
	}
	beforeDot = dot;

	return shakePos;
}

void Camera::UpDownZoom() {
	//キー入力でズームを指定する
	if (Pad(0).IsPress(enButtonUp)) {
		cameraUp += -100.0f;
	}else
	if (Pad(0).IsPress(enButtonDown)) {
		cameraUp += 100.0f;
	}

	if (cameraUp > MaxCamera) {
		cameraUp = MaxCamera;
	} else if (MinCamera > cameraUp) {
		cameraUp = MinCamera;
	}
}

CVector3 Camera::calcCenter() {
	CVector3 center;
	//参加者の座標の平均を求めて、中央の座標とする
	int count = 0;
	for (Player* player : Game::GetInstance()->m_player) {
		if (player != nullptr) {
			center += player->GetPosition();
			count++;
		}
	}
	center /= count;
	return center;
}

void Camera::AutoZoom(const CVector3& center)
{
	//ズーム＆アウト
	float Saityou = -1;
	//縦
	for (Player* player : Game::GetInstance()->m_player)
	{
		if (player == nullptr) {
			continue;
		}
		float Max = fabs(player->GetPosition().z - center.z) + 10000;
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
		float Max = fabs(player->GetPosition().x - center.x) + 4000;
		if (Saityou < Max)
		{
			Saityou = Max;
		}
	}
	t = max( t, Saityou / max(0.1f, tan(yokoAngle )) );
	cameraUp = max(2500.0f, t );
}

void Camera::Update() {
	CVector3 targetPos;

#ifdef UseNetwork
	targetPos = m_player->GetPosition();
	UpDownZoom();
#else
	targetPos = calcCenter();
	AutoZoom(targetPos);
#endif

	targetPos += shakeProcess();

	MainCamera().SetTarget(targetPos);
	targetPos.y += cameraUp;
	MainCamera().SetPosition(targetPos);

	MainCamera().SetNear(cameraUp-10000.0f);
	MainCamera().SetFar(cameraUp+1200.0f);
	//カメラの更新。
	MainCamera().Update();
	
}

