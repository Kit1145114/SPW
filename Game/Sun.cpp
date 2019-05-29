#include "stdafx.h"
#include "Sun.h"
#include "Camera.h"

Sun::Sun()
{
}


Sun::~Sun()
{
	DeleteGO(p_skinModelRender);
}

bool Sun::Start()
{
	camera = FindGO<Camera>("Camera");

	p_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	p_skinModelRender->Init(L"modelData/Sun.cmo");
	p_skinModelRender->SetPosition(p_position);
	//���C�g�n�B
	p_Cpointlit = NewGO < prefab::CPointLight >(0);
	p_Cpointlit->SetAttn({ 40000, 5, 0 });
	emissionColorLow = { 2.3f,2.3f,-0.5f };
	emissionColorHigh = emissionColorLow * 2.0f;
	p_Cpointlit->SetColor(emissionPointLigColorLow);
	//���z�t���A�n�B
	emissionPointLigColorLow = { 100.0f, 50.0f, 25.0f };
	emissionPointLigColorHigh = emissionPointLigColorLow * 5.0f;
	p_skinModelRender->SetEmissionColor(emissionColorLow);
	//�X�P�[���n�B	
	p_skinModelRender->SetScale(scale*(radius/30.0f));
	//radius *= SunSize;
	radius += 100.0f;//�����蔻�葝�₷�����B
	return true;
}

void Sun::Move()
{
	if (radius > 1.0f) {
		//�������I���瑾�z�I�I�v���C���[�j�󂷂����I�I�B
		for (int i = 0;i < Game::GetInstance()->GetSansenKazu();i++) {
			//�v���C���[�����G�Ȃ�U������߂�B
			if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
				//2�_�Ԃ̋������v�Z����B
				CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - p_position;
				//�݂��̔��a�̍��v�������ȉ��Ȃ�B
				if (Game::GetInstance()->m_player[i]->Getradius() + radius > kyori.Length()
					&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
					Game::GetInstance()->m_player[i]->AddHP(-100);
					Game::GetInstance()->m_player[i]->SetLABulletNum(-1);

				}
			}
		}

		//�f�������񂷁B
		for (int i = 0;i < Planetnumber_Num;i++) {
			//QueryGOs<Planet>("planet", [&](Planet* planet)->bool{
				//�����A�A�Aᒂɏ���Y�����A�ǂ������Ǝv�����炷�����j���ė��₪��(�f�����m�̋�������B
			if (Game::GetInstance()->memoryPP[i] != nullptr) {
				//2�_�Ԃ̋������v�Z����B
				CVector3 diff = Game::GetInstance()->memoryPP[i]->GetPosition() - p_position;
				//�݂��̔��a�̍��v�������ȉ��Ȃ�B
				if (Game::GetInstance()->memoryPP[i]->GetRadius() + radius > diff.Length()) {
					Game::GetInstance()->memoryPP[i]->explosion();
				}
			}
		}
	}
}

void Sun::Reflection()
{	//Bullet�T�[�`�B
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		//�ΏۂƂ̋����𑪒�B
		CVector3 kyori = b->GetPosition() - p_position;
		//�ΏۂƂ̋��������ȉ��ɂȂ�����B
		if (kyori.Length() < radius *1.25f) {
			b->Death();
			SunHP--;
		}
		return true;
	});
}
//��]
void Sun::Rotation()
{
	//�N�H�[�^�j�I����P�ʃN�H�[�^�j�I���ŏ���������B
	CQuaternion qRot = CQuaternion::Identity;
	//Y�������0.15�x�񂷁B
	angle += 0.15f;
	qRot.SetRotationDeg(CVector3::AxisZ, angle);
	//��]�����Z����B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	m_rotation.Multiply(qRot);
	//��]��ݒ�B
	p_skinModelRender->SetRotation(m_rotation);
}

void Sun::Light()
{
	if (p_Cpointlit != nullptr) {
		p_Cpointlit->SetPosition(p_position);
	}
}
//���z�t���A�����B
void Sun::Flare()
{
	if (SunRevivalFlag == false) {
		switch (m_state) {
		case eState_Low: {
			const float emissionEndTime = 1.0f;

			m_timer += GameTime().GetFrameDeltaTime();
			m_timer = min(emissionEndTime, m_timer);
			m_emissionTimer += GameTime().GetFrameDeltaTime();
			if (m_emissionTimer > 1.0f) {
				m_emissionTimer = 0.0f;
				//1�b���Ƃ�10%�̊m���ő��z�t���A�����B
				if (Random().GetRandDouble() < 0.1f) {
					m_timer = 0.0f;
					m_state = eState_High;
					break;
				}

			}
			CVector3 emissionColor;
			emissionColor.Lerp(m_timer / emissionEndTime, emissionColorHigh, emissionColorLow);
			p_skinModelRender->SetEmissionColor(emissionColor);
			CVector3 ptLigColor;
			ptLigColor.Lerp(m_timer / emissionEndTime, emissionPointLigColorHigh, emissionPointLigColorLow);
			p_Cpointlit->SetColor(ptLigColor);

		}break;
		case eState_High: {

			const float emissionEndTime = 0.5f;
			m_timer += GameTime().GetFrameDeltaTime();
			m_timer = min(emissionEndTime, m_timer);

			m_emissionTimer += GameTime().GetFrameDeltaTime();
			if (m_emissionTimer > 1.0f) {
				m_emissionTimer = 0.0f;
				//1�b���Ƃ�50%�̊m���ő��z�t���A�I���B
				if (Random().GetRandDouble() < 0.5f) {
					m_timer = 0.0f;
					m_state = eState_Low;
					break;
				}

			}

			CVector3 emissionColor;
			emissionColor.Lerp(m_timer / emissionEndTime, emissionColorLow, emissionColorHigh);
			p_skinModelRender->SetEmissionColor(emissionColor);

			CVector3 ptLigColor;
			ptLigColor.Lerp(m_timer / emissionEndTime, emissionPointLigColorLow, emissionPointLigColorHigh);
			p_Cpointlit->SetColor(ptLigColor);

		}break;
		}
	}
	else {

	}
}

void Sun::HPCount(){

	//���S�����B
	if (SunHP < 0) {
		Size -=  0.005f;
		float minsize =  0.001f;

		if (Size <= minsize) {
			//�X�^�[�|�b�v�B
			Star* m_star = NewGO<Star>(0, "Star");
			CVector3 iti = { 1.0f,1.0f,1.0f };
			float tyousei = 30.0f; //�f���Ɛ��̃��f���̑傫���̍��𒲐����B
			m_star->Pop(this->p_position, iti*this->Maxradius / tyousei);
			Game::GetInstance()->SetStarCount(1);

			SunHP = 50;            //���S�����I���B
			SunRevivalFlag = true; //���z���S�B
			camera->shake(100000, 200, 0.3f);
		}
		//���f�ƍX�V�B
		radius = Maxradius * Size;
		p_Cpointlit->SetAttn({ 40000* Size, 5, 0 });
		p_Cpointlit->SetColor(emissionColorLow * 0.1f);//���񂾐F�B
		p_skinModelRender->SetScale(scale*(radius / 30.0f));
	}
	//���������B
	if (SunRevivalFlag == true) {
		Revival();
	}
}
void Sun::Revival() {

		//���S���Ă���J�E���g�J�n�B
		m_Deathtimer += GameTime().GetFrameDeltaTime();
		//����������B
		if (m_Deathtimer >= m_Revivaltimer) {
			Size += 0.01f;
			//���̑傫���ɖ߂����犮�S�����B
			if (Size >= 1.0f) {
				m_Deathtimer = 0.0f;//���Z�b�g�B
				SunHP = 5;			//�t���񕜁B
				SunRevivalFlag = false;
			}
		}
		//���f�ƍX�V�B
		radius = Maxradius * Size;
		p_Cpointlit->SetAttn({ 40000 * Size, 5, 0 });
		p_skinModelRender->SetScale(scale*(radius / 30.0f));
	
};

void Sun::Update()
{
	Reflection();
	Move();
	Light();
	Rotation();
	Flare();
	HPCount();
}
