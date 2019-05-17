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
	//timer++;
	//if (timer == 2500)
	//{
	//	Death();
	//}
}
//ìÆÇ≠
void Meteo::Move()
{

	if (movecount == false) {

		randomspeed.x = Random().GetRandDouble() * Speed * GameTime().GetFrameDeltaTime();
		randomspeed.z = Random().GetRandDouble() * Speed * GameTime().GetFrameDeltaTime();
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.x *= -1;
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.z *= -1;

		movecount = true;
	}
	m_position += randomspeed;
	m_skinModelRender->SetPosition(m_position);
}
//éÄÇ 
void Meteo::Death()
{
	DeleteGO(this);
}
//Ç¢ÇÎÇÒÇ»îªíËÅB
void Meteo::Hantei()
{
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//ÉvÉåÉCÉÑÅ[Ç™ñ≥ìGÇ»ÇÁçUåÇÇÇ‚ÇﬂÇÈÅB
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			if (kyori.Length() < hantei
				&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
				Game::GetInstance()->m_player[i]->AddHP(-100);
				Game::GetInstance()->m_player[i]->SetLABulletNum(-1);
					//Death();
			}
		}
	}
	//íeÇÃîªíË
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* bullet)->bool
	{
		CVector3 b_kyori = bullet->GetPosition() - m_position;
		if (b_kyori.Length() < hantei) {
			bullet->Death();
		}
		return true;
	});
	QueryGOs<Planet>("planet", [&](Planet* planet)->bool
	{
		CVector3 p_kyori = planet->GetPosition() - m_position;
		if (p_kyori.Length() < Plhantei) {
			planet->explosion();
		}
		return true;
	});
	//QueryGOs<Meteo>("Meteo", [&](Meteo* meteo)->bool
	//{
	//	CVector3 m_kyori = meteo->GetPosition() - m_position;
	//	if (m_kyori.Length() > Metehantei) {
	//		Death();
	//	}
	//	return true;
	//});
	if (m_position.x > PosMaxLimitx || m_position.x< -PosMaxLimitx
		|| m_position.z>PosMaxLimitz || m_position.z < -PosMaxLimitz) {
		Death();
	}
}
