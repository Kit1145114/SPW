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
		DeleteGO(m_player);
	}
	DeleteGO(m_field);
	if (m_camera != nullptr) {
		DeleteGO(m_camera);
	}
	if (m_player_Rtype2 != nullptr) {
		DeleteGO(m_player_Rtype2);
	}
	DeleteGO(m_enemy);
	DeleteGO(m_G_Timer);
	DeleteGO(m_planet);
}
bool Game::Start()
{
	//ÉJÉÅÉâÇê›íËÅB
	m_player = NewGO<Player>(0, "Player");
	m_field = NewGO<field>(0);
	m_camera = NewGO<Camera>(0);
	m_enemy = NewGO<Enemy>(0);
	m_G_Timer = NewGO<GamenTimer>(0,"GamenTimer");
	//m_planet = NewGO<Planet>(0);
	//Planet::Generate();
	return true;
}

void Game::Update()
{
	if (Pad(0).IsPress(enButtonB)&&m_player != nullptr)
	{
		NewGO<Player_RType2>(0,"Player_RType2");
		DeleteGO(m_player);
		DeleteGO(m_camera);
		m_player = nullptr;
		m_camera = nullptr;
	}
	if (m_player == nullptr)
	{
		m_player_Rtype2 = FindGO<Player_RType2>("Player_RType2");
	}
	//ìñÇΩÇËîªíËï\é¶
	dbg::SetDrawPhysicsCollisionEnable();
	if (GameMode == 0) {

	}
	else if (GameMode == 1)
	{
		GameMode = 0;
		NewGO<Title_2>(0, "TItle_2");
		DeleteGO(this);
	}
}