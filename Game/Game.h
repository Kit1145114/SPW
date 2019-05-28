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
	//�v���C���[�̒e�����݂��Ă��邩

	 //�e�̐�
	void SetKazu(int a)
	{
		PB_Kazu += a;
	}
	//�X�^�[�̐�
	void SetStarCount(int kazu)
	{
		StarCount += kazu;
	}//�X�^�[�����݂��Ă��邩
	void AddPlStarCount(int kazu)
	{
		PlStarCount += kazu;
	}
	//�V�ԃX�e�[�W��ݒ肷��
	void setStage(int _stage) {
		Stage = _stage;
	}
	//�u���b�N�z�[�����肩�Ȃ����B
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

	//�����҉��o�p
	float waitEnd = 0.0f;
	MoveSprite* winnerSprite = nullptr;
	WordRender* winnerWord = nullptr;

	int trpotnumber = 0;
	prefab::CSoundSource* bgmSoundSource = nullptr;//BGM�p�̃T�E���h�\�[�X�B
	
	int GameMode = 0;
	int Stage = 0;          //�X�e�[�W�I��p
	int SansenKazu = 0;
	int StarCount  = 0;
	int PlStarCount = 0;
	float P_pos = 1800.0f;

	int PB_Kazu = 0;
	int timer = 0;
	bool PlS_Init = false;
	bool BHflag = false;     //�u���b�N�z�[���̃t���O�Atrue���Ɣ������Ȃ��Ȃ�B
	int BHCount = 0;		 //�u���b�N�z�[�����J�E���g����B
	bool Sunflag = false;    //���z�̃t���O�Atrue�Ńv���l�b�g�̌����̒����Ȃǁi���z�X�e�[�W����m�点��t���O�j�B
	
};

