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
	if (Game::GetInstance()->GetSunflag() == false) {//もし通常ステージなら。
		psShader.Load("shader/model.fx", "PSMainBG", CShader::EnType::PS);
	}
	else {											 //太陽ステージなら。
		psShader.Load("shader/model.fx", "PSMainBGSun", CShader::EnType::PS);
	}
	//psShader.Load("shader/model.fx", "PSMainBG", CShader::EnType::PS);
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Space_field.cmo");
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetForwardRenderFlag(true);
	m_skinModelRender->FindMaterial([&](CModelEffect* mat) {
		mat->SetRender3DModelPSShader(psShader);
	});
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