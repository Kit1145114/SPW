#pragma once
//#include "Game.h"
#include"Planet.h"

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
private:
	enum EState {
		eState_Low,		//�����ア�B
		eState_High,	//���������B
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
	float m_Revivaltimer = 8.0f;			//�������ԁB
	float m_emissionTimer = 0.0f;
	EState m_state = eState_Low;
	CVector3 emissionPointLigColorLow;		//�����ア���̃|�C���g���C�g�̃J���[�B
	CVector3 emissionPointLigColorHigh;		//�����������̃|�C���g���C�g�̃J���[�B
	CVector3 emissionColorLow;				//�����ア���̃G�~�b�V�����J���[�B
	CVector3 emissionColorHigh;				//�����������̃G�~�b�V�����J���[�B
	int SunHP = 5;
	float Size = 1.0f;
	bool SunRevivalFlag = false;
};

