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
	sinka_bar->Init(L"sprite/Sinka_Bar.dds", 200.0f, 35.0f);
	m_position.y = -300.0f;
	sinka_bar->SetPosition(m_position);
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("Player");
	//texture.CreateFromDDSTextureFromFile(L"sprite / Midori.dds");
	//sinka_gezi.Init(texture, 193.0f, 25.0f);
	//sinka_gezi = NewGO<prefab::CSpriteRender>(0);
	//sinka_gezi->Init(L"sprite/Midori.dds", 193.0f, 25.0f);
	//sinka_gezi->SetPosition(m_position);
	//sinka_gezi->SetPivot({ 0.0f, 0.5f });
	//m_scale = {1.0f,1.0f,1.0f};
	
	return true;
}

void Sinka_Bar::Update()
{
	sinka_gezi->Init(L"sprite/Midori.dds", 193.0f, 25.0f);
	//if (m_game->Pver == 1 && Gezi == false)
	//{
	//	sinka_gezi->Init(L"sprite/Midori.dds", 193.0f, 25.0f);
	//	sinka_gezi->SetPosition(m_position);
	//	Gezi = true;
	//}
	//else if (m_game->Pver == 2)
	//{

	//}
}

//void Sinka_Bar::PostRender(CRenderContext & renderContext)
//{
//	sinka_gezi.Draw();
//	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
//}
