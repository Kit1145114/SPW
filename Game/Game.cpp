#include "stdafx.h"
#include "Game.h"
#include"field.h"
#include "tkEngine/light/tkDirectionLight.h"

Game::Game()
{
}


Game::~Game()
{
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
	if (m_player_Rtype2 != nullptr) {
		DeleteGO(m_player_Rtype2);
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
	DeleteGO(s_kazu);
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
		break;
	case 2:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		m_player[1] = NewGO<Player>(0, "Player");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
		break;
	case 3:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		m_player[1] = NewGO<Player>(0, "Player");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
		m_player[2] = NewGO<Player>(0, "Player");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos);
		break;
	case 4:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
		m_player[1] = NewGO<Player>(0, "Player");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
		m_player[2] = NewGO<Player>(0, "Player");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos);
		m_player[3] = NewGO<Player>(0, "Player");
		m_player[3]->SetPadNum(3);
		m_player[3]->SetPositionX(P_pos*3);
	break;
	}

	m_field = NewGO<field>(0);
	m_camera = NewGO<Camera>(0);
	m_enemy = NewGO<Enemy>(0,"Enemy");
	m_G_Timer = NewGO<GamenTimer>(0,"GamenTimer");
	s_bar = NewGO<Sinka_Bar>(0, "Sinka_Bar");
	Planet::Generate();
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
		//当たり判定表示
		dbg::SetDrawPhysicsCollisionEnable();
		//プレイヤーのポジ確保
		//switch (PadMaxKazu)
		//{
		//case 1:
		//	memory_position = ;
		//	break;
		//case 2:
		//	memory_position = Kyori;
		//	break;
		//case 3:
		//	memory_position = SyokiCamera;
		//	break;
		//case 4:
		//	memory_position = SyokiCamera;
		//	break;
		//}
	}
	else if (GameMode == 1)
	{
		GameMode = 0;
		NewGO<Title_2>(0, "Title_2");
		DeleteGO(this);
	}
}

void Game::P_Ver()
{
	if (Pver == 1 && m_player_Rtype2 == nullptr)
	{
		//m_player_Rtype2 = NewGO<Player_RType2>(0, "Player_RType2");
		//m_player_Rtype2->m_position = GetPosition();
	}
	else if (Pver == 2)
	{

	}
}

void Game::S_Pu()
{
	if (m_enemy == nullptr&& m_star == nullptr && starget == 0)
	{
		m_star = NewGO<Star>(0, "Star");
		starget = 1;
	}
	if (starget == 1)
	{

	}
	/*if (m_enemy == nullptr&& m_star == nullptr)
	{
		float S;
		S = Random().GetRandDouble;
		if (Random().GetRandDouble < 0.3f) {
			m_star = NewGO<Star>(0, "Star");
			m_star->m_position = m_enemy->m_position;
			m_star->m_position.x += 100;
		}
		else if (Random().GetRandDouble >= 0.3f && Random().GetRandDouble<0.7f)
		{
			m_star = NewGO<Star>(0, "Star");
			m_star = NewGO<Star>(0, "Star");
		}
		else if (Random().GetRandDouble >= 0.7f)
		{
			m_star = NewGO<Star>(0, "Star");
			m_star = NewGO<Star>(0, "Star");
			m_star = NewGO<Star>(0, "Star");
		}
	}*/
}

void Game::H_Pu()
{
	//if (m_player->GetDeathCount() == true && d_hako == nullptr)
	//{
	//	d_hako = NewGO<Drop_Hako>(0, "Drop_Hako");
	//	d_hako->SetSpwanCount(1);
	//}
}

void Game::PlayerNum()
{

}

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
				m_camera->SetKyori(-10.0f);
		}
		if (m_camera->GetKyori() < m_camera->MaxCameraPos()/*3000*/) {
			if (Kyori.Length() > MaxC_pos) {
				m_camera->SetKyori(10.0f);
			}
		}
		break;
	case 3:
		Tyuou = m_player[0]->GetPosition() / 2 + m_player[1]->GetPosition() / 2 - m_player[2]->GetPosition()/2;
		memory_position = Tyuou;
		Kyori = m_player[0]->GetPosition() - m_player[1]->GetPosition() - m_player[2]->GetPosition();
		if (m_camera->GetKyori() > m_camera->MinCameraPos()/*1500*/) {
			if (Kyori.Length() < MinC_pos)
				m_camera->SetKyori(-10.0f);
		}
		if (m_camera->GetKyori() < m_camera->MaxCameraPos()/*3000*/) {
			if (Kyori.Length() > MaxC_pos) {
				m_camera->SetKyori(10.0f);
			}
		}
		break;
	case 4:
		Tyuou = m_player[0]->GetPosition() / 2 + m_player[1]->GetPosition() / 2 
			- m_player[2]->GetPosition() - m_player[3]->GetPosition()/2;
		memory_position = Tyuou;
		Kyori = m_player[0]->GetPosition() - m_player[1]->GetPosition() -
			m_player[2]->GetPosition() - m_player[4]->GetPosition();
		if (m_camera->GetKyori() > m_camera->MinCameraPos()/*1500*/) {
			if (Kyori.Length() < MinC_pos)
				m_camera->SetKyori(-10.0f);
		}
		if (m_camera->GetKyori() < m_camera->MaxCameraPos()/*3000*/) {
			if (Kyori.Length() > MaxC_pos) {
				m_camera->SetKyori(10.0f);
			}
		}
	}

}