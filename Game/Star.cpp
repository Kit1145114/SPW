#include "stdafx.h"
#include "Star.h"


Star::Star()
{
}


Star::~Star()
{
	(m_skinModelRender);
}

bool Star::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Bulet.cmo");
	m_game = FindGO<Game>("Game");
	return true;
}

void Star::Update()
{
	m_timer++;
	if (m_timer == 300)
	{
		DeleteGO(this);
		m_timer = 0;
	}
}


void Star::Push()
{

}