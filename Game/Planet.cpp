#include "stdafx.h"
#include "Planet.h"
#include "Game.h"
#include <string>

//�f���������A���̃I�u�W�F�N�g�ɔ�������̍ă��|�b�v�p�B
class RepopPlanet : public IGameObject {
	int numpla=0;
public:
	void Set(int SetNum) {
		numpla = SetNum;
	}
	void Update()
	{
		if (Game::GetInstance()!=false) {
			if (Planet::Generate(1, numpla) == true) {
				DeleteGO(this);
			}
		}
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
	p_skinModelRender->SetEmissionColor({ 0.50, 0.50, 0.50 }); //�����̂����点��R�[�h�B
	return true;
}

bool Planet::Generate(int Reload, int Planetnum) {
	Game* game = nullptr;
	game = FindGO<Game>("Game");
	//Planetnumber_Num���̍쐬�B
	for (int i = 0, w = Planetnumber_00;i < Reload;i++, w++) {
			
			int myplanetnum = 0;
			if (Reload != Planetnumber_Num) { //���X�|�[���̂��ߗ�O�B
				w = Planetnum;               //�f���̎w��B
				myplanetnum = Planetnum;
			}
			else {                           //�����|�b�v�B
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
			float PosMaxLimitx = 35000.0f;
			float PosMaxLimitz = 20000.0f;
			hako.x *= PosMaxLimitx;
			hako.z *= PosMaxLimitz;

			//�f���̑傫�������_���B
			float v = 30.0f;//�Œ���̑傫����\�ߓ���Ă����B
			v += 50.0f * Random().GetRandDouble();
			float radius = { 30.0f };//	��{�f���̔��a
			radius *= v;
			bool isCreatePlanet = true;//�t���O
			////�|�b�v���Ƀv���C���[�ƂԂ���Ȃ��悤�ɁB
			for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
					CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - hako;
					if (kyori.Length() < radius + 5000.0f) {
						isCreatePlanet = false;
					}
			}
			//�|�b�v���ɘf���ƂԂ���Ȃ��悤�ɁB
			for (int j = 0; j < Planetnumber_Num; j++) {
				if (j != myplanetnum) {       //�����łȂ���΁B
					Planet* planet = Game::GetInstance()->memoryPP[j];
					if (planet !=nullptr//�����|�b�v�̎��܂���������Ă��Ȃ��f���Ɣ�r���Ȃ��悤�ɁB
						) {               //���|�b�v�͂n�j�B
						CVector3 kyori = planet -> p_position - hako;
						if (kyori.Length() < radius + 500.0f) {
							isCreatePlanet = false;
						}
					}
				}
			}
			//�v���l�b�g�𐶐��ł���Ȃ�쐬����B
			if (isCreatePlanet) {
			//�f���̃��f�����O�w��B
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
			else {
				NewGO<RepopPlanet>(0)->Set(myplanetnum);
			}
	}
	return true;
}
//���̐����B
void Planet::init(CVector3 position, prefab::CSkinModelRender* skinModelRender,float scale)
{
	//���̃|�W�V�����ۑ��B
	p_position = position;

	//�ۑ�
	p_Size.x *= scale;
	p_Size.z *= scale;
	p_Size.y *= scale;
	radius *= scale;
	
	p_skinModelRender = skinModelRender;
	p_skinModelRender->SetScale(p_Size*sizecount);
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

	//��]
	//�N�H�[�^�j�I����P�ʃN�H�[�^�j�I���ŏ���������B
	CQuaternion qRot = CQuaternion::Identity;
	//Y�������0.5�x�񂷁B
	angle += 0.5f;
	qRot.SetRotationDeg(CVector3::AxisY, angle);
	//��]�����Z����B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	m_rotation.Multiply(qRot);
	//��]��ݒ�B
	p_skinModelRender->SetRotation(m_rotation);
	
}
//pop�������Âg�傷��B
void Planet::Size()
{
	if (sizecount <= 1.0f) {
		sizecount += 0.01f;
		p_skinModelRender->SetScale(p_Size*sizecount);
	}
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
		Game::GetInstance()->memoryPP[this->myPlanetnumber] = nullptr;
		Generate(1, myPlanetnumber); //�V���Șf���𐶐��i�����̃i���o�[�̘f�����j�B
		//NewGO<RepopPlanet>(0)->Set(myPlanetnumber);
		DeleteGO(this);

		//�G�t�F�N�g���쐬�B
		prefab::CEffect* effect;
		effect = NewGO<prefab::CEffect>(0);
		//�G�t�F�N�g���Đ��B
		effect->Play(L"effect/BigExplosion.efk");
		//�G�t�F�N�g�ɔ��a/�i�l�����ƍ��j��������
		effect->SetScale( CVector3(radius/200,1.0f,radius/200 ) * 0.1f);
		effect->SetPosition(this->p_position);

		//���ʉ��i�����j;
		SoundSource = NewGO<prefab::CSoundSource>(0);
		SoundSource->Init(L"sound/bakuhatu.wav");
		SoundSource->Play(false);                     //�����V���b�g�Đ��B
		SoundSource->SetVolume(0.3f);                 //���ʒ��߁B
	}
}
//�f�����S����B
void Planet::Death() {

	//�������I����f���I�I�v���C���[�j�󂷂����I�I�B
	for (int i = 0;i < Game::GetInstance()->GetSansenKazu();i++) {
		//�v���C���[�����G�Ȃ�U������߂�B
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//2�_�Ԃ̋������v�Z����B
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - p_position;
			//�݂��̔��a�̍��v�������ȉ��Ȃ�B
			if (Game::GetInstance()->m_player[i]->Getradius()+ radius > kyori.Length()
				&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
				Game::GetInstance()->m_player[i]->AddHP(-100);
				Game::GetInstance()->m_player[i]->SetLABulletNum(-1);
				if (time > 2) { //�o�n�o���͊��ق��Ă�����I
					explosion();
				}
			}
		}
	}
	//�e�����͊��ق��Ă��������B
		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* bullet)->bool
		{
			CVector3 b_kyori = bullet->GetPosition() - p_position;
			if (b_kyori.Length() < radius) {
				explosion();
			}
			return true;
		});
	//�f�������񂷁B
	for (int i = 0;i < Planetnumber_Num;i++) {
	//QueryGOs<Planet>("planet", [&](Planet* planet)->bool{
		//�����A�A�Aᒂɏ���Y�����A�ǂ������Ǝv�����炷�����j���ė��₪��(�f�����m�̋�������B
		//������r����f���������łȂ���΁B
		if (Game::GetInstance()->memoryPP[i] != this
			&&Game::GetInstance()->memoryPP[i] != nullptr) {
			//2�_�Ԃ̋������v�Z����B
			CVector3 diff = Game::GetInstance()->memoryPP[i]->p_position - p_position;
			//�݂��̔��a�̍��v�������ȉ��Ȃ�B
			if (Game::GetInstance()->memoryPP[i]->radius + radius > diff.Length()) {
				explosion();
				int MaxBHCount = 8;
				if (Game::GetInstance()->GetBHflag() == false
					&& Game::GetInstance()->GetBHCount() < MaxBHCount) {
					BlackHole::Generate(p_position, radius);
				}
			}
		}
	}
	//�ف[���ق��ق��ق����f���炵���I�z���A���Ă����Ȃ����I�U�[�{������h�h���A����A�G���A�O�ɂłĔ��������Y��ȉԉ΂ł��悧�B

	if (p_position.x> PosMaxLimitx || p_position.x< -PosMaxLimitx
			||p_position.z>PosMaxLimitz || p_position.z < -PosMaxLimitz) {
			explosion();
	}
	
}

void Planet::Update() {
	if (Game::GetInstance()->isWaitStart())return;
	Size();
	Move();
	Death();
}