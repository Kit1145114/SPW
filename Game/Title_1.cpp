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
	m_spriteRender->Init(L"sprite/rogo4.dds", 1280.0f, 720.0f);
	return true;
}

void Title_1::Update()
{
	timer += GameTime().GetFrameDeltaTime();		
	if (Pad(0).IsTrigger(enButtonA)) {
		timer = Limit;
	}
	if (timer == Limit)
	{
		Fade::fadeIn([&]() {
			if (isSecondSprite) {
				DeleteGO(this);
				NewGO<Title_2>(0, "Title_2");
			} else {
				isSecondSprite = true;
				timer = 1.0f;
				m_spriteRender->Init(L"sprite/title1.dds", 1280.0f, 720.0f);
				Fade::fadeOut();
			}
		});
	}
}