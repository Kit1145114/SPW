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

	return true;
}

void BlackHole::Generate(CVector3 position, float magnification)
{
	
	//エフェクトを作成。
	prefab::CEffect* effect;
	effect = NewGO<prefab::CEffect>(0);
	BlackHole* bh =NewGO<BlackHole>(0, "BlackHole");
	bh->m_position = position;
	//エフェクトを再生。
	effect->Play(L"effect/BH.efk");
	CVector3 scale = CVector3::Zero;
	effect->SetScale(scale*magnification);
	effect->SetPosition(position);
}

void BlackHole::Move()
{
	//Playerサーチ
	//for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
	//	CVector3 player_kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
	//	if (player_kyori.Length() < radius*30) {
	//		Game::GetInstance()->m_player[i]->SetPosition(m_position);
	//			//Game::GetInstance()->m_player[i]->GetPosition() -(player_kyori/5));
	//			
	//	}
	//}
	//Plametサーチ
	for (int i = 0; i < Planetnumber_Num; i++) {
		CVector3 plamet_kyori = Game::GetInstance()->memoryPP[i]->GetPosition() - m_position;
		if (plamet_kyori.Length() < radius * 50) {
			Game::GetInstance()->memoryPP[i]->SetPosition(Game::GetInstance()->memoryPP[i]->GetPosition() + (plamet_kyori*-1 / 10));
		}
	}

	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		CVector3 kyori = b->GetPosition() - m_position;
		if (kyori.Length() < radius * 50) {
			b->SetPosition(b->GetPosition()-(kyori / 5));
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
	Count();
}
