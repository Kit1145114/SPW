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
	//�X�e�[�g�A���z�����̏�Ԃ��Ǘ�����B
	enum EState {
		eState_Low,		//�����ア�B
		eState_High,	//���������B
		eState_death,
	};
	prefab::CSkinModelRender* p_skinModelRender = nullptr;//�X�L�����f�������_���[�B
	prefab::CPointLight* p_Cpointlit = nullptr;//�|�C���g���C�g�B
	CVector3 p_position = CVector3::Zero;//�|�W�V�����B
	CVector3 scale = { 1.0f,1.0f,1.0f };//��{�T�C�Y�B
	float radius = { 7500.0f };				 //��{�f���̔��a�B
	float Maxradius = 7500.0f;				//�ő唼�a�B
	float SunSize = 250.0f;					//SetScale;
	float angle = 0;						//��]�B
	float G_limitar = { 50000.0f };			//Sun�̏d�́i�f�j�����B
	float nizyou = { 1000.0f };				//��撲���B
	float m_timer = 0.0f;					//�^�C�}�[�B
	float m_Deathtimer = 0.0f;				//���S���ԁB
	float m_Revivaltimer = 10.0f;			//�������ԁB
	float m_emissionTimer = 0.0f;			//�G�~�b�V�����^�C�}�[�B
	EState m_state = eState_Low;			//�����X�e�[�g�B
	CVector3 emissionPointLigColorLow;		//�����ア���̃|�C���g���C�g�̃J���[�B
	CVector3 emissionPointLigColorHigh;		//�����������̃|�C���g���C�g�̃J���[�B
	CVector3 emissionColorLow;				//�����ア���̃G�~�b�V�����J���[�B
	CVector3 emissionColorHigh;				//�����������̃G�~�b�V�����J���[�B
	prefab::CSoundSource* SoundSource = nullptr;//BGM�p�̃T�E���h�\�[�X�B
	prefab::CSoundSource* SoundSource2 = nullptr;//BGM�p�̃T�E���h�\�[�X�B
	prefab::CSoundSource* sunFlareSS = nullptr;	//���z�t���A�̎��̃T�E���h�B
	int SunHP = 90;							//HP�B
	float Size = 1.0f;						//�T�C�Y�B
	bool SunRevivalFlag = false;			//���z���S�t���O�Atrue�Ŏ��S���o�ցB
	Camera* camera = nullptr;				//�J�����B
	bool Sountziki = false;					//���C���̉��𔭐�������t���O
	
};

