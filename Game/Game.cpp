#include "stdafx.h"
#include "Game.h"
#include"field.h"
#include "tkEngine/light/tkDirectionLight.h"

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
		for (int i = 0; i < PadMaxKazu+1; i++)
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
	if (d_hako != nullptr) {
		DeleteGO(this);
	}
	DeleteGO(s_bar);
	DeleteGO(m_field);
	DeleteGO(m_G_Timer);
	DeleteGO(m_planet);
	//DeleteGO(s_kazu);
	DeleteGO(Pl1);
	DeleteGO(Pl2);
	DeleteGO(Pl3);
	DeleteGO(Pl4);
	QueryGOs<Planet>("planet", [&](Planet* obj)->bool
	{
		DeleteGO(obj);
		return true;
	});
}

bool Game::Start()
{
	s_kazu = FindGO<SansenKazu>("SansenKazu");
	PadMaxKazu = s_kazu->GetKazu();
	switch (PadMaxKazu)
	{
	case 1:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		Pl1 = NewGO<Draw_1P>(0, "1P");
		Pl1->SetPosition(0.0f, -300.0f);
		break;
	case 2:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		Pl1 = NewGO<Draw_1P>(0, "1P");
		Pl1->SetPosition(-150.0f, -300.0f);
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
		Pl2 = NewGO<Draw_2P>(0, "2P");
		Pl2->SetPosition(150.0f, -300.0f);
		break;
	case 3:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		Pl1 = NewGO<Draw_1P>(0, "1P");
		Pl1->SetPosition(-300.0f, -300.0f);
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
		Pl2 = NewGO<Draw_2P>(0, "2P");
		Pl2->SetPosition(0.0f, -300.0f);
		m_player[2] = NewGO<Player>(0, "Player2");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos);
		Pl3 = NewGO<Draw_3P>(0, "3P");
		Pl3->SetPosition(300.0f, -300.0f);
		break;
	case 4:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		Pl1 = NewGO<Draw_1P>(0, "1P");
		Pl1->SetPosition(-450.0f, -300.0f);
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
		Pl2 = NewGO<Draw_2P>(0, "2P");
		Pl2->SetPosition(-150.0f, -300.0f);
		m_player[2] = NewGO<Player>(0, "Player2");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos);
		Pl3 = NewGO<Draw_3P>(0, "3P");
		Pl3->SetPosition(150.0f, -300.0f);
		m_player[3] = NewGO<Player>(0, "Player3");
		m_player[3]->SetPadNum(3);
		m_player[3]->SetPositionX(P_pos*3);
		Pl4 = NewGO<Draw_4P>(0, "4P");
		Pl4->SetPosition(400.0f, -300.0f);
	break;
	}

	m_field = NewGO<field>(0);
	m_camera = NewGO<Camera>(0);
	m_enemy = NewGO<Enemy>(0,"Enemy");
	m_G_Timer = NewGO<GamenTimer>(0,"GamenTimer");
	//s_bar = NewGO<Sinka_Bar>(0, "Sinka_Bar");
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
	return true;
}

void Game::Update()
{
	if (GameMode == 0) {
		P_Ver();
		S_Pu();
		H_Pu();
		PlayerNum();
		CameraPos();
		Star_Life();
		PlStar_Life();
		Bullet_Life();
		//当たり判定表示
		dbg::SetDrawPhysicsCollisionEnable();
		if (Pad(0).IsPress(enButtonSelect) == true)
		{
			NewGO<Title_2>(0, "Title2");
			DeleteGO(this);
			if (s_kazu != nullptr)
			{
				DeleteGO(s_kazu);
			}
		}
	}
	else if (GameMode == 1)
	{
		GameMode = 0;
		NewGO<ResultGamen>(0, "ResultGamen");
		DeleteGO(this);
	}
}
//未使用
void Game::P_Ver()
{
}
//☆の出現。
void Game::S_Pu()
{
}
//箱の出現。
void Game::H_Pu()
{
	//if (m_player->GetDeathCount() == true && d_hako == nullptr)
	//{
	//	d_hako = NewGO<Drop_Hako>(0, "Drop_Hako");
	//	d_hako->SetSpwanCount(1);
	//}
}
//プレイヤーの人数
void Game::PlayerNum()
{

}
//カメラの動作。
void Game::CameraPos()
{
	switch (PadMaxKazu)
	{
	case 1:
		memory_position = m_player[0]->GetPosition();
		break;
	case 2:
		Tyuou = m_player[0]->GetPosition() / 2 + m_player[1]->GetPosition() / 2;
		memory_position = Tyuou;
		Kyori = m_player[0]->GetPosition() - m_player[1]->GetPosition();
		if (m_camera->GetKyori() > m_camera->MinCameraPos()/*1500*/) {
			if (Kyori.Length() < MinC_pos)
				m_camera->SetKyori(-15.0f);
		}
		if (m_camera->GetKyori() < m_camera->MaxCameraPos()/*4000*/) {
			if (Kyori.Length() > MaxC_pos) {
				m_camera->SetKyori(15.0f);
			}
		}
		break;
	case 3:
		Tyuou = m_player[0]->GetPosition() / 2 + m_player[1]->GetPosition() / 2 + m_player[2]->GetPosition()/2;
		memory_position = Tyuou;
		Kyori = m_player[0]->GetPosition() - m_player[1]->GetPosition() - m_player[2]->GetPosition();
		if (m_camera->GetKyori() > m_camera->MinCameraPos()/*1500*/) {
			if (Kyori.Length() < MinC_pos)
				m_camera->SetKyori(-15.0f);
		}
		if (m_camera->GetKyori() < m_camera->MaxCameraPos()/*3000*/) {
			if (Kyori.Length() > MaxC_pos) {
				m_camera->SetKyori(15.0f);
			}
		}
		break;
	case 4:
		Tyuou = m_player[0]->GetPosition() / 2 + m_player[1]->GetPosition() / 2 
			+ m_player[2]->GetPosition()/2 + m_player[3]->GetPosition()/2;
		memory_position = Tyuou;
		Kyori = m_player[0]->GetPosition() - m_player[1]->GetPosition() -
			m_player[2]->GetPosition() - m_player[3]->GetPosition();
		if (m_camera->GetKyori() > m_camera->MinCameraPos()/*1500*/) {
			if (Kyori.Length() < MinC_pos)
				m_camera->SetKyori(-15.0f);
		}
		if (m_camera->GetKyori() < m_camera->MaxCameraPos()/*3000*/) {
			if (Kyori.Length() > MaxC_pos) {
				m_camera->SetKyori(15.0f);
			}
		}
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
