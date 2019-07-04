#include "stdafx.h"
#include "PlayerStar.h"


PlayerStar::PlayerStar()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/PlayerStar.cmo");
	m_scale = { 3.0f,3.0f,3.0f };
	m_skinModelRender->SetScale(m_scale);
	m_game = Game::GetInstance();
}


PlayerStar::~PlayerStar()
{
	DeleteGO(m_skinModelRender);
}

bool PlayerStar::Start()
{
	SansenKazu = m_game->GetSansenKazu();
	switch (SansenKazu)
	{
	case 1:
		m_player[0] = FindGO<Player>("Player");
		break;
	case 2:
		m_player[0] = FindGO<Player>("Player");
		m_player[1] = FindGO<Player>("Player1");
		break;
	case 3:
		m_player[0] = FindGO<Player>("Player");
		m_player[1] = FindGO<Player>("Player1");
		m_player[2] = FindGO<Player>("Player2");
		break;
	case 4:
		m_player[0] = FindGO<Player>("Player");
		m_player[1] = FindGO<Player>("Player1");
		m_player[2] = FindGO<Player>("Player2");
		m_player[3] = FindGO<Player>("Player3");
		break;
	}
	return true;
}

void PlayerStar::Update()
{
	Rotation();
	CVector3 kyori = Game::GetInstance()->m_player[Getplayer]->GetPosition() - m_position;
	float minkyori = 1600.0f;
	if (kyori.Length() > minkyori) {
		m_position += kyori / 11;
	}
	else {
		Death();
	}
	m_skinModelRender->SetPosition(m_position);
}
//™‚Ì‰ñ“]
void PlayerStar::Rotation()
{
	angle += 3.0f;
	m_rotation.SetRotationDeg(CVector3::AxisY, angle);
	m_rotation.SetRotationDeg(CVector3::AxisZ, angle);
	m_skinModelRender->SetRotation(m_rotation);
}
//™‚ÌŽ€–S
void PlayerStar::Death()
{
	DeleteGO(this);
}

void PlayerStar::Pop(int Death, int Get) {
	Getplayer = Get;
	m_position = Game::GetInstance()->m_player[Deathplayer = Death]->GetPosition();
	m_skinModelRender->SetPosition(m_position);
}
