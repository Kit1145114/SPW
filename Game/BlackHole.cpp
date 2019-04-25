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
	//m_game = FindGO<Game>("Game");
	switch (m_game->GetPadKazu())
	{
	case 1:
		m_player[0] = FindGO<Player>("Player");
		Pl1 = FindGO<Draw_1P>("1P");
		break;
	case 2:
		m_player[0] = FindGO<Player>("Player");
		m_player[1] = FindGO<Player>("Player1");
		Pl1 = FindGO<Draw_1P>("1P");
		Pl2 = FindGO<Draw_2P>("2P");
		break;
	case 3:
		m_player[0] = FindGO<Player>("Player");
		m_player[1] = FindGO<Player>("Player1");
		m_player[2] = FindGO<Player>("Player2");
		Pl1 = FindGO<Draw_1P>("1P");
		Pl2 = FindGO<Draw_2P>("2P");
		Pl3 = FindGO<Draw_3P>("3P");
		break;
	case 4:
		m_player[0] = FindGO<Player>("Player");
		m_player[1] = FindGO<Player>("Player1");
		m_player[2] = FindGO<Player>("Player2");
		m_player[3] = FindGO<Player>("Player3");
		Pl1 = FindGO<Draw_1P>("1P");
		Pl2 = FindGO<Draw_2P>("2P");
		Pl3 = FindGO<Draw_3P>("3P");
		Pl4 = FindGO<Draw_4P>("4P");
		break;
	}
	//エフェクトを作成。
	prefab::CEffect* effect;
	effect = NewGO<prefab::CEffect>(0);
	//エフェクトを再生。
	effect->Play(L"effect/kari_BH.efk");
	effect->SetPosition(this->m_position);


	return true;
}

void BlackHole::Move()
{
	//Playerサーチ
	for (int i = 0; i < m_game->GetPadKazu(); i++) {
		CVector3 player_kyori = m_player[i]->GetPosition() - m_position;
		if (player_kyori.Length() < radius*100) {
			m_player[i]->SetPosition(m_player[i]->GetPosition() -(player_kyori/10));
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
