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
	effect->SetPosition(this->m_position);
	return true;
}

void BlackHole::Move()
{
	//Playerサーチ
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		CVector3 player_kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
		if (player_kyori.Length() < radius*100) {
			Game::GetInstance()->m_player[i]->SetPosition(Game::GetInstance()->m_player[i]->GetPosition() -(player_kyori/10));
		}
	}
	
	//Plametサーチ
	/*for (int i = 0; i < Planetnumber_Num; i++) {
		CVector3 plamet_kyori =  - m_position;
		if (plamet_kyori.Length() < radius * 100) {
			m_player[i]->SetPosition(m_player[i]->GetPosition() + (p_kyori*-1 / 10));
		}
	}*/
}

void BlackHole::Gravity()
{

}

void BlackHole::Update()
{
	Move();
}
