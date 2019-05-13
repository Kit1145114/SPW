#include "stdafx.h"
#include "RadarRing.h"


RadarRing::RadarRing()
{
}


RadarRing::~RadarRing()
{
	DeleteGO(m_skinModelRender);
}

bool RadarRing::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(draw_P);
	scale = { 12.0f,12.0f,12.0f };
	m_skinModelRender->SetScale(scale);
	return true;
}

void RadarRing::Update()
{
	m_skinModelRender->SetPosition(m_position);
}

