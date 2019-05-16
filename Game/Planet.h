#pragma once
#include"Game.h"
#include"Draw_Player.h"
#include"BlackHole.h"
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
	void Death();
	void explosion();
	static bool Generate(int Reload,int Planetnum);
	void init(CVector3 position, prefab::CSkinModelRender* skinModelRender, float scale);

	CVector3 GetPosition() {
		return p_position;
	} 
	void SetPosition(CVector3 plpos)
	{
		p_position = plpos;
	}

	float GetRadius() {
		return radius;
	}
private:
	CCharacterController p_CharaCon;
	CVector3 p_position = CVector3::Zero;
	CVector3 p_moveSpeed = CVector3::Zero;
	CVector3 scale = { 1.0f,1.0f,1.0f };
	CQuaternion p_rotation = CQuaternion::Identity;
	CVector3 randomspeed = CVector3::Zero;
	prefab::CSkinModelRender* p_skinModelRender = nullptr;
	prefab::CSoundSource* SoundSource = nullptr;//BGM�p�̃T�E���h�\�[�X�B
	
	Bullet* m_bullet = nullptr;
	Planet* hoge = nullptr;
	float radius = { 30.0f };  //��{�f���̔��a
	float PosMaxLimitx = 37000.0f;
	float PosMaxLimitz = 20000.0f;
	bool movecount = false;
	bool CountExplosion = false;
	bool repopflag = false;    //�|�b�v�������Ȃ葼�Ɣ��̂�h���̂Ɏg���t���O
	int myPlanetnumber =0;     //������Plamet�i���o�[�ۑ��p
	int time = 0;              //plamet���a�����Ă���̎���
};

