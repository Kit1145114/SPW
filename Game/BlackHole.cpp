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
	//�G�t�F�N�g���쐬�B
	prefab::CEffect* effect;
	effect = NewGO<prefab::CEffect>(0);
	//�G�t�F�N�g���Đ��B
	effect->Play(L"effect/BH.efk");
	effect->SetPosition(this->m_position);
	return true;
}

void BlackHole::Move()
{
	//Player�T�[�`
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		CVector3 player_kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
		if (player_kyori.Length() < radius*100) {
			Game::GetInstance()->m_player[i]->SetPosition(Game::GetInstance()->m_player[i]->GetPosition() -(player_kyori/10));
		}
	}
	
	//Plamet�T�[�`
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
