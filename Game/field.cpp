#include "stdafx.h"
#include "field.h"


field::field()
{
}


field::~field()
{
	DeleteGO(m_skinModelRender);
}

bool field::Start() {
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Space_field.cmo");
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_skinModelRender->SetScale(scale);
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