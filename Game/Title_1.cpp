#include "stdafx.h"
#include "Title_1.h"
#include "Fade.h"

Title_1::Title_1()
{
}


Title_1::~Title_1()
{
	DeleteGO(m_spriteRender);
}

bool Title_1::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/title1.dds", 1280.0f, 720.0f);
	return true;
}

void Title_1::Update()
{
	m_timer++;
	if (Pad(0).IsTrigger(enButtonA)) {
		m_timer = Limit;
	}
	if (m_timer == Limit)
	{
		Fade::fadeIn([&]() {
			if (isSecondSprite) {
				DeleteGO(this);
				NewGO<Title_2>(0, "Title_2");
			} else {
				isSecondSprite = true;
				m_timer = -80;
				m_spriteRender->Init(L"sprite/rogo4.dds", 1280.0f, 720.0f);
				Fade::fadeOut();
			}
		});
	}
}