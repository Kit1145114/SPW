#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
	DeleteGO(m_skinModelRender);
}

bool Bullet::Start()
{
	m_game = FindGO<Game>("Game");
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Bulet.cmo");
	return true;
}

void Bullet::Update()
{
	m_position += m_moveSpeed;
	m_position.y = 100.0f;
	m_skinModelRender->SetPosition(m_position);

	m_timer++;
	if (m_timer == 100)
	{
		DeleteGO(this);
		m_game->SetKazu(-1);
	}
}

int Bullet::GetPB()
{
	switch (PB)
	{
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
	}
}