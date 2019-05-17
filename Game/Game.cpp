#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include"field.h"
#include"Player.h"
#include"MeteoGene.h"
//#include"Enemy.h"
#include"ResultGamen.h";
//#include"Sinka_Bar.h"
#include "Stage1/SatelliteGene.h"
#include "Stage1/RocketGene.h"

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
	//if (m_enemy != nullptr) {
	//	DeleteGO(m_enemy);
	//}
	if (m_star != nullptr) {
		DeleteGO(m_star);
	}
	DeleteGO(m_field);
	DeleteGO(m_G_Timer);
	DeleteGO(satelliteG);
	DeleteGO(rocketG);
	DeleteGO(meteogene);
	DeleteGO(bgmSoundSource);
	DeleteGOs("planet");//Planetクラス
	DeleteGOs("BlackHole");//BlackHoleクラス
	DeleteGOs("PlayerBullet");//Bulletクラス
	DeleteGOs("Star");//Starクラス
	DeleteGOs("Meteo");
	DeleteGO("そら");
}
//シンプル。
void Game::CreateStage0() {
	switch (SansenKazu) {
	case 4:
		m_player[3] = NewGO<Player>(0, "Player3");
		m_player[3]->SetPadNum(3);
		m_player[3]->SetPositionX(P_pos * 10);
		m_player[3]->SetPositionZ(P_pos *-5);
	case 3:
		m_player[2] = NewGO<Player>(0, "Player2");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos *-10);
		m_player[2]->SetPositionZ(P_pos *-5);
	case 2:
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos * 10);
		m_player[1]->SetPositionZ(P_pos * 5);
	case 1:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos *-10);
		m_player[0]->SetPositionZ(P_pos * 5);
	}
	m_field = NewGO<field>(0);
	//BGM
	bgmSoundSource = NewGO<prefab::CSoundSource>(0);
	bgmSoundSource->Init(L"sound/kaisen.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(1.0f);
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
}
//衛星。
void Game::CreateStage1() {
	switch (SansenKazu) {
	case 4:
		m_player[3] = NewGO<Player>(0, "Player3");
		m_player[3]->SetPadNum(3);
		m_player[3]->SetPositionX(P_pos * 3);
	case 3:
		m_player[2] = NewGO<Player>(0, "Player2");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos);
	case 2:
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
	case 1:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
	}
	satelliteG = NewGO<SatelliteGene>(0, "SatelliteGene");
	rocketG = NewGO<RocketGene>(0, "RocketGene");
	m_field = NewGO<field>(0);
	//BGM
	bgmSoundSource = NewGO<prefab::CSoundSource>(0);
	bgmSoundSource->Init(L"sound/kaisen.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(0.1f);
	BHflag = true;//ブラックホールをOFFにする
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
}
//隕石。
void Game::CreateStage2() {

	meteogene = NewGO<MeteoGene>(0, "MeteoGene");
	switch (SansenKazu) {
	case 4:
		m_player[3] = NewGO<Player>(0, "Player3");
		m_player[3]->SetPadNum(3);
		m_player[3]->SetPositionX(P_pos * 10);
		m_player[3]->SetPositionZ(P_pos *-5);
	case 3:
		m_player[2] = NewGO<Player>(0, "Player2");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos *-10);
		m_player[2]->SetPositionZ(P_pos *-5);
	case 2:
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos * 10);
		m_player[1]->SetPositionZ(P_pos * 5);
	case 1:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos *-10);
		m_player[0]->SetPositionZ(P_pos * 5);
	}
	m_field = NewGO<field>(0);
	//BGM
	bgmSoundSource = NewGO<prefab::CSoundSource>(0);
	bgmSoundSource->Init(L"sound/kaisen.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(0.1f);
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
}
//ビックブラックホール。
void Game::CreateStage3()
{
	switch (SansenKazu) {
	case 4:
		m_player[3] = NewGO<Player>(0, "Player3");
		m_player[3]->SetPadNum(3);
		m_player[3]->SetPositionX(P_pos * 3);
	case 3:
		m_player[2] = NewGO<Player>(0, "Player2");
		m_player[2]->SetPadNum(2);
		m_player[2]->SetPositionX(P_pos);
	case 2:
		m_player[1] = NewGO<Player>(0, "Player1");
		m_player[1]->SetPadNum(1);
		m_player[1]->SetPositionX(P_pos*-1);
	case 1:
		m_player[0] = NewGO<Player>(0, "Player");
		m_player[0]->SetPadNum(0);
		m_player[0]->SetPositionX(P_pos*-3);
	}
	//BBH = NewGO<BigBlackHole>(0, "bigblackhole");
	CVector3 position = { 10.0f, 10.0f,  10.0f };
	float BHsize = { 1000.0f };       //	基本惑星の半径。
	float Search = { 1000.0f };       //	BHの重力範囲の調整。
	float Limit  = { 1000.0f };       //   BHの重力（Ｇ）調整。
	BlackHole::Generate2(position, BHsize, Search, Limit);
	m_field = NewGO<field>(0);
	//BGM
	bgmSoundSource = NewGO<prefab::CSoundSource>(0);
	bgmSoundSource->Init(L"sound/kaisen.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(1.0f);
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
}
//ワープ。
void Game::CreateStage4()
{
}
//太陽系。
void Game::CreateStage5()
{
}

bool Game::Start()
{
	auto sky = NewGO<prefab::CSky>(0, "そら");
	sky->SetScale({ 50000.0f, 50000.0f, 50000.0f });
	sky->SetEmissionColor({ 0.1484f, 0.1484f, 0.398f });
	LightManager().SetAmbientLight({ 10.0f, 10.0f, 10.0f });
	//ステージ振り分け。
	switch (Stage) {
	case 0:
		CreateStage0();
		break;
	case 1:
		CreateStage1();
		break;
	case 2:
		CreateStage2();
		break;
	case 3:
		CreateStage3();
		break;
	default:
		CreateStage0();
	}
	m_camera = NewGO<Camera>(0, "Camera");
	m_G_Timer = NewGO<GamenTimer>(0, "GamenTimer");

	Fade::fadeOut();
	return true;
}

void Game::Update()
{
	if (GameMode == 0) {
		PlStar_Life();
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

void Game::Stage2()
{


}

Game* Game::GetInstance()
{
	return m_instance;
}
