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
	CVector3 scale = { 1.0f,1.0f,1.0f };
	effect->SetScale(scale/**radius*/);
	effect->SetPosition(m_position);
	return true;
}

void BlackHole::Generate(CVector3 position, float magnification)
{
	//�|�W�V�����̕ۑ��B
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	bh->m_position = position;
	bh->radius *= magnification;
	////�G�t�F�N�g���쐬�B
	//prefab::CEffect* effect;
	//effect = NewGO<prefab::CEffect>(0);
	////�G�t�F�N�g���Đ��B
	//effect->Play(L"effect/BH.efk");
	//CVector3 scale = { 10.0f,10.0f,10.0f };
	//effect->SetScale(scale*magnification);
	//effect->SetPosition(position);
}

void BlackHole::Move()
{
	//Player�T�[�`�B
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		CVector3 player_kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
		if (player_kyori.Length() < radius) {
			Game::GetInstance()->m_player[i]->SetPosition(m_position);
				//Game::GetInstance()->m_player[i]->GetPosition() -(player_kyori/5));
				
		}
	}
	//Plamet�T�[�`�B
	for (int i = 0; i < Planetnumber_Num; i++) {
		CVector3 plamet_kyori = Game::GetInstance()->memoryPP[i]->GetPosition() - m_position;
		if (plamet_kyori.Length() < radius) {
			Game::GetInstance()->memoryPP[i]->SetPosition(Game::GetInstance()->memoryPP[i]->GetPosition() + (plamet_kyori*-1 / 10));
		}
	}
	//Bullet�T�[�`�B
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		CVector3 kyori = b->GetPosition() - m_position;
		if (kyori.Length() < radius) {
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
	//Count();
}
