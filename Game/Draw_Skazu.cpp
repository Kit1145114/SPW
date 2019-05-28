#include "stdafx.h"
#include "Draw_Skazu.h"


Draw_Skazu::Draw_Skazu()
{
}


Draw_Skazu::~Draw_Skazu()
{
	DeleteGO(Star);
	DeleteGO(Bullet);
}

bool Draw_Skazu::Start()
{
	Star = NewGO<prefab::CSpriteRender>(0);
	Star->Init(draw_S, 40.0f, 38.0f);
	/*Bullet = NewGO<prefab::CSpriteRender>(0);
	Bullet->Init(draw_B, 50.0f, 38.0f);*/
	return true;
}

void Draw_Skazu::Update()
{
	Star->SetPosition(Starposition);
	//Bullet->SetPosition(BulletPosition);
}

void Draw_Skazu::PostRender(CRenderContext& rc)
{
	wchar_t text[256];

	swprintf_s(text, L"    %d", star);
	m_font.Begin(rc);

	m_font.Draw(
		text,
		{ S_kazuposition },
		{Color},
		0.0f,
		1.0f
	);

	//swprintf_s(text, L"%d", bullet);
	//m_font.Draw(
	//	text,
	//	{ B_kazuposition },
	//	{ Color },
	//	0.0f,
	//	1.0f
	//	);
	m_font.End(rc);
}
