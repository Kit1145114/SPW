#include "stdafx.h"
#include "field.h"


field::field()
{
}


field::~field()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(Haikei);
}

bool field::Start() {
	psShader.Load("shader/model.fx", "PSMainBG", CShader::EnType::PS);
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Space_field.cmo");
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetForwardRenderFlag(true);
	m_skinModelRender->FindMaterial([&](CModelEffect* mat) {
		mat->SetRender3DModelPSShader(psShader);
	});
	m_skinModelRender->SetEmissionColor({ -20.1f,-20.1f,-20.1f });
	//Haikei = NewGO<prefab::CSkinModelRender>(0);
	//Haikei->Init(L"modelData/Back.cmo");
	//Haikei->SetShadowReceiverFlag(true);
	//CVector3 h_scale = { 2.0f,0.2f,1.0f };
	//Haikei->SetScale(h_scale);
	//静的物理オブジェクトを初期化する。
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
	//Haikei->SetPosition(h_pos);
}