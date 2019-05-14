#include "stdafx.h"
#include "Meteo.h"


Meteo::Meteo()
{
}


Meteo::~Meteo()
{
	DeleteGO(m_skinModelRender);
}

bool Meteo::Start()
{
	game = Game::GetInstance();
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Inseki.cmo");
	m_skinModelRender->SetScale(scale);
	return true;
}

void Meteo::Update()
{
	timer++;
	if (timer == 1000)
	{
		Death();
	}
}

void Meteo::Move()
{

}

void Meteo::Death()
{
	DeleteGO(this);
}

void Meteo::Generate()
{
	Meteo* meteo = NewGO<Meteo>(0, "Meteo");

	CVector3 hako;
	do {
		meteo->repopflag = false;
		//ランダムポップ。
		float vx = Random().GetRandDouble();
		float vz = Random().GetRandDouble();
		hako.x = vx;
		hako.z = vz;
		if (Random().GetRandDouble() <= 0.5f)
			hako.x *= -1;
		if (Random().GetRandDouble() <= 0.5f)
			hako.z *= -1;
		//ランダム生成する場所の制限。
		float PosLimitx = 30000.0f;
		float PosLimitz = 20000.0f;
		hako.x *= PosLimitx;
		hako.z *= PosLimitz;

		meteo->m_position = hako;
	} while (meteo->repopflag == true);
}
