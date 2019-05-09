#include "stdafx.h"
#include "BlackHole.h"


BlackHole::BlackHole()
{
}


BlackHole::~BlackHole()
{
}

bool BlackHole::Start()
{
	m_game = Game::GetInstance();
	//エフェクトを作成。
	prefab::CEffect* effect;
	effect = NewGO<prefab::CEffect>(0);
	//エフェクトを再生。
	effect->Play(L"effect/BH.efk");
	CVector3 scale = { 1.0f,1.0f,1.0f };
	effect->SetScale(scale*radius);
	effect->SetPosition(m_position);
	return true;
}

void BlackHole::Generate(CVector3 position, float magnification)
{
	//ポジションの保存。
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	bh->m_position = position;
	bh->radius *= magnification/500;
	////エフェクトを作成。
	//prefab::CEffect* effect;
	//effect = NewGO<prefab::CEffect>(0);
	////エフェクトを再生。
	//effect->Play(L"effect/BH.efk");
	//CVector3 scale = { 10.0f,10.0f,10.0f };
	//effect->SetScale(scale*magnification);
	//effect->SetPosition(position);
}

void BlackHole::Move()
{
	//Playerサーチ。
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		CVector3 player_kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
		if (player_kyori.Length() < radius * 1200) {
			Game::GetInstance()->m_player[i]->SetPosition(m_position);
				//Game::GetInstance()->m_player[i]->GetPosition() -(player_kyori/5));
				
		}
	}
	//QueryGOs<Player>("planet", [&](Player* player) ->bool {

	//	CVector3 player_kyori = player->GetPosition() - m_position;
	//	if (player_kyori.Length() < radius) {
	//		player->SetPosition(m_position);
	//		//Game::GetInstance()->m_player[i]->GetPosition() -(player_kyori/5));

	//	}
	//	return true;
	//});

	//Plametサーチ。
	for (int i = 0; i < Planetnumber_Num; i++) {
		CVector3 plamet_kyori = Game::GetInstance()->memoryPP[i]->GetPosition() - m_position;
		if (plamet_kyori.Length() < radius * 1200) {
			Game::GetInstance()->memoryPP[i]->SetPosition(Game::GetInstance()->memoryPP[i]->GetPosition() + (plamet_kyori*-1 / 10));
		}
	}
	/*QueryGOs<Planet>("planet", [&](Planet* plnet) ->bool {
		CVector3 plamet_kyori = plnet->GetPosition() - m_position;
			if (plamet_kyori.Length() < radius) {
				plnet->SetPosition(plnet->GetPosition() + (plamet_kyori*-1 / 10));
			}

			return true;
	});*/


	//Bulletサーチ。
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		CVector3 kyori = b->GetPosition() - m_position;
		if (kyori.Length() < radius*1200) {
			b->SetMoveSpeed((kyori / 1)*-1);
		}
		return true;
	});
}

void BlackHole::Gravity()
{

}

void BlackHole::Count()
{
	timer++;
	if (timer >60) {
		Death();
	}
}

void BlackHole::Death()
{
	DeleteGO(this);
}

void BlackHole::Update()
{
	Move();
	//Count();
}
