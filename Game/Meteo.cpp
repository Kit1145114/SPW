#include "stdafx.h"
#include "Meteo.h"


Meteo::Meteo()
{
	game = Game::GetInstance();
}


Meteo::~Meteo()
{
	DeleteGO(m_skinModelRender);
}

bool Meteo::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Inseki.cmo");
	scale = { 50.0f,5.0f,50.0f };
	m_skinModelRender->SetScale(scale);
	return true;
}

void Meteo::Update()
{
	Move();
	Hantei();
	timer++;
	//if (timer == 2500)
	//{
	//	Death();
	//}
}

void Meteo::Move()
{

	if (movecount == false) {

		randomspeed.x = Random().GetRandDouble() * 20000 * GameTime().GetFrameDeltaTime();
		randomspeed.z = Random().GetRandDouble() * 20000 * GameTime().GetFrameDeltaTime();
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.x *= -1;
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.z *= -1;

		movecount = true;
	}
	m_position += randomspeed;
	m_skinModelRender->SetPosition(m_position);
}

void Meteo::Death()
{
	DeleteGO(this);
}

void Meteo::Hantei()
{
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//プレイヤーが無敵なら攻撃をやめる。
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			if (kyori.Length() < hantei
				&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
				Game::GetInstance()->m_player[i]->AddHP(-100);
				if (timer > 2) { //ＰＯＰ時は勘弁してやっぞ！
					Death();
				}
			}
		}
	}
	//弾の判定
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* bullet)->bool
	{
		CVector3 b_kyori = bullet->GetPosition() - m_position;
		if (b_kyori.Length() < hantei) {
			bullet->Death();
		}
		return true;
	});
	if (m_position.x > PosMaxLimitx || m_position.x< -PosMaxLimitx
		|| m_position.z>PosMaxLimitz || m_position.z < -PosMaxLimitz) {
		Death();
	}
}

//void Meteo::InitTime()
//{
//const int Initkazu = 2;
//for (int i = 0; i < Initkazu; i++) {
//	Meteo* meteo = NewGO<Meteo>(0, "Meteo");
//	CVector3 hako;
//	do {
//		meteo->repopflag = false;
//		//ランダムポップ。
//		float vx = Random().GetRandDouble();
//		float vz = Random().GetRandDouble();
//		hako.x = vx;
//		hako.z = vz;
//		if (Random().GetRandDouble() <= 0.5f)
//			hako.x *= -1;
//		if (Random().GetRandDouble() <= 0.5f)
//			hako.z *= -1;
//		//ランダム生成する場所の制限。
//		float PosLimitx = 30000.0f;
//		float PosLimitz = 20000.0f;
//		hako.x *= PosLimitx;
//		hako.z *= PosLimitz;
//
//		meteo->m_position = hako;
//	} while (meteo->repopflag == true);
//}
//return true;
//}
