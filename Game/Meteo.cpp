#include "stdafx.h"
#include "Meteo.h"
#include "Star.h"

Meteo::Meteo()
{
	game = Game::GetInstance();
}

Meteo::~Meteo()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(effect);
}

bool Meteo::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Inseki.cmo");
	scale = { 40.0f,40.0f,40.0f };
	//effect = NewGO<prefab::CEffect>(0);
	///*effect->Play(L"effect/Fire.efk");
	//effect->SetPosition(e_position);*/
	m_skinModelRender->SetScale(scale);
	return true;
}

void Meteo::Update()
{
	if (Game::GetInstance()->isWait())return;
	Move();
	//Rotation();
	Hantei();
	//effect->SetPosition(e_position);
}
//動く、動く(we go walk...)
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
	e_position = m_position;
	e_position.y = 2000.0f;
	m_skinModelRender->SetPosition(m_position);
}
//死ぬ
void Meteo::Death()
{
	prefab::CEffect* effect;
	effect = NewGO<prefab::CEffect>(0);
	//エフェクトを再生。
	effect->Play(L"effect/BigExplosion.efk");
	//エフェクトに半径/（Ｍａｘと差）をかける
	effect->SetScale({ 1, 1, 1 });
	effect->SetPosition(m_position + CVector3(0, 1000, 0));

	prefab::CSoundSource* se = NewGO<prefab::CSoundSource>(0);
	se->Init(L"sound/bakuhatu.wav");
	se->Play(false);                     //ワンショット再生。
	se->SetVolume(0.3f);
	
	CVector3 pos = m_position;
	pos.z += 500;
	for (int i = 0; i < 3; i++) {
		Star* star = NewGO<Star>(0, "Star");
		//hanteiはたぶん半径のことだと思っています。
		star->Pop(pos, { 50,50,50 });

		if (i == 0) {
			pos.z -= 1500.0f;
			pos.x += 1000.0f;
		} else if (i == 1) {
			pos.x -= 2000.0f;
		}
	}

	DeleteGO(this);
}
//いろんな判定。
void Meteo::Hantei()
{
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//プレイヤーが無敵なら攻撃をやめる。
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			if (kyori.Length() < Game::GetInstance()->m_player[i]->Getradius() + (radius*1.5)
				&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
				Game::GetInstance()->m_player[i]->AddHP(-100);
				Game::GetInstance()->m_player[i]->SetLABulletNum(-1);
					//Death();
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
		DeleteGO(this);
	}
}
//回転させるよー
void Meteo::Rotation()
{
	angleY += randomspeed.x /20.0f;
	m_rotation.SetRotationDeg(CVector3::AxisY, angleY);
	m_skinModelRender->SetRotation(m_rotation);
}