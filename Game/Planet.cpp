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
	p_CharaCon.Init(30.0f, 100.0f, p_position);
	p_skinModelRender->SetScale(scale);
	return true;
}
void Planet::Move() {

}
void Planet::Update() {
	p_skinModelRender->SetPosition(p_position);

}