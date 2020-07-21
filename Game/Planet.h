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
	/// <summary>
	/// �f������Ăɐ�������A����f���������Ń����_���w��Ăт����Ă���B
	/// </summary>
	/// <param name="Reload">����������f����</param>
	/// <param name="Planetnum">���X�|�[���̏ꍇ�����œn�����i���o�[�̘f�������</param>
	/// <returns></returns>
	static bool Generate(int Reload,int Planetnum);
	/// <summary>
	/// �f���̐���������B
	/// </summary>
	/// <param name="position">�ꏊ</param>
	/// <param name="skinModelRender">�X�L�����f���w��</param>
	/// <param name="scale">�傫��</param>
	/// <param name="cpointlight">���C�g</param>
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
	CVector3 p_position = CVector3::Zero;//�|�W�V�����B
	CVector3 scale = { 1.0f,1.0f,1.0f };//�T�C�Y�B
	CVector3 p_Size = { 1.0f,1.0f,1.0f };           //pop���̏����Â傫���Ȃ�Size�Ŏg���B
	CQuaternion p_rotation = CQuaternion::Identity;
	CVector3 randomspeed = CVector3::Zero;//�����_���X�s�[�h�B
	prefab::CSkinModelRender* p_skinModelRender = nullptr;
	prefab::CSoundSource* SoundSource = nullptr;//BGM�p�̃T�E���h�\�[�X�B
	prefab::CPointLight* p_Cpointlit = nullptr;//�����Ƃ炷���C�g�B
	Bullet* m_bullet = nullptr;
	Planet* hoge = nullptr;
	float radius = { 30.0f };  //��{�f���̔��a�B
	float PosMaxLimitx = 37000.0f;//�f���������ł���x�͈́A�t�B�[���h�ɍ��킹�Ē��߂����B
	float PosMaxLimitz = 20000.0f;//�f���������ł���y�͈́A�t�B�[���h�ɍ��킹�Ē��߂����B
	float angle = 0;           //��]�B
	float sizecount = 0.01f;    //pop���̏����Â傫���Ȃ�Size�Ŏg���B
	bool movecount = false;//�����_���Ɉړ�����t���O�Atrue�ɂ���ƈ��܂������_���Ɍ�����ς���B
	bool CountExplosion = false;//�����t���O�Atrue�Ŕ����G�t�F�N�g�ƌ��ʉ����o����Delete����B
	bool repopflag = false;    //�|�b�v�������Ȃ葼�Ɣ��̂�h���̂Ɏg���t���O�B
	int myPlanetnumber =0;     //������Plamet�i���o�[�ۑ��p�B
	int time = 0;              //plamet���a�����Ă���̎��ԁB
};

