#include "stdafx.h"
#include "RadarRing.h"
#include "Player.h"
#include "Camera.h"

RadarRing::RadarRing()
{
}


RadarRing::~RadarRing()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(arrowSprite);
}

void RadarRing::SetPlayerRadar(const wchar_t * path, Player* player_) {
	draw_P = path;
	player = player_;
	switch (player_->GetPadNum()) {
	case 0:
		color = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;
	case 1:
		color = { 0.0f, 0.0f, 1.0f, 1.0f };
		break;
	case 2:
		color = { 0.1f, 1.0f, 0.0f, 1.0f };
		break;
	case 3:
		color = { 1.0f, 0.7f, 0.0f, 1.0f };
		break;
	}
}

bool RadarRing::Start()
{
	camera = FindGO<Camera>("Camera");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(draw_P);
	m_skinModelRender->SetScale({ 12.0f,12.0f,12.0f });

	arrowSprite = NewGO<prefab::CSpriteRender>(1);
	arrowSprite->Init(L"sprite/arrow.dds", 400 * 0.1f, 150*0.1f);
	arrowSprite->SetPivot({ 0.0f, 0.5f });
	arrowSprite->SetMulColor(color);

	tex.CreateFromDDSTextureFromFile(L"sprite/GaugeIn.dds");
	gaugeIn.Init(tex, 200, 200,true);
	color.a = 0.5f;
	gaugeIn.SetMulColor(color);
	return true;
}

void RadarRing::Update()
{
	m_skinModelRender->SetPosition(player->GetPosition());

	//プレイヤーの2D座標を取得
	CVector3 pPos;
	{
		CVector2 pos;
		MainCamera().CalcScreenPositionFromWorldPosition(pos, player->GetPosition());
		pPos = { pos.x, pos.y, 0 };
	}

	//カメラが遠くなるにつれて小さくしたりするための数値
	float cameraScale;
	{
		float angleSin = sinf(MainCamera().GetViewAngle() / 2) * 2;
		cameraScale = camera->getUpLength()*angleSin / cameraScaleDev;
	}

	{//スティック方向アロー
		int pNum = player->GetPadNum();

		//パッド取得
		float x = Pad(pNum).GetRStickXF();
		float y = Pad(pNum).GetRStickYF();

		//大きさ調整
		float length = sqrt(x * x + y * y);
		arrowSprite->setScale({ length ,1,1 });

		//回転させる
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisZ, atan2f(y, x));
		arrowSprite->SetRotation(rot);

		//表示位置を調整する
		CVector3 arrowVec = { 80, 0, 0 };
		arrowVec /= cameraScale;
		rot.Multiply(arrowVec);
		arrowSprite->SetPosition(pPos + arrowVec);
	}

	{//残弾数ゲージ
		float scale = 1 / cameraScale;
		gaugeIn.Update(pPos, CQuaternion::Identity, { scale,scale,scale });

		gaugeIn.setFillAmount(player->getBulletPercentage());
	}
}

void RadarRing::PostRender(CRenderContext & rc) {
	CCamera& camera = MainCamera2D();
	gaugeIn.Draw(rc, camera.GetViewMatrix(), camera.GetProjectionMatrix());
}

