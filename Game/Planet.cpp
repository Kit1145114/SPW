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
	m_player = FindGO<Player>("Game");
	return true;
}

void Planet::Generate() {
	Game* m_game = nullptr;
	m_game = FindGO<Game>("Game");
	
	//�f���̃��f�����O�w��B
	for (int i = 0,w = Planetnumber_00;i < Planetnumber_Num;i++,w++) {

		prefab::CSkinModelRender* P_skinModelRender;
		P_skinModelRender = NewGO<prefab::CSkinModelRender>(0);

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
		Planet* m_planet= NewGO<Planet>(0, "planet");
		
		m_game->memoryPP[i] = m_planet;

		//�����_���ȃ|�W�V�������B
		float vx = Random().GetRandDouble();
		float vz = Random().GetRandDouble();
		CVector3 hako;
		hako.x = vx;
		hako.z = vz;
		if(Random().GetRandDouble() <= 0.5f)
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
}
void Planet::init(CVector3 position, prefab::CSkinModelRender* skinModelRender)
{
	//���̐����B
	//���̃|�W�V�����B
	p_position = position;
	
	//�f���̑傫�������_���B
	float v = 50 * Random().GetRandDouble();
	scale.x *= v;
	scale.z *= v;
	r *= v;
	////�����蔻�蒲���B
	//CVector3 pa_position = position;
	//pa_position.y -= 300.0f;

	p_skinModelRender0 = skinModelRender;
	//p_CharaCon.Init(1.0f * 30 * scale.x,100.0f, pa_position);
	p_skinModelRender0->SetScale(scale);
	p_skinModelRender0->SetPosition(position);
}
void Planet::Move() {

}
void Planet::Death(){
	
	if (Pad(0).IsPress(enButtonSelect)) {
		DeleteGO(this);
	}
	for (int i = 0;i < Planetnumber_Num;i++) {
		//������r����f���������łȂ���΁B
		if (m_game->memoryPP[i] != this) {
			//2�_�Ԃ̋������v�Z����B
			CVector3 diff = m_game->memoryPP[i]->p_position - p_position;
			//���������a�ȉ��Ȃ�B
			if (diff.Length() < r) {
				DeleteGO(this);
			}
			else if (m_game->memoryPP[i]->r+r > diff.Length()) {
				DeleteGO(this);
			}
		}
	}
}
void Planet::Update() {
	
	Move();
	Death();
}