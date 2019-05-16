#include "stdafx.h"
#include "Meteo.h"


Meteo::Meteo()
{
	game = Game::GetInstance();
}


Meteo::~Meteo()
{
	DeleteGO(m_skinModelRender);
}

bool Meteo::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Inseki.cmo");
	scale = { 50.0f,5.0f,50.0f };
	m_skinModelRender->SetScale(scale);
	return true;
}

void Meteo::Update()
{
	Move();
	Hantei();
	timer++;
	//if (timer == 2500)
	//{
	//	Death();
	//}
}

void Meteo::Move()
{

	if (movecount == false) {

		randomspeed.x = Random().GetRandDouble() * 20000 * GameTime().GetFrameDeltaTime();
		randomspeed.z = Random().GetRandDouble() * 20000 * GameTime().GetFrameDeltaTime();
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.x *= -1;
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.z *= -1;

		movecount = true;
	}
	m_position += randomspeed;
	m_skinModelRender->SetPosition(m_position);
}

void Meteo::Death()
{
	DeleteGO(this);
}

void Meteo::Hantei()
{
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//�v���C���[�����G�Ȃ�U������߂�B
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			if (kyori.Length() < hantei
				&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
				Game::GetInstance()->m_player[i]->AddHP(-100);
				if (timer > 2) { //�o�n�o���͊��ق��Ă�����I
					Death();
				}
			}
		}
	}
	//�e�̔���
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* bullet)->bool
	{
		CVector3 b_kyori = bullet->GetPosition() - m_position;
		if (b_kyori.Length() < hantei) {
			bullet->Death();
		}
		return true;
	});
	if (m_position.x > PosMaxLimitx || m_position.x< -PosMaxLimitx
		|| m_position.z>PosMaxLimitz || m_position.z < -PosMaxLimitz) {
		Death();
	}
}

//void Meteo::InitTime()
//{
//const int Initkazu = 2;
//for (int i = 0; i < Initkazu; i++) {
//	Meteo* meteo = NewGO<Meteo>(0, "Meteo");
//	CVector3 hako;
//	do {
//		meteo->repopflag = false;
//		//�����_���|�b�v�B
//		float vx = Random().GetRandDouble();
//		float vz = Random().GetRandDouble();
//		hako.x = vx;
//		hako.z = vz;
//		if (Random().GetRandDouble() <= 0.5f)
//			hako.x *= -1;
//		if (Random().GetRandDouble() <= 0.5f)
//			hako.z *= -1;
//		//�����_����������ꏊ�̐����B
//		float PosLimitx = 30000.0f;
//		float PosLimitz = 20000.0f;
//		hako.x *= PosLimitx;
//		hako.z *= PosLimitz;
//
//		meteo->m_position = hako;
//	} while (meteo->repopflag == true);
//}
//return true;
//}

bool Meteo::Generate()
{
	Game* game = nullptr;
	game = Game::GetInstance();

	prefab::CSkinModelRender* m_skinModelRender;
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	CVector3 hako;
	//�����_���|�b�v�B
	float vx = Random().GetRandDouble();
	float vz = Random().GetRandDouble();

	hako.x = vx;
	hako.z = vz;
	if (Random().GetRandDouble() <= 0.5f)
		hako.x *= -1;
	if (Random().GetRandDouble() <= 0.5f)
		hako.z *= -1;

	//�����_����������ꏊ�̐����B
	float PosMaxLimitx = 35000.0f;
	float PosMaxLimitz = 20000.0f;
	hako.x *= PosMaxLimitx;
	hako.z *= PosMaxLimitz;

	//�f���̑傫�������_���B
	float v = 10.0f;//�Œ���̑傫����\�ߓ���Ă����B
	v += 50.0f * Random().GetRandDouble();
	float radius = { 30.0f };//	��{�f���̔��a
	radius *= v;
	bool isCreatePlanet = true;//�t���O

	for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
		CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - hako;
		if (kyori.Length() < radius + 5000.0f) {
			isCreatePlanet = false;
		}
	}

	if (isCreatePlanet) {
		Meteo* meteo = NewGO<Meteo>(0, "Meteo");
		meteo->m_position = hako;
		meteo->init(meteo->m_position,m_skinModelRender,v);
	}
	return true;
}

void Meteo::init(CVector3 position, prefab::CSkinModelRender* skinModelRender, float scale)
{
	//���̃|�W�V�����ۑ��B
	m_position = position;

	//�ۑ�
	CVector3 hoge = { 1.0f,1.0f,1.0f };
	hoge.x *= scale;
	hoge.z *= scale;
	hantei *= scale;

	m_skinModelRender = skinModelRender;
	m_skinModelRender->SetScale(hoge);
	m_skinModelRender->SetPosition(position);
}
