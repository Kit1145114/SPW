#include "stdafx.h"
#include "Planet.h"
#include "Game.h"
#include <string>

Planet::Planet()
{
}


Planet::~Planet()
{
	DeleteGO(p_skinModelRender0);
}
bool Planet::Start() {
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("Player");

	

	return true;
}

void Planet::Generate(int Reload) {
	
	Game* m_game = nullptr;
	m_game = FindGO<Game>("Game");
	//Planetnumber_Num���̍쐬
	for (int i = 0, w = Planetnumber_00;i < Reload;i++, w++) {
		//���GetPlanetAgeinCount����11���o������悤��
		//if (m_game->GetPlanetAgeinCount() < Planetnumber_Num) {
			//m_game->SetPlanetAgeinCount(+1);
			prefab::CSkinModelRender* P_skinModelRender;
			P_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
			
			//�f���̃��f�����O�w��B
			switch (w) {
			case Planetnumber_00:
				P_skinModelRender->Init(L"modelData/planet0fire.cmo");
				break;
			case Planetnumber_01:
				P_skinModelRender->Init(L"modelData/planet01.cmo");
				break;
			case Planetnumber_02:
				P_skinModelRender->Init(L"modelData/planet02.cmo");
				break;
			case Planetnumber_03:
				P_skinModelRender->Init(L"modelData/planet03.cmo");
				break;
			case Planetnumber_04:
				P_skinModelRender->Init(L"modelData/planet04.cmo");
				break;
			case Planetnumber_05:
				P_skinModelRender->Init(L"modelData/planet05.cmo");
				break;
			case Planetnumber_06:
				P_skinModelRender->Init(L"modelData/planet06.cmo");
				break;
			case Planetnumber_07:
				P_skinModelRender->Init(L"modelData/planet07.cmo");
				break;
			case Planetnumber_08:
				P_skinModelRender->Init(L"modelData/planet08.cmo");
				break;
			case Planetnumber_09:
				P_skinModelRender->Init(L"modelData/planet09.cmo");
				break;
			case Planetnumber_10:
				P_skinModelRender->Init(L"modelData/planet_10.cmo");
				break;
			case Planetnumber_11:
				P_skinModelRender->Init(L"modelData/planet11.cmo");
				break;
			default:w = Planetnumber_00;
			}
			Planet* m_planet = NewGO<Planet>(0, "planet");
			m_game->memoryPP[i] = m_planet;
			m_planet->myPlanetnumber = w;    //������Plamet�i���o�[�ۑ�

			//�����_���|�b�v�B
			float vx = Random().GetRandDouble();
			float vz = Random().GetRandDouble();
			CVector3 hako;
			hako.x = vx;
			hako.z = vz;
			if (Random().GetRandDouble() <= 0.5f)
				hako.x *= -1;
			if (Random().GetRandDouble() <= 0.5f)
				hako.z *= -1;

			//�����_����������ꏊ�̐����B
			float PosLimitx = 20000.0f;
			float PosLimitz = 10000.0f;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			m_planet->p_position = hako;

			m_planet->init(m_planet->p_position, P_skinModelRender);
		}
	//}
}
//���̐����B
void Planet::init(CVector3 position, prefab::CSkinModelRender* skinModelRender)
{
	//���̃|�W�V�����B
	p_position = position;
	
	//�f���̑傫�������_���B
	float v = 50 * Random().GetRandDouble();
	scale.x *= v;
	scale.z *= v;
	radius *= v;

	p_skinModelRender0 = skinModelRender;
	p_skinModelRender0->SetScale(scale);
	p_skinModelRender0->SetPosition(position);
}
void Planet::Move() {
	//�����_���ړ��B
	
	if (movecount == false) {
		
		randomspeed.x = Random().GetRandDouble() * 100 * GameTime().GetFrameDeltaTime();
		randomspeed.z = Random().GetRandDouble() * 100 * GameTime().GetFrameDeltaTime();
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.x *= -1;
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.z *= -1;
		
		movecount = true;
	}
	p_position += randomspeed;
	p_skinModelRender0->SetPosition(p_position);
}
//�h�J�[���i�����j�����˂��A�ԉ΂����A�A�A�B
void Planet::explosion()
{
	Star* m_star = NewGO<Star>(0, "star");
	m_star->Pop(this->p_position);
	Generate(1); //�V���Șf���𐶐��i�����̃i���o�[�̘f�����j
	DeleteGO(this);
	//m_game->SetPlanetAgeinCount(-1);
}
//�f�����S����B
void Planet::Death(){
	
	//�������I����f���I�I�v���C���[�j�󂷂����I�I�B
	m_sansenkazu = FindGO<SansenKazu>("SansenKazu");
	for (int i = 0;i < m_sansenkazu->GetKazu();i++) {
		CVector3 p_kyori = m_game->GetPosition() - p_position;
		if (p_kyori.Length() < radius
			&& m_game->m_player[i]->GetDeathCount() == false) {
			m_game->m_player[i]->Death();
		}
	}
	//�e�����͊��ق��Ă��������B
	if (m_player->GetShortCount()==true) {
		m_bullet = FindGO<Bullet>("PlayerBullet");
		CVector3 b_kyori = m_bullet->GetPosition() - p_position;
		if (b_kyori.Length() < radius) {
			explosion();
		}
	}

	//�f�����m�̋�������B
	for (int i = 0;i < Planetnumber_Num;i++) {
		//������r����f���������łȂ���΁B
		if (m_game->memoryPP[i] != this) {
			//2�_�Ԃ̋������v�Z����B
			CVector3 diff = m_game->memoryPP[i]->p_position - p_position;
			//���������a�ȉ��Ȃ�B
			if (diff.Length() < radius) {
				explosion();
			}
			else if (m_game->memoryPP[i]->radius + radius > diff.Length()) {
				explosion();
			}
		}
	}
}

void Planet::Update() {
	
	Move();
	Death();
}