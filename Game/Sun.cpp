#include "stdafx.h"
#include "Sun.h"


Sun::Sun()
{
}


Sun::~Sun()
{
	DeleteGO(p_skinModelRender);
}

bool Sun::Start()
{
	p_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	p_skinModelRender->Init(L"modelData/planet0fire.cmo");
	p_skinModelRender->SetPosition(p_position);
	//���C�g�n�B
	p_Cpointlit = NewGO < prefab::CPointLight >(0);
	p_Cpointlit->SetAttn({ 35000, 1, 0 });
	p_Cpointlit->SetColor({ 100.0f, 50.0f, 25.0f });
	p_skinModelRender->SetEmissionColor({ 6.0f,6.0f,-0.5f });
	//�X�P�[���n�B	
	CVector3 scale = { 1.0f,1.0f,1.0f };
	p_skinModelRender->SetScale(scale*SunSize);
	radius *= SunSize;
	radius += 100.0f;//�����蔻�葝�₷�����B
	return true;
}

void Sun::Move()
{
	//�������I����f���I�I�v���C���[�j�󂷂����I�I�B
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

void Sun::Reflection()
{	//Bullet�T�[�`�B
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		//�ΏۂƂ̋����𑪒�B
		CVector3 kyori = b->GetPosition() - p_position;
		//�ΏۂƂ̋��������ȉ��ɂȂ�����B
		if (kyori.Length() < radius *1.25f) {
			//�f���S�ɉ�����Ύキ�A�߂���΋����B
			float G = radius * 1.25f - kyori.Length();
			//�Ώۂɓn���d�́B����Ώd�͂ƂȂ�B
			G_limitar = { 10.0f };//   BBH�̏d�́i�f�j�����B
			CVector3 Migawari = kyori;
			Migawari.Normalize();
			G = G * G / nizyou;
			b->SetMoveSpeed(((Migawari * G) / G_limitar));
			//b->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
		}
		return true;
	});
}

void Sun::Rotation()
{
	//��]
	//�N�H�[�^�j�I����P�ʃN�H�[�^�j�I���ŏ���������B
	CQuaternion qRot = CQuaternion::Identity;
	//Y�������0.1�x�񂷁B
	angle += 0.1f;
	qRot.SetRotationDeg(CVector3::AxisY, angle);
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

void Sun::Update()
{
	Reflection();
	Move();
	Light();
	Rotation();
}
