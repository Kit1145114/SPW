#include "stdafx.h"
#include "Planet.h"


Planet::Planet()
{
}


Planet::~Planet()
{
	DeleteGO(p_skinModelRender0);
}
bool Planet::Start() {
	


	return true;
}
void Planet::Move() {

}
void Planet::Generate() {

	//¯‚Ì¶¬
	//¯‚Ìƒ|ƒWƒVƒ‡ƒ“
	CVector3 pa_position[10];
	//“–‚½‚è”»’è’²®
	for (int i = 0;i < 10;i++) {
		pa_position[i] = p_position[i];
		pa_position[i].y -= p_position[i].y + 30.0f;
	}

	p_position[0] = { 1000.0f,100.0f,0.0f, };
	p_skinModelRender0 = NewGO<prefab::CSkinModelRender>(0);
	p_skinModelRender0->Init(L"modelData/planet_aomura.cmo");
	//p_CharaCon.Init(150.0f, 1.0f, pa_position[0]);
	p_skinModelRender0->SetScale(scale);

	p_skinModelRender0->SetPosition(p_position[0]);

}
void Planet::Update() {

	Generate();
}