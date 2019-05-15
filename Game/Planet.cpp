#include "stdafx.h"
#include "Planet.h"
#include "Game.h"
#include <string>


class RepopPlanet : public IGameObject {
	int numpla=0;
public:
	void Update()
	{
		if (Planet::Generate(1, numpla) == true) {
			DeleteGO(this);
		}
	}
	void Set(int SetNum) {
		numpla = SetNum;
	}
};
Planet::Planet()
{
}

Planet::~Planet()
{
	DeleteGO(p_skinModelRender);
	
}

bool Planet::Start() 
{
	return true;
}
void Planet::GenerateAll(int Reload, int Planetnum) {

	Game* m_game = nullptr;
	m_game = FindGO<Game>("Game");
	//Planetnumber_Num���̍쐬
	for (int i = 0, w = Planetnumber_00; i < Reload; i++, w++) {
		prefab::CSkinModelRender* P_skinModelRender;
		P_skinModelRender = NewGO<prefab::CSkinModelRender>(0);

		//�f���̃��f�����O�w��B
		if (Reload != Planetnumber_Num) //Num�͏������X�|�[���̂��ߗ�O�B
			w = Planetnum;          //�f���̎w��B

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
		//�������X�|�[���̏ꍇ�B
		if (Planetnum == Planetnumber_Num) {
			m_game->memoryPP[i] = m_planet;
			m_planet->myPlanetnumber = i;    //������Plamet�i���o�[�ۑ��B
		}
		//���|�b�v�B
		else if (Planetnum != Planetnumber_Num) {
			m_game->memoryPP[w] = m_planet;
			m_planet->myPlanetnumber = w;    //������Plamet�i���o�[�ۑ��B
		}

		CVector3 hako;
		do {
			m_planet->repopflag = false;
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
			float PosLimitx = 30000.0f;
			float PosLimitz = 20000.0f;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			m_planet->p_position = hako;

			m_planet->initAll(m_planet->p_position, P_skinModelRender);

			//�|�b�v���Ƀv���C���[�ƂԂ���Ȃ��悤�ɁB
			for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
				if (j != Game::GetInstance()->GetSansenKazu()) { //�����łȂ����
					CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - m_planet->p_position;
					if (kyori.Length() < m_planet->radius + 500.0f) {
						m_planet->repopflag = true;
					}
				}
			}
			//�|�b�v���ɘf���ƂԂ���Ȃ��悤�ɁB
			//for (int j = 0; j < Planetnumber_Num; j++) {
			//	if (j == m_planet->myPlanetnumber) {//�����łȂ����
			//		CVector3 kyori = Game::GetInstance()->memoryPP[i]->p_position - m_planet->p_position;
			//		if (kyori.Length() < m_planet->radius + 500.0f) {
			//			m_planet->repopflag = true;
			//		}
			//	}
			//}
		} while (m_planet->repopflag == true);
	}
}
bool Planet::Generate(int Reload, int Planetnum) {
	
	Game* game = nullptr;
	game = FindGO<Game>("Game");
	//Planetnumber_Num���̍쐬
	for (int i = 0, w = Planetnumber_00;i < Reload;i++, w++) {
			prefab::CSkinModelRender* P_skinModelRender;
			P_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
			int myplanetnum = 0;
			if (Reload != Planetnumber_Num) { //Num�͏������X�|�[���̂��ߗ�O�B
				w = Planetnum;          //�f���̎w��B
				int myplanetnum = Planetnum;
			}
			else {
				myplanetnum = i;
			}

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
			float PosLimitx = 30000.0f;
			float PosLimitz = 20000.0f;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			//�f���̑傫�������_���B
			float v = 10.0f;//�Œ���̑傫����\�ߓ���Ă����B
			v += 50.0f * Random().GetRandDouble();
			float radius = { 30.0f };//	��{�f���̔��a
			radius *= v;

			bool isCreatePlanet = true;//�t���O
			////�|�b�v���Ƀv���C���[�ƂԂ���Ȃ��悤�ɁB
			for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
					CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - hako;
					if (kyori.Length() < radius + 500.0f) {
						isCreatePlanet = false;
					}
				
			}
			//�|�b�v���ɘf���ƂԂ���Ȃ��悤�ɁB
			//for (int j = 0; j < Planetnumber_Num; j++) {
			//	if (j == m_planet->myPlanetnumber) {//�����łȂ����
			//		CVector3 kyori = Game::GetInstance()->memoryPP[i]->p_position - hako;
			//		if (kyori.Length() < m_planet->radius + 500.0f) {
			//			isCreatePlanet = false;
			//		}
			//	}
			//}

			if (isCreatePlanet) {
				//�v���l�b�g�𐶐��ł���Ȃ�쐬����B

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
				Planet* planet = NewGO<Planet>(0, "planet");
				//�������X�|�[���̏ꍇ�B
				if (Planetnum == Planetnumber_Num) {
					game->memoryPP[i] = planet;
					planet->myPlanetnumber = i;    //������Plamet�i���o�[�ۑ��B
				}
				//���|�b�v�B
				else if (Planetnum != Planetnumber_Num) {
					game->memoryPP[w] = planet;
					planet->myPlanetnumber = w;    //������Plamet�i���o�[�ۑ��B
				}
				planet->p_position = hako;

				planet->init(planet->p_position, P_skinModelRender,v);

			}
	}
	return true;
}
//���̐����B
void Planet::initAll(CVector3 position, prefab::CSkinModelRender* skinModelRender)
{
	//���̃|�W�V�����ۑ��B
	p_position = position;

	//�f���̑傫�������_���B

	float v = 10.0f;//�Œ���̑傫����\�ߓ���Ă����B
	v += 50.0f * Random().GetRandDouble();
	scale.x *= v;
	scale.z *= v;
	radius *= v;

	p_skinModelRender = skinModelRender;
	p_skinModelRender->SetScale(scale);
	p_skinModelRender->SetPosition(position);
}
//���̐����B
void Planet::init(CVector3 position, prefab::CSkinModelRender* skinModelRender,float scale)
{
	//���̃|�W�V�����ۑ��B
	p_position = position;

	//�ۑ�
	CVector3 hoge = { 1.0f,1.0f,1.0f };
	hoge.x *= scale;
	hoge.z *= scale;
	radius *= scale;
	
	p_skinModelRender = skinModelRender;
	p_skinModelRender->SetScale(hoge);
	p_skinModelRender->SetPosition(position);
}
//�����_���ړ��B
void Planet::Move() {
	
	if (movecount == false) {
		
		randomspeed.x = Random().GetRandDouble() * 1000 * GameTime().GetFrameDeltaTime();
		randomspeed.z = Random().GetRandDouble() * 1000 * GameTime().GetFrameDeltaTime();
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.x *= -1;
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.z *= -1;
		
		movecount = true;
	}
	p_position += randomspeed;
	p_skinModelRender->SetPosition(p_position);
}
//�h�J�[���i�����j�����˂��A�ԉ΂����A�A�A�B
void Planet::explosion()
{
	if (this->CountExplosion == false) {
		CountExplosion = true;
		Star* m_star = NewGO<Star>(0, "Star");
		float tyousei = 30.0f; //�f���Ɛ��̃��f���̑傫���̍��𒲐����B
		m_star->Pop(this->p_position, this->scale*this->radius/ tyousei);
		Game::GetInstance()->SetStarCount(1);
		//Generate(1, myPlanetnumber); //�V���Șf���𐶐��i�����̃i���o�[�̘f�����j�B
		NewGO<RepopPlanet>(0)->Set(myPlanetnumber);
		DeleteGO(this);

		//�G�t�F�N�g���쐬�B
		prefab::CEffect* effect;
		effect = NewGO<prefab::CEffect>(0);
		//�G�t�F�N�g���Đ��B
		effect->Play(L"effect/explosion1.efk");
		//�G�t�F�N�g�ɔ��a/�i�l�����ƍ��j��������
		effect->SetScale({ radius/200,1.0f,radius/200 });
		effect->SetPosition(this->p_position);

		//���ʉ��i�����j;
		SoundSource = NewGO<prefab::CSoundSource>(0);
		SoundSource->Init(L"sound/bakuhatu.wav");
		SoundSource->Play(false);                     //�����V���b�g�Đ��B
		SoundSource->SetVolume(0.1f);                 //���ʒ��߁B
	}
}

void Planet::Timer()
{
	time++;
}
//�f�����S����B
void Planet::Death() {

	//�������I����f���I�I�v���C���[�j�󂷂����I�I�B
	
	for (int i = 0;i < Game::GetInstance()->GetSansenKazu();i++) {
		//�v���C���[�����G�Ȃ�U������߂�B
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - p_position;
			if (kyori.Length() < radius
				&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
				Game::GetInstance()->m_player[i]->AddHP(-100);
				if (time > 2) { //�o�n�o���͊��ق��Ă�����I
					explosion();
				}
			}
		}
	}
	//�e�����͊��ق��Ă��������B
	if (Game::GetInstance()->GetPBInit() == true) {
		int a = 0;
		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* bullet)->bool
		{
			CVector3 b_kyori = bullet->GetPosition() - p_position;
			if (b_kyori.Length() < radius) {
				a++;
				explosion();
			}
			return true;
		});
	}
	//�f�������񂷁B
	for (int i = 0;i < Planetnumber_Num;i++) {
		//�����A�A�Aᒂɏ���Y�����A�A�ǂ������Ǝv�����炷�����j���ė��₪��(�f�����m�̋�������B
			//������r����f���������łȂ���΁B
		if (Game::GetInstance()->memoryPP[i] != this) {
			//2�_�Ԃ̋������v�Z����B
			CVector3 diff = Game::GetInstance()->memoryPP[i]->p_position - p_position;
			//���������a�ȉ��Ȃ�B
		/*	if (diff.Length() < radius) {
				explosion();
				BlackHole::Generate(p_position, radius);
			}
			else*/ if (Game::GetInstance()->memoryPP[i]->radius + radius > diff.Length()) {
				explosion();
				BlackHole::Generate(p_position, radius);
			}
		}
	}
	//�ف[���ق��ق��ق����f���炵���I�z���A���Ă����Ȃ����I�U�[�{������h�h���A����A�G���A�O�ɂłĔ��������Y��ȉԉ΂ł��悧�B

	if (p_position.x> 32000.0f || p_position.x< -32000.0f
			||p_position.z>20000.0f || p_position.z < -20000.0f) {
			explosion();
	}
	
}

void Planet::Update() {
	
	Timer();
	Move();
	Death();
}