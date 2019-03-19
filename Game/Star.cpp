#include "stdafx.h"
#include "Star.h"


Star::Star()
{
}


Star::~Star()
{
	DeleteGO(m_skinModelRender);
}

bool Star::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Bulet.cmo");
	m_CharaCon.Init(30.0f, 100.0f, m_position);
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	return true;
}

void Star::Update()
{
	Hantei();
	m_timer++;
	if (m_timer == 300)
	{
		m_game->m_star = nullptr;
		DeleteGO(this);
		m_timer = 0;
	}
}
//™‚ÌŽæ“¾”»’èB
void Star::Hantei()
{
	if (m_game->m_player != nullptr)
	{
		CVector3 diff = m_player->GetPosition() - m_position;
		if (diff.Length() < 150.0f)
		{
			m_player->Ver = 1;
			m_game->Pver = 1;
			m_game->m_star = nullptr;
			DeleteGO(this);
		}
	}
	else if (m_game->m_player == nullptr)
	{

	}
}

void Star::Push()
{

}