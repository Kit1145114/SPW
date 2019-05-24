#include "stdafx.h"
#include "BlackHole.h"
#include "Star.h"

BlackHole::BlackHole()
{
}


BlackHole::~BlackHole()
{
	if (effect !=nullptr) {
		DeleteGO(effect);
	}
}

bool BlackHole::Start()
{
	m_game = Game::GetInstance();

	//エフェクトを作成。
	effect = NewGO<prefab::CEffect>(0);
	//エフェクトを再生。
	effect->Play(L"effect/BH.efk");
	scale = { 0.1f,0.1f,0.1f };
	effect->SetScale(scale*radius);
	effect->SetPosition(m_position);
	//BHカウントしておく。
	Game::GetInstance()->SetBHCount(1);
	//
	effect->SetEffectFlag(true);
	return true;
}

void BlackHole::Generate(CVector3 position, float magnification)
{
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	//保存。
	bh->m_position = position;
	bh->radius *= magnification/500;
}


void BlackHole::Move()
{
	//Playerサーチ。
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//プレイヤーが無敵なら吸収をやめる。
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//対象との距離を測定。
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			//対象との距離が一定以下になったら。
				if (kyori.Length() < radius * Searchment*1.2) {
					//Ｇ中心に遠ければ弱く、近ければ強く。
					float G = radius * Searchment - kyori.Length();
					//対象に渡す重力。反転（-1）すれば重力となる。
					G_limitar = { 50.0f };//   BBHの重力（Ｇ）調整。
					CVector3 Migawari = kyori;
					Migawari.Normalize();
					G = G * G / BBHnizyou;
					Game::GetInstance()->m_player[i]->SetMoveSpeed(((Migawari * G) / G_limitar)*-1);
					//Game::GetInstance()->m_player[i]->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
					//対象との距離が中心に近くなったら。
					if (kyori.Length() < radius * Searchment / 5) {
						//破壊。
						Game::GetInstance()->m_player[i]->AddHP(-100);
						Game::GetInstance()->m_player[i]->SetLABulletNum(-1);
					}
				}
		}
	}
	//Plametサーチ。
	for (int i = 0; i < Planetnumber_Num; i++) {
		//対象がnullptrでなければ。
		if (Game::GetInstance()->memoryPP[i] != nullptr) {
			//対象との距離を測定。
			CVector3 kyori = Game::GetInstance()->memoryPP[i]->GetPosition() - m_position;
			//対象との距離が一定以下になったら。
				if (kyori.Length() < radius * Searchment) {
					//Ｇ中心に遠ければ弱く、近ければ強く。
					float G = radius * Searchment - kyori.Length();
					//対象に渡す重力。、反転（-1）すれば重力となる。
					G_limitar = { 100.0f };//   BBHの重力（Ｇ）調整。
					CVector3 Migawari = kyori;
					Migawari.Normalize();
					G = G * G / BBHnizyou;
					Game::GetInstance()->memoryPP[i]->SetMoveSpeed(((Migawari * G) / G_limitar)*-1);
					//Game::GetInstance()->memoryPP[i]->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
					//対象との距離が中心に近くなったら。
					if (kyori.Length() < radius * Searchment / 5) {
						//破壊。
						Game::GetInstance()->memoryPP[i]->explosion();
					}
				}
		}
	}
	//Starサーチ。
	QueryGOs<Star>("Star", [&](Star* star)->bool {
		CVector3 Kyori = star->GetPosition() - m_position;
		if (Kyori.Length() < radius * Searchment) {
			m_game->SetStarCount(-1);
			star->Death();
		} 
		return true;
	});
	//Bulletサーチ。
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		//対象との距離を測定。
		CVector3 kyori = b->GetPosition() - m_position;
		//対象との距離が一定以下になったら。
		if (kyori.Length() < radius * Searchment) {
			//Ｇ中心に遠ければ弱く、近ければ強く。
			float G = radius * Searchment - kyori.Length();
			//対象に渡す重力。すれば重力となる。
			G_limitar = { 200.0f };//   BBHの重力（Ｇ）調整。
			CVector3 Migawari = kyori;
			Migawari.Normalize();
			G = G * G / BBHnizyou;
			b->SetMoveSpeed(((Migawari * G) / G_limitar)*-1);
			//b->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
		}
		return true;
	});
	//メテオサーチ。
	QueryGOs<Meteo>("Meteo", [&](Meteo* m) ->bool {
		//対象との距離を測定。
		CVector3 kyori = m->GetPosition() - m_position;
		//対象との距離が一定以下になったら。
		if (kyori.Length() < radius * Searchment) {
			//Ｇ中心に遠ければ弱く、近ければ強く。
			float G = radius * Searchment - kyori.Length();
			//対象に渡す重力。kyoriにGをかけてG_limitarで制限調整して、反転（-1）すれば重力となる。
			G_limitar = { 600.0f };//   BBHの重力（Ｇ）調整。
			CVector3 Migawari = kyori;
			Migawari.Normalize();
			G = G * G / BBHnizyou;
			m->SetMoveSpeed(((Migawari * G) / G_limitar)*-1);
			if (kyori.Length() < radius * Searchment / 5) {
				//破壊。
				m->Death();
			}
		}
		return true;
	});
}

void BlackHole::Gravity()
{

}

void BlackHole::Count()
{
	if (Countflg == false) {
		timer++;
		if (timer > 720) {
			Death();
		}
	}
}

void BlackHole::Death()
{
	DeleteGO(this);
	Game::GetInstance()->SetBHCount(-1);
}

void BlackHole::Size()
{
	if (scale.x <=1.0f) {
		scale += { 0.01f,0.01f,0.01f };
		effect->SetScale(scale*radius);
	}
}

void BlackHole::Update()
{
	Size();
	Move();
	Count();
}
