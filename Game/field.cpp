#include "stdafx.h"
#include "field.h"
#include"Game.h"

field::field()
{
}


field::~field()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(Haikei);
}

bool field::Start() {
	if (Game::GetInstance()->GetSunflag() == false) {//�����ʏ�X�e�[�W�Ȃ�B
		psShader.Load("shader/model.fx", "PSMainBG", CShader::EnType::PS);
	}
	else {											 //���z�X�e�[�W�Ȃ�B
		psShader.Load("shader/model.fx", "PSMainBGSun", CShader::EnType::PS);
	}
	
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Space_field.cmo");
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetForwardRenderFlag(true);
	m_skinModelRender->FindMaterial([&](CModelEffect* mat) {
		mat->SetRender3DModelPSShader(psShader);
	});

	//�ÓI�����I�u�W�F�N�g������������B
	m_phyStaticObject.CreateMesh(
		pos,
		CQuaternion::Identity,
		scale,
		m_skinModelRender
	);
	
	return true;
}

void field::Update() {
	m_skinModelRender->SetPosition(pos);
}