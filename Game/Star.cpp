#include "stdafx.h"
#include "Star.h"


Star::Star()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/star.cmo");
	m_scale = { 8.0f, 8.0, 8.0f };
	m_skinModelRender->SetScale(m_scale);
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
}


Star::~Star()
{
	DeleteGO(m_skinModelRender);
}



void Star::Update()
{
	Rotation();
	Push();
	m_timer++;
	if (m_timer == Limit)
	{
		m_game->m_star = nullptr;
		m_game->SetStarCount(-1);
		m_timer = 0;
		Death();
	}
}

//™‚ÌoŒ»
void Star::Pop(CVector3 position,CVector3 scale)
{
	m_position = position;
	m_scale = scale;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
};

void Star::Push()
{
	m_skinModelRender->SetPosition(m_position);
}

void Star::Rotation()
{
	angle += 3.0f;
	m_rotation.SetRotationDeg(CVector3::AxisY, angle);
	m_skinModelRender->SetRotation(m_rotation);
}

void Star::Death()
{
	DeleteGO(this);
}

