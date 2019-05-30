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
	for (int i = 0; i < 4; i++) {
		if (P_spriteRender[i] != nullptr)
		{
			DeleteGO(P_spriteRender[i]);
		}
	}
	for (int i = 0; i < 4; i++) {
		if (G_spriteRender[i] != nullptr)
		{
			DeleteGO(G_spriteRender[i]);
		}
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
	switch (stage)
	{
	case 0:
		r_spriteRender = NewGO<prefab::CSpriteRender>(0);
		r_spriteRender->Init(L"sprite/Reslut1.dds", 1280.0f, 720.0f);
		break;
	default:
		r_spriteRender = NewGO<prefab::CSpriteRender>(0);
		r_spriteRender->Init(L"sprite/Reslut1.dds", 1280.0f, 720.0f);
		break;
	}
	switch (PadKazu)
	{
	case 1:
		//プレイヤー
		junban = 1;
		draw_P[0] = L"sprite/1Player.dds";
		m_player[0] = FindGO<Player>("Player");
		for (int i = 0; i < PadKazu; i++) {
			r_Draw[i] = NewGO<ResultDraw>(0);
			r_Draw[i]->SetPlayer(i + 1);
			P_spriteRender[i] = NewGO<prefab::CSpriteRender>(0);
			PS[i] = m_player[i]->GetStarCount();
		}
		P_spriteRender[0]->SetPosition(N1position);

		//ゲート
		for (int i = 0; i < PadKazu; i++)
		{
			G_spriteRender[i] = NewGO<prefab::CSpriteRender>(0);
			G_spriteRender[i]->Init(L"sprite/Gate.dds", GateSizeX,GateSizeY);
		}
		G_spriteRender[0]->SetPosition(G1position);
		break;
	case 2:
		//プレイヤー
		junban = 2;
		draw_P[0] = L"sprite/1Player.dds";
		m_player[0] = FindGO<Player>("Player");
		draw_P[1] = L"sprite/2Player.dds";
		m_player[1] = FindGO<Player>("Player1");
		for (int i = 0; i < PadKazu; i++) {
			r_Draw[i] = NewGO<ResultDraw>(0);
			r_Draw[i]->SetPlayer(i+1);
			P_spriteRender[i] = NewGO<prefab::CSpriteRender>(0);
			PS[i] = m_player[i]->GetStarCount();
		}
		P_spriteRender[0]->SetPosition(N1position);
		P_spriteRender[1]->SetPosition(N2position);
		//ゲート
		for (int i = 0; i < PadKazu; i++)
		{
			G_spriteRender[i] = NewGO<prefab::CSpriteRender>(0);
			G_spriteRender[i]->Init(L"sprite/Gate.dds", GateSizeX, GateSizeY);
		}
		G_spriteRender[0]->SetPosition(G1position);
		G_spriteRender[1]->SetPosition(G2position);
break;
	case 3:
		//プレイヤー
		junban =3;
		draw_P[0] = L"sprite/1Player.dds";
		m_player[0] = FindGO<Player>("Player");
		draw_P[1] = L"sprite/2Player.dds";
		m_player[1] = FindGO<Player>("Player1");
		draw_P[2] = L"sprite/3Player.dds";
		m_player[2] = FindGO<Player>("Player2");
		for (int i = 0; i < PadKazu; i++) {
			r_Draw[i] = NewGO<ResultDraw>(0);
			r_Draw[i]->SetPlayer(i + 1);
			P_spriteRender[i] = NewGO<prefab::CSpriteRender>(0);
			PS[i] = m_player[i]->GetStarCount();
		}
		P_spriteRender[0]->SetPosition(N1position);
		P_spriteRender[1]->SetPosition(N2position);
		P_spriteRender[2]->SetPosition(N3position);
		//ゲート
		for (int i = 0; i < PadKazu; i++)
		{
			G_spriteRender[i] = NewGO<prefab::CSpriteRender>(0);
			G_spriteRender[i]->Init(L"sprite/Gate.dds", GateSizeX, GateSizeY);
		}
		G_spriteRender[0]->SetPosition(G1position);
		G_spriteRender[1]->SetPosition(G2position);
		G_spriteRender[2]->SetPosition(G3position);
		break;
	case 4:
		//プレイヤー
		junban = 4;
		draw_P[0] = L"sprite/1Player.dds";
		m_player[0] = FindGO<Player>("Player");
		draw_P[1] = L"sprite/2Player.dds";
		m_player[1] = FindGO<Player>("Player1");
		draw_P[2] = L"sprite/3Player.dds";
		m_player[2] = FindGO<Player>("Player2");
		draw_P[3] = L"sprite/4Player.dds";
		m_player[3] = FindGO<Player>("Player3");
		for (int i = 0; i < PadKazu; i++) {
			r_Draw[i] = NewGO<ResultDraw>(0);
			r_Draw[i]->SetPlayer(i + 1);
			P_spriteRender[i] = NewGO<prefab::CSpriteRender>(0);
			PS[i] = m_player[i]->GetStarCount();
		}
		P_spriteRender[0]->SetPosition(N1position);
		P_spriteRender[1]->SetPosition(N2position);
		P_spriteRender[2]->SetPosition(N3position);
		P_spriteRender[3]->SetPosition(N4position);
		//ゲート
		for (int i = 0; i < PadKazu; i++)
		{
			G_spriteRender[i] = NewGO<prefab::CSpriteRender>(0);
			G_spriteRender[i]->Init(L"sprite/Gate.dds", GateSizeX, GateSizeY);
		}
		G_spriteRender[0]->SetPosition(G1position);
		G_spriteRender[1]->SetPosition(G2position);
		G_spriteRender[2]->SetPosition(G3position);
		G_spriteRender[3]->SetPosition(G4position);
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
	GateDraw();
}

void ResultGamen::Result()
{
	//int PNums[4];
	const wchar_t* p = nullptr;
	for (int i = 0; i < 4; i++) {
		PNums[i] = i;
	}

	for (int i = 0; i < PadKazu; i++) {
		for (int j = (PadKazu-1); j > i; j--) {
			if (PS[PNums[j - 1]] == PS[PNums[j]])
			{
				PNums[j] = PNums[j - 1];
			}
			 if (PS[PNums[j-1]] < PS[PNums[j]]) {
				int n = PNums[j];
				PNums[j]= PNums[j - 1];
				PNums[j - 1] = n;

				p = draw_P[j];			//プレイヤー
				draw_P[j] = draw_P[j - 1];
				draw_P[j - 1] = p;
			}
		}
	}

	//for (int i = 0; i < PadKazu; i++)
	//{
	//	if (PS[PNums[i]] == PS[PNums[i + 1]])
	//	{
	//		PS[i] = PS[i + 1];
	//	}
	//}

	for (int i = 0; i < PadKazu; i++) {
		r_Draw[i]->SetPlayer(PNums[i]+1);
		P_spriteRender[i]->Init(draw_P[i], 500.0f, 135.0f);
	}
}

void ResultGamen::GateDraw()
{
	switch (PadKazu)
	{
	case 1:
		timer++;
		//if (timer < Limit) {
		//	G1position.x += 10.0;
		//	G_spriteRender[0]->SetPosition(G1position);
		//	if (G1position.x > 220)
		//	{
		//		G1position.x = 200.0;
		//		G_spriteRender[0]->SetPosition(G1position);
		//	}
		//}
		if (timer > Limit) {
			if (junban == 1) {
				G1position.x += 10.0;
				if (G1position.x > change) {
					G1position.x = change;
					//timer = 0;
					junban = 0;
				}
				else
				{
					G_spriteRender[0]->SetPosition(G1position);
				}
			}
			break;
		}
	case 2:
		timer++;
		if (timer > Limit) {
			if (junban == 2) {
				G2position.x += 10.0;
				if (G2position.x > change) {
					G2position.x = change;
					//timer = 0;
					junban = 1;
				}
				else if (G2position.x < change)
				{
					G_spriteRender[1]->SetPosition(G2position);
				}
			}
			if (timer > Limit) {
				if (junban == 1) {
					G1position.x += 10.0;
					if (G1position.x > change) {
						G1position.x = change;
						//timer = 0;
						junban = 0;
					}
					else if (G1position.x < change)
					{
						G_spriteRender[0]->SetPosition(G1position);
					}
				}
			}
		}
		break;
	case 3:
		timer++;
		if (timer > Limit) {
			if (junban == 3) {
				G3position.x += 10.0;
				if (G3position.x > change) {
					G3position.x = change;
					//timer = 0;
					junban = 2;
				}
				else if (G3position.x < change)
				{
					G_spriteRender[2]->SetPosition(G3position);
				}
			}
			if (timer > Limit) {
				if (junban == 2) {
					G2position.x += 10.0;
					if (G2position.x > change) {
						G2position.x = change;
						//timer = 0;
						junban = 1;
					}
					else if (G2position.x < change)
					{
						G_spriteRender[1]->SetPosition(G2position);
					}
				}
			}
			if (timer > Limit) {
				if (junban == 1) {
					G1position.x += 10.0;
					if (G1position.x > change) {
						G1position.x = change;
						//timer = 0;
						junban = 0;
					}
					else if (G1position.x < change)
					{
						G_spriteRender[0]->SetPosition(G1position);
					}
				}
			}
		}
		break;
	case 4:
		timer++;
		if (timer > Limit) {
			if (junban == 4) {
				G4position.x += 10.0;
				if (G4position.x > change) {
					G4position.x = change;
					junban = 3;
				}
				else if (G4position.x < change)
				{
					G_spriteRender[3]->SetPosition(G4position);
				}
			}
			if (timer > Limit) {
				if (junban == 3) {
					G3position.x += 10.0;
					if (G3position.x > change) {
						G3position.x = change;
						junban = 2;
					}
					else if (G3position.x < change)
					{
						G_spriteRender[2]->SetPosition(G3position);
					}
				}
			}
			if (timer > Limit) {
				if (junban == 2) {
					G2position.x += 10.0;
					if (G2position.x > change) {
						G2position.x = change;
						junban = 1;
					}
					else if (G2position.x < change)
					{
						G_spriteRender[1]->SetPosition(G2position);
					}
				}
			}
			if (timer > Limit) {
				if (junban == 1) {
					G1position.x += 10.0;
					if (G1position.x > change) {
						G1position.x = change;
						junban = 0;
					}
					else if (G1position.x < change)
					{
						G_spriteRender[0]->SetPosition(G1position);
					}
				}
			}
		}
	}
}
