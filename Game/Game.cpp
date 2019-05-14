#include "stdafx.h"
#include "Game.h"
#include"field.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"

Game* Game::m_instance = nullptr;

Game::Game()
{
	if (m_instance != nullptr)
	{
		std::abort();
	}
	m_instance = this;
}

Game::~Game()
{
	m_instance = nullptr;
	if (m_player != nullptr) {
		for (int i = 0; i < SansenKazu; i++)
		{
			DeleteGO(m_player[i]);
		}
	}
	if (m_camera != nullptr) {
		DeleteGO(m_camera);
	}
	if (m_enemy != nullptr) {
		DeleteGO(m_enemy);
	}
	if (m_star != nullptr) {
		DeleteGO(m_star);
	}
	DeleteGO(s_bar);
	DeleteGO(m_field);
	DeleteGO(m_G_Timer);
	DeleteGO(m_planet);
	DeleteGO(bgmSoundSource);
	DeleteGO(Pl1);
	DeleteGOs("planet");//Planetクラス
	DeleteGOs("BlackHole");//BlackHoleクラス
	DeleteGOs("PlayerBullet");//Bulletクラス
	DeleteGOs("Star");//Starクラス
}

bool Game::Start()
{
	switch (SansenKazu)
	{
	case 1:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		break;
	case 2:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
		break;
	case 3:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
		m_player[2] = NewGO<Player>(0, "Player2");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos);
		break;
	case 4:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
		m_player[2] = NewGO<Player>(0, "Player2");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos);
		m_player[3] = NewGO<Player>(0, "Player3");
		m_player[3]->SetPadNum(3);
		m_player[3]->SetPositionX(P_pos*3);
	break;
	}
	m_field = NewGO<field>(0);
	m_camera = NewGO<Camera>(0,"Camera");
	m_G_Timer = NewGO<GamenTimer>(0,"GamenTimer");
	//BGM
	bgmSoundSource = NewGO<prefab::CSoundSource>(0);
	bgmSoundSource->Init(L"sound/kaisen.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(1.0f);
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
	Fade::fadeOut();
	return true;
}

void Game::Update()
{
	if (GameMode == 0) {
		Star_Life();
		PlStar_Life();
		Bullet_Life();
		//当たり判定表示
		//dbg::SetDrawPhysicsCollisionEnable();
		if (Pad(0).IsPress(enButtonSelect) == true)
		{
			Fade::fadeIn([&]() {
				NewGO<Title_2>(0, "Title_2");
				DeleteGO(this);
			});
		}
	}
	else if (GameMode == 1)
	{
		//TODO ネット対戦用に変える必要がある
		Fade::fadeIn([&]() {
			GameMode = 0;
			NewGO<ResultGamen>(0, "ResultGamen")->SetSansenKazu(SansenKazu);
			DeleteGO(this);
		});
	}
}

void Game::Star_Life()
{
	if (StarCount > Star0)
	{
		S_Init = true;
	}
	else if (StarCount == Star0)
	{
		S_Init = false;
	}
}

void Game::PlStar_Life()
{
	if (PlStarCount > 0)
	{
		PlS_Init = true;
	}
	else if (PlStarCount == 0)
	{
		PlS_Init = false;
	}
}

void Game::Bullet_Life()
{
	if (PB_Kazu > 0)
	{
		PBullet_Init = true;
	}
	else if (PB_Kazu == 0)
	{
		PBullet_Init = false;
	}
}

Game* Game::GetInstance()
{
	return m_instance;
}
