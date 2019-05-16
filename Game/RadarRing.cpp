#include "stdafx.h"
#include "RadarRing.h"


RadarRing::RadarRing()
{
}


RadarRing::~RadarRing()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(arrowSprite);
}

void RadarRing::SetPlayerRadar(const wchar_t * player, int num) {
	draw_P = player;
	pNum = num;
	switch (num) {
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
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(draw_P);
	scale = { 12.0f,12.0f,12.0f };
	m_skinModelRender->SetScale(scale);

	arrowSprite = NewGO<prefab::CSpriteRender>(0);
	arrowSprite->Init(L"sprite/arrow.dds", 400 * 0.1f, 150*0.1f);
	arrowSprite->SetPivot({ 0.0f, 0.5f });
	arrowSprite->SetMulColor(color);
	return true;
}

void RadarRing::Update()
{
	m_skinModelRender->SetPosition(m_position);

	//パッド取得
	float x = Pad(pNum).GetRStickXF();
	float y = Pad(pNum).GetRStickYF();

	//大きさ調整
	float length = sqrt(x * x + y * y);
	arrowSprite->setScale({length ,1,1 });

	//回転させる
	CQuaternion rot;
	rot.SetRotation(CVector3::AxisZ, atan2f(y, x));
	arrowSprite->SetRotation(rot);

	//表示位置を調整する
	CVector3 arrowVec = { 40, 0, 0 };
	rot.Multiply(arrowVec);
	CVector2 pos;
	MainCamera().CalcScreenPositionFromWorldPosition(pos, m_position);
	pos.x += arrowVec.x;
	pos.y += arrowVec.y;
	arrowSprite->SetPosition(CVector3(pos.x, pos.y, 0));
}

