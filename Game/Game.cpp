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
	DeleteGO(s_bar);
	DeleteGO(m_field);
	DeleteGO(m_G_Timer);
	DeleteGO(m_planet);
	QueryGOs<Planet>("planet", [&](Planet* obj)->bool
	{
		DeleteGO(obj);
		return true;
	});
}
bool Game::Start()
{
	//ÉJÉÅÉâÇê›íËÅB
	m_player = NewGO<Player>(0, "Player");
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
	P_Ver();
	S_Pu();
	//ìñÇΩÇËîªíËï\é¶
	dbg::SetDrawPhysicsCollisionEnable();


	if (GameMode == 0) {

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
		m_player_Rtype2 = NewGO<Player_RType2>(0, "Player_RType2");
		m_player_Rtype2->m_position = m_player->memory_position;
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