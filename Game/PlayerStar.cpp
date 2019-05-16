#include "stdafx.h"
#include "PlayerStar.h"


PlayerStar::PlayerStar()
{
}


PlayerStar::~PlayerStar()
{
	DeleteGO(m_skinModelRender);
}

bool PlayerStar::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/PlayerStar.cmo");
	m_scale = { 0.5f,0.5f,0.5f };
	m_skinModelRender->SetScale(m_scale);
	m_game = Game::GetInstance();
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
	//Move();
	m_timer++;
	if (m_timer == MaxTimer)
	{
		m_game->AddPlStarCount(-1);
		m_timer = ResetTimer;
		DeleteGO(this);
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
	//m_player->SetPLST(nullptr);
}

void PlayerStar::Pop(CVector3 position)
{
	m_position = position;
	m_skinModelRender->SetPosition(m_position);
};

void PlayerStar::Move()
{
	m_position.x += S_move;
	m_position.z += S_move;
	m_skinModelRender->SetPosition(m_position);
}