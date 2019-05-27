#pragma once
#include"Game.h"
#include"Draw_Player.h"
#include"BlackHole.h"
#include "tkEngine/light/tkPointLight.h"
class Game;
class Bullet;
class Star;
class BlackHole;

class Planet : public IGameObject
{
public:
	Planet();
	~Planet();
	bool Start();
	void Update();
	void Move();
	void Size();
	void Death();
	void explosion();
	static bool Generate(int Reload,int Planetnum);
	void init(CVector3 position, prefab::CSkinModelRender* skinModelRender, float scale, prefab::CPointLight* cpointlight);
	void Light();
	CVector3 GetPosition() {
		return p_position;
	} 
	void SetPosition(CVector3 plpos)
	{
		p_position = plpos;
	}
	void SetMoveSpeed(CVector3 Speed) {
		p_position+= Speed;
	}
	float GetRadius() {
		return radius;
	}
protected:
	CCharacterController p_CharaCon;
	CVector3 p_position = CVector3::Zero;
	CVector3 scale = { 1.0f,1.0f,1.0f };
	CVector3 p_Size = { 1.0f,1.0f,1.0f };           //pop���̏����Â傫���Ȃ�Size�Ŏg���B
	CQuaternion p_rotation = CQuaternion::Identity;
	CVector3 randomspeed = CVector3::Zero;
	prefab::CSkinModelRender* p_skinModelRender = nullptr;
	prefab::CSoundSource* SoundSource = nullptr;//BGM�p�̃T�E���h�\�[�X�B
	prefab::CPointLight* p_Cpointlit = nullptr;//�����Ƃ炷���C�g�B
	Bullet* m_bullet = nullptr;
	Planet* hoge = nullptr;
	float radius = { 30.0f };  //��{�f���̔��a�B
	float PosMaxLimitx = 37000.0f;
	float PosMaxLimitz = 20000.0f;
	float angle = 0;           //��]�B
	float sizecount = 0.01f;    //pop���̏����Â傫���Ȃ�Size�Ŏg���B
	bool movecount = false;
	bool CountExplosion = false;
	bool repopflag = false;    //�|�b�v�������Ȃ葼�Ɣ��̂�h���̂Ɏg���t���O�B
	int myPlanetnumber =0;     //������Plamet�i���o�[�ۑ��p�B
	int time = 0;              //plamet���a�����Ă���̎��ԁB
};

