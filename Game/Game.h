#pragma once
#include"BlackHole.h"
#include"GamenTimer.h"
#include"BigBlackHole.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

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
	SatelliteGene* getSatelliteGene() {
		return satelliteG;
	}

	RocketGene* getRocketGene() {
		return rocketG;
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
	Player* m_player[PlKazu] = {nullptr};
	Star* m_star = nullptr;
private:
	static Game* m_instance;
	Enemy* enemy = nullptr;
	Camera* m_camera = nullptr;
	field* m_field = nullptr;
	GamenTimer* m_G_Timer = nullptr;
	SatelliteGene* satelliteG = nullptr;
	BigBlackHole* BBH = nullptr;
	MeteoGene* meteogene = nullptr;
	RocketGene* rocketG = nullptr;
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
   	//CVector3 BHpos1 = { 0.0f , 0.0f, 5000.0f };
	//CVector3 BHsca1 = { 1000.0f,0.0f,5.0f };
};

