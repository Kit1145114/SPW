#include "stdafx.h"
#include "ResultGamen.h"
#include "Fade.h"

ResultGamen::ResultGamen()
{
	Game* game = Game::GetInstance();
}


ResultGamen::~ResultGamen()
{
	DeleteGO(r_spriteRender);
	if (P1_spriteRender != nullptr)
	{
		DeleteGO(P1_spriteRender);
	}
	if (P2_spriteRender != nullptr)
	{
		DeleteGO(P2_spriteRender);
	}
	if (P3_spriteRender != nullptr)
	{
		DeleteGO(P3_spriteRender);
	}
	if (P4_spriteRender != nullptr)
	{
		DeleteGO(P4_spriteRender);
	}
	if (r_Draw[0] != nullptr)
	{
		DeleteGO(r_Draw[0]);
	}
	if (r_Draw[1] != nullptr)
	{
		DeleteGO(r_Draw[1]);
	}
	if (r_Draw[2] != nullptr)
	{
		DeleteGO(r_Draw[2]);
	}
	if (r_Draw[3] != nullptr)
	{
		DeleteGO(r_Draw[3]);
	}
}

bool ResultGamen::Start()
{
	r_spriteRender = NewGO<prefab::CSpriteRender>(0);
	r_spriteRender->Init(L"sprite/Reslut.dds", 1280.0f, 720.0f);
	switch (PadKazu)
	{
	case 1:
		m_player[0] = FindGO<Player>("Player");
		r_Draw[0] = NewGO<ResultDraw>(0);
		r_Draw[0]->SetPlayer(1);
		PS[0] = m_player[0]->GetStarCount();
		P1_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P1_spriteRender->Init(L"sprite/1Player.dds", 300.0f, 110.0f);
		P1_spriteRender->SetPosition(N1position);
		break;
	case 2:
		m_player[0] = FindGO<Player>("Player");
		PS[0] = m_player[0]->GetStarCount();
		r_Draw[0] = NewGO<ResultDraw>(0);
		r_Draw[0]->SetPlayer(1);
		m_player[1] = FindGO<Player>("Player1");
		r_Draw[1] = NewGO<ResultDraw>(0);
		PS[1] = m_player[1]->GetStarCount();
		r_Draw[1]->SetPlayer(2);
		P1_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P1_spriteRender->Init(L"sprite/1Player.dds", 300.0f, 110.0f);
		P1_spriteRender->SetPosition(N1position);
		P2_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P2_spriteRender->Init(L"sprite/2Player.dds", 300.0f, 110.0f);
		P2_spriteRender->SetPosition(N2position);
break;
	case 3:
		m_player[0] = FindGO<Player>("Player");
		PS[0] = m_player[0]->GetStarCount();
		r_Draw[0] = NewGO<ResultDraw>(0);
		r_Draw[0]->SetPlayer(1);
		m_player[1] = FindGO<Player>("Player1");
		PS[1] = m_player[1]->GetStarCount();
		r_Draw[1] = NewGO<ResultDraw>(0);
		r_Draw[1]->SetPlayer(2);
		m_player[2] = FindGO<Player>("Player2");
		PS[2] = m_player[2]->GetStarCount();
		r_Draw[2] = NewGO<ResultDraw>(0);
		r_Draw[2]->SetPlayer(3);
		P1_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P1_spriteRender->Init(L"sprite/1Player.dds", 300.0f, 110.0f);
		P1_spriteRender->SetPosition(N1position);
		P2_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P2_spriteRender->Init(L"sprite/2Player.dds", 300.0f, 110.0f);
		P2_spriteRender->SetPosition(N2position);
		P3_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P3_spriteRender->Init(L"sprite/3Player.dds", 300.0f, 110.0f);
		P3_spriteRender->SetPosition(N3position);
		break;
	case 4:
		m_player[0] = FindGO<Player>("Player");
		PS[0] = m_player[0]->GetStarCount();
		r_Draw[0] = NewGO<ResultDraw>(0);
		r_Draw[0]->SetPlayer(1);
		m_player[1] = FindGO<Player>("Player1");
		PS[1] = m_player[1]->GetStarCount();
		r_Draw[1] = NewGO<ResultDraw>(0);
		r_Draw[1]->SetPlayer(2);
		m_player[2] = FindGO<Player>("Player2");
		PS[2] = m_player[2]->GetStarCount();
		r_Draw[2] = NewGO<ResultDraw>(0);
		r_Draw[2]->SetPlayer(3);
		m_player[3] = FindGO<Player>("Player3");
		r_Draw[3] = NewGO<ResultDraw>(0);
		r_Draw[3]->SetPlayer(4);
		PS[3] = m_player[3]->GetStarCount();
		P1_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P1_spriteRender->Init(L"sprite/1Player.dds", 300.0f, 110.0f);
		P1_spriteRender->SetPosition(N1position);
		P2_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P2_spriteRender->Init(L"sprite/2Player.dds", 300.0f, 110.0f);
		P2_spriteRender->SetPosition(N2position);
		P3_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P3_spriteRender->Init(L"sprite/3Player.dds", 300.0f, 110.0f);
		P3_spriteRender->SetPosition(N3position);
		P4_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P4_spriteRender->Init(L"sprite/4Player.dds", 300.0f, 110.0f);
		P4_spriteRender->SetPosition(N4position);
		break;
	}
	Result();
	Fade::fadeOut();
	return true;
}

void ResultGamen::Update()
{
	if (Pad(0).IsPress(enButtonA) == true)
	{
		Fade::fadeIn([&]() {
			NewGO<Title_2>(0, "Title_2");
			DeleteGO(this);
		});
	}
}

void ResultGamen::Result()
{
	int PNums[4];
	for (int i = 0; i < 4; i++) {
		PNums[i] = i;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 3; j > i; j--) {
			if (PS[PNums[j-1]] < PS[PNums[j]]) {
				int n = PNums[j];
				PNums[j] = PNums[j - 1];
				PNums[j - 1] = n;
			}
		}
	}

	for (int i = 0; i < PadKazu; i++) {
		r_Draw[PNums[i]]->SetJuni(i+1);
	}
}