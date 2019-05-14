#include "stdafx.h"
#include "Satellite.h"


Satellite::Satellite() {
}


Satellite::~Satellite() {
	DeleteGO(m_modelRender);
}

bool Satellite::Start() {
	m_modelRender = NewGO<prefab::CSkinModelRender>(0);
	m_modelRender->Init(L"modelData/Satellite.cmo");
	collider.CreateBox(m_pos, m_rot, { 16000, 2000 ,2000 }, 10000.0f, {0,0,0});
	return true;
}

void Satellite::Update() {
	m_modelRender->SetPosition(m_pos);
}
