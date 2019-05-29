#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include"field.h"
#include"Player.h"
#include"MeteoGene.h"
#include"Enemy.h"
#include"ResultGamen.h";
//#include"Sinka_Bar.h"
#include "Stage1/SatelliteGene.h"
#include "Stage2/RocketGene.h"
#include "TerepotHole.h"
#include "Utility/CountDown.h"
#include "ResultCamera.h"
#include "Utility/MoveSprite.h"
#include "Utility/WordRender.h"

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
	if (enemy != nullptr) {
		DeleteGO(enemy);
	}
	if (m_star != nullptr) {
		DeleteGO(m_star);
	}
	if (BBH != nullptr) {
		DeleteGO("BBH");//Bigblackholeクラス
	}
	if (m_sun != nullptr) {
		DeleteGO("BigSun");
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
	DeleteGO(countdown);
	DeleteGO(winnerSprite);
	DeleteGO(winnerWord);
	DeleteGOs("テレポート");
	
	
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
	LightManager().SetAmbientLight({ 10.0f, 10.0f, 10.0f }); //ステージの明るさ。
}
//衛星。
void Game::CreateStage1() {
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
	satelliteG = NewGO<SatelliteGene>(0, "SatelliteGene");
	m_field = NewGO<field>(0);
	//BGM
	bgmSoundSource = NewGO<prefab::CSoundSource>(0);
	bgmSoundSource->Init(L"sound/ryunomai.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(1.0f);
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
	LightManager().SetAmbientLight({ 10.0f, 10.0f, 10.0f }); //ステージの明るさ。
}
//隕石。
void Game::CreateStage2() {

	meteogene = NewGO<MeteoGene>(0, "MeteoGene");
	rocketG = NewGO<RocketGene>(0, "RocketGene");
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
	bgmSoundSource->Init(L"sound/squall.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(1.0f);
	BHflag = true;//ブラックホールをOFFにする
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
	LightManager().SetAmbientLight({ 10.0f, 10.0f, 10.0f }); //ステージの明るさ。
}
//ビックブラックホール。
void Game::CreateStage3()
{
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
	BBH = NewGO<BigBlackHole>(0, "BBH");
	
	//BigBlackHole::Generate();
	BHflag = true;
	m_field = NewGO<field>(0);
	//BGM
	bgmSoundSource = NewGO<prefab::CSoundSource>(0);
	bgmSoundSource->Init(L"sound/boss.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(1.0f);
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
	LightManager().SetAmbientLight({ 10.0f, 10.0f, 10.0f }); //ステージの明るさ。
}
//太陽系。
void Game::CreateStage4()
{
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
	m_sun = NewGO<Sun>(0, "BigSun");
	Sunflag = true;
	//BGM
	bgmSoundSource = NewGO<prefab::CSoundSource>(0);
	bgmSoundSource->Init(L"sound/maounoshiro.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(1.0f);
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);

	LightManager().SetAmbientLight({ 0.8f, 0.8f, 0.8f });   //ステージの明るさ。
	//
	
}
//ワープ。
void Game::CreateStage5() {
	
	tere[0] = NewGO<TerepotHole>(0, "テレポート");
	tere[0]->SetPosi({ -30000,0,-12000 });
	tere[0]->SetFilePath(L"modelData/terepot.cmo");//緑
	tere[1] = NewGO<TerepotHole>(0, "テレポート");
	tere[1]->SetPosi({ -30000,0,4000 });
	tere[1]->SetFilePath(L"modelData/terepot2.cmo");//青
	tere[2] = NewGO<TerepotHole>(0, "テレポート");
	tere[2]->SetPosi({ -30000,0,18000 });
	tere[2]->SetFilePath(L"modelData/terepot3.cmo");//黄

	tere[3] = NewGO<TerepotHole>(0, "テレポート");
	tere[3]->SetPosi({ 30000,0,-12000 });
	tere[3]->SetFilePath(L"modelData/terepot.cmo");//緑
	tere[4] = NewGO<TerepotHole>(0, "テレポート");
	tere[4]->SetPosi({ 30000,0,4000 });
	tere[4]->SetFilePath(L"modelData/terepot2.cmo");//青
	tere[5] = NewGO<TerepotHole>(0, "テレポート");
	tere[5]->SetPosi({ 30000,0,18000 });
	tere[5]->SetFilePath(L"modelData/terepot3.cmo");//黄

	tere[0]->SetLinkTerepotHole(tere[3]);
	tere[1]->SetLinkTerepotHole(tere[4]);
	tere[2]->SetLinkTerepotHole(tere[5]);

	tere[3]->SetLinkTerepotHole(tere[0]);
	tere[4]->SetLinkTerepotHole(tere[1]);
	tere[5]->SetLinkTerepotHole(tere[2]);

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
	bgmSoundSource->Init(L"sound/bakumatsubukyoku_ikusa.wav");
	bgmSoundSource->Play(true);
	bgmSoundSource->SetVolume(1.0f);
	Planet::Generate(Planetnumber_Num, Planetnumber_Num);
	LightManager().SetAmbientLight({ 10.0f, 10.0f, 10.0f }); //ステージの明るさ。
}
bool Game::Start()
{
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
	case 4:
		CreateStage4();
		break;
	case 5:
		CreateStage5();
		break;
	default:
		CreateStage0();
	}
	m_camera = NewGO<Camera>(0, "Camera");
	m_G_Timer = NewGO<GamenTimer>(0, "GamenTimer");
	countdown = NewGO<CountDown>(2);
	countdown->setPP(&countdown);
	//enemy = NewGO<Enemy>(0, "Enemy");
	Fade::fadeOut();
	return true;
}

void Game::Update()
{
	if (GameMode == 0) {
		PlStar_Life();
		//当たり判定表示
		//dbg::SetDrawPhysicsCollisionEnable();
		if (Pad(0).IsPress(enButtonB) == true)
		{
			Fade::fadeIn([&]() {
				NewGO<Title_2>(0, "Title_2");
				DeleteGO(this);
			});
		}
	}
	else if (GameMode == 1)
	{
		Player* topPlayer[4] = {};
		int topNum = 1;//1位のプレイヤー数
		int star = -1;
		//1位を選別する。同点1位を考慮する。
		for (Player* p : m_player) {
			if (p) {
				if (p->GetStarCount() > star) {//今までのどのプレイヤーより星が多い場合
					topPlayer[0] = p;
					for (int i = 1; i < 4; i++) {
						topPlayer[i] = nullptr;//過去の同点1位はすべて抹消する
					}
					star = p->GetStarCount();
					topNum = 1;
				}else if(p->GetStarCount() == star) {//今までの星の最大数と同じ星数だった場合
					for (int i = 1; i < 4; i++) {
						if (topPlayer[i] == nullptr) {
							topPlayer[i] = p;//配列の頭からたどった時の最初のnullptrに追加する
							break;
						}
					}
					topNum++;
				}
			}
		}
		{//1位に勝者と設定するのと、同点1位の場合のワープを行う
			CVector3 pos = topPlayer[0]->GetPosition();
				for (int i = 0; i < topNum; i++) {
					topPlayer[i]->setWinner();
					if (i >= 1) {
						pos.x += 3000;
						topPlayer[i]->doTiesMove(pos);
					}
					prefab::CEffect* effect;
					effect = NewGO<prefab::CEffect>(0);
					//エフェクトを再生。
					effect->Play(L"effect/Paper.efk");
					effect->SetScale({ 1, 1, 1 });
					effect->SetPosition(pos);
				}
		}
		ResultCamera* camera = NewGO<ResultCamera>(0);
		camera->Init((const Player**)topPlayer, topNum,MainCamera().GetPosition(), MainCamera().GetTarget());
		DeleteGO(m_camera);
		m_camera = camera;
		waitEnd = 5.5f;

		winnerSprite = NewGO<MoveSprite>(2);
		winnerSprite->Init(L"sprite/winner.dds", 1300, 166);
		winnerSprite->setNowPos({ -1000, -230, 0 });
		winnerSprite->setTargetPos({ -400, -230, 0 });
		winnerSprite->setSpeed(3, 3);
		winnerWord = NewGO<WordRender>(3);
		CVector4 color;
		for (int i = 0; i < topNum; i++) {
			CVector4 pColor = topPlayer[i]->getColor();
			color.x += pColor.x;
			color.y += pColor.y;
			color.z += pColor.z;
			color.w += pColor.w;
		}
		color.x /= topNum;
		color.y /= topNum;
		color.z /= topNum;
		color.w /= topNum;
		winnerWord->Init(L"winner", winnerSprite, { 180,30,0 }, color, 3);
		GameMode = 2;
	} else if (GameMode == 2) {
		waitEnd -= GameTime().GetFrameDeltaTime();
		if (waitEnd > 4.5f) {
			bgmSoundSource->SetVolume((waitEnd - 4.5f));
		} else if (bgmSoundSource) {
			bgmSoundSource->Stop();
			DeleteGO(bgmSoundSource);
			bgmSoundSource = nullptr;
			prefab::CSoundSource* single = NewGO<prefab::CSoundSource>(0);
			single->Init(L"sound/GameEnd.wav");
			single->Play(false);
		}

		if (waitEnd <= 0 || Pad(0).IsTrigger(enButtonA)) {
			Fade::fadeIn([&]() {
				GameMode = 0;
				result = NewGO<ResultGamen>(0, "ResultGamen");
				result->SetSansenKazu(SansenKazu);
				result->SetStage(Stage);
				DeleteGO(this);
			});
		}
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
