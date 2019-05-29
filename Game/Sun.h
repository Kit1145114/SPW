#pragma once
//#include "Game.h"
#include"Planet.h"

class Camera;

class Sun : public IGameObject
{
public:
	Sun();
	~Sun();
	bool Start();
	void Move();
	void Reflection();
	void Rotation();
	void Light();
	void Flare();
	void HPCount();
	void Revival();
	void Update();
	float GetSize()
	{
		return Size;
	}
private:
	enum EState {
		eState_Low,		//�����ア�B
		eState_High,	//���������B
		eState_death,
	};
	prefab::CSkinModelRender* p_skinModelRender = nullptr;
	prefab::CPointLight* p_Cpointlit = nullptr;
	CVector3 p_position = CVector3::Zero;
	CVector3 scale = { 1.0f,1.0f,1.0f };
	float radius = { 7500.0f };				 //��{�f���̔��a�B
	float Maxradius = 7500.0f;
	float SunSize = 250.0f;					//SetScale;
	float angle = 0;						//��]�B
	float G_limitar = { 50000.0f };			//Sun�̏d�́i�f�j�����B
	float nizyou = { 1000.0f };				//��撲���B
	float m_timer = 0.0f;
	float m_Deathtimer = 0.0f;				//���S���ԁB
	float m_Revivaltimer = 10.0f;			//�������ԁB
	float m_emissionTimer = 0.0f;
	EState m_state = eState_Low;
	CVector3 emissionPointLigColorLow;		//�����ア���̃|�C���g���C�g�̃J���[�B
	CVector3 emissionPointLigColorHigh;		//�����������̃|�C���g���C�g�̃J���[�B
	CVector3 emissionColorLow;				//�����ア���̃G�~�b�V�����J���[�B
	CVector3 emissionColorHigh;				//�����������̃G�~�b�V�����J���[�B
	prefab::CSoundSource* SoundSource = nullptr;//BGM�p�̃T�E���h�\�[�X�B
	prefab::CSoundSource* SoundSource2 = nullptr;//BGM�p�̃T�E���h�\�[�X�B
	prefab::CSoundSource* sunFlareSS = nullptr;	//���z�t���A�̎��̃T�E���h�B
	int SunHP = 200;
	float Size = 1.0f;
	bool SunRevivalFlag = false;

	Camera* camera = nullptr;
	bool Sountziki = false;
	
};

