#pragma once
#include"BlackHole.h"
#include"GamenTimer.h"
#include"BigBlackHole.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
#include "Sun.h"

class BlackHole;
class field;
class Camera;
class Player;
class GamenTimer;
class Enemy;
class Title_2;
class ResultGamen;
class Planet;
class Player_RType2;
class Star;
class Draw_Player;
class SatelliteGene;
class RocketGene;
class MeteoGene;
class BigBlackHole;
class CountDown;
class TrepotHole;
class TrepotHole2;
class Sun;
class MoveSprite;
class WordRender;

class TerepotHole;

enum Planetnumber {
	Planetnumber_00,
	Planetnumber_01,
	Planetnumber_02,
	Planetnumber_03,
	Planetnumber_04,
	Planetnumber_05,
	Planetnumber_06,
	Planetnumber_07,
	Planetnumber_08,
	Planetnumber_09,
	Planetnumber_10,
	Planetnumber_11,
	Planetnumber_Num
};

const int PlKazu = 4;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void PlStar_Life();
	void Stage2();
	static Game* GetInstance();

	void SetGameMode(int a)
	{
		GameMode = a;
	}
	void SetSanSenkazu(int kazu)
	{
		SansenKazu = kazu;
	}
	int GetSansenKazu()
	{
		return SansenKazu;
	}
	//プレイヤーの弾が存在しているか

	 //弾の数
	void SetKazu(int a)
	{
		PB_Kazu += a;
	}
	//スターの数
	void SetStarCount(int kazu)
	{
		StarCount += kazu;
	}//スターが存在しているか
	void AddPlStarCount(int kazu)
	{
		PlStarCount += kazu;
	}
	//遊ぶステージを設定する
	void setStage(int _stage) {
		Stage = _stage;
	}
	//ブラックホールありかなしか。
	bool GetBHflag() {
		return BHflag;
	}
	int GetBHCount() {
		return BHCount;
	}
	void SetBHCount(int kazu) {
		BHCount += kazu;
	}
	bool GetSunflag() {
		return Sunflag;
	}
	SatelliteGene* getSatelliteGene() {
		return satelliteG;
	}

	RocketGene* getRocketGene() {
		return rocketG;
	}

	bool isWait() {
		return isWaitStart() || isWaitEnd();
	}
	
	bool isWaitStart() {
		return countdown != nullptr;
	}

	bool isWaitEnd() {
		return waitEnd;
	}

private:
	void CreateStage0();
	void CreateStage1();
	void CreateStage2();
	void CreateStage3();
	void CreateStage4();
	void CreateStage5();
public:
	Planet* memoryPP[Planetnumber_Num] = {};
	Player* m_player[PlKazu] = { nullptr };
	
	Star* m_star = nullptr;
	TerepotHole* tere[6]  = { nullptr };

private:
	static Game* m_instance;
	Enemy* enemy = nullptr;
	IGameObject* m_camera = nullptr;
	field* m_field = nullptr;
	GamenTimer* m_G_Timer = nullptr;
	SatelliteGene* satelliteG = nullptr;
	ResultGamen* result = nullptr;
	BigBlackHole* BBH = nullptr;
	MeteoGene* meteogene = nullptr;
	RocketGene* rocketG = nullptr;
	Sun* m_sun = nullptr;
	CountDown* countdown = nullptr;

	//勝利者演出用
	float waitEnd = 0.0f;
	MoveSprite* winnerSprite = nullptr;
	WordRender* winnerWord = nullptr;

	int trpotnumber = 0;
	prefab::CSoundSource* bgmSoundSource = nullptr;//BGM用のサウンドソース。
	
	int GameMode = 0;
	int Stage = 0;          //ステージ選択用
	int SansenKazu = 0;
	int StarCount  = 0;
	int PlStarCount = 0;
	float P_pos = 1800.0f;

	int PB_Kazu = 0;
	int timer = 0;
	bool PlS_Init = false;
	bool BHflag = false;     //ブラックホールのフラグ、trueだと発生しなくなる。
	int BHCount = 0;		 //ブラックホールをカウントする。
	bool Sunflag = false;    //太陽のフラグ、trueでプラネットの光方の調整など（太陽ステージだよ知らせるフラグ）。
	
};

