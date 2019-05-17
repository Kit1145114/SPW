#include "stdafx.h"
#include "Sinka_Bar.h"


Sinka_Bar::Sinka_Bar()
{
}


Sinka_Bar::~Sinka_Bar()
{
	DeleteGO(sinka_bar);
	DeleteGO(sinka_gezi);
}

bool Sinka_Bar::Start()
{
	sinka_bar = NewGO<prefab::CSpriteRender>(0);
	sinka_gezi = NewGO<prefab::CSpriteRender>(0);
	sinka_bar->Init(L"sprite/Sinka_Bar.dds", 500.0f, 350.0f);
	sinka_bar->Init(L"sprite/midori.dds", 0.0f, 300.0f);
	sinka_bar->SetPosition(bar_position);
	sinka_gezi->SetPosition(gezi_position);
	m_game = Game::GetInstance();
	//switch (m_game->GetSansenKazu())
	//{
	//case 1:
	//	m_player[0] = FindGO<Player>("Player");
	//	break;
	//case 2:
	//	m_player[0] = FindGO<Player>("Player");
	//	m_player[1] = FindGO<Player>("Player1");
	//	break;
	//case 3:
	//	m_player[0] = FindGO<Player>("Player");
	//	m_player[1] = FindGO<Player>("Player1");
	//	m_player[2] = FindGO<Player>("Player2");
	//	break;
	//case 4:
	//	m_player[0] = FindGO<Player>("Player");
	//	m_player[1] = FindGO<Player>("Player1");
	//	m_player[2] = FindGO<Player>("Player2");
	//	m_player[3] = FindGO<Player>("Player3");
	//}
	return true;
}

void Sinka_Bar::Update()
{
	gezi = StarCount * gezi;
	sinka_bar->Init(L"sprite/midori.dds", gezi, 25.0f);
	sinka_bar->SetPosition(bar_position);
	sinka_gezi->SetPosition(gezi_position);
}
//void Sinka_Bar::PostRender(CRenderContext & renderContext)
//{
//	sinka_gezi.Draw();
//	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
//}
