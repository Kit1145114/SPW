#include "stdafx.h"
#include "Planet.h"


Planet::Planet()
{
}


Planet::~Planet()
{
	DeleteGO(p_skinModelRender);
}
bool Planet::Start() {

	p_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	p_skinModelRender->Init(L"modelData/planet_aomura.cmo");
	CVector3 p_position2 = p_position;
	p_position2.y -= p_position.y+30.0f;
	p_CharaCon.Init(150.0f, 1.0f, p_position2);
	p_skinModelRender->SetScale(scale);
	return true;
}
void Planet::Move() {

}
void Planet::Update() {
	p_skinModelRender->SetPosition(p_position);
}