#include "stdafx.h"
#include "Game.h"
#include"field.h"
#include "tkEngine/light/tkDirectionLight.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_field);
	DeleteGO(m_camera);
	DeleteGO(m_enemy);
	DeleteGO(m_G_Timer);
	DeleteGO(m_planet);
}
bool Game::Start()
{
	//ƒJƒƒ‰‚ğİ’èB
	/*MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });*/
	//MainCamera().SetNear(10.0f);
	//MainCamera().SetFar(10000.0f);
	//MainCamera().SetPosition({ 00.0f, 70.0f, 200.0f });
	//MainCamera().Update();
	m_player = NewGO<Player>(0, "Player");
	m_field = NewGO<field>(0);
	m_camera = NewGO<Camera>(0);
	m_enemy = NewGO<Enemy>(0);
	m_G_Timer = NewGO<GamenTimer>(0,"GamenTimer");
	m_planet = NewGO<Planet>(0);
	return true;
}

void Game::Update()
{
	//“–‚½‚è”»’è•\¦
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