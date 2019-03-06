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

	for (int i = 0;i < 10;i++) {
		prefab::CSkinModelRender* P_skinModelRender;
		P_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		switch (i) {
		case 0:
			P_skinModelRender->Init(L"modelData /planet0fire");
			break;
		case 1:
			P_skinModelRender->Init(L"modelData /planet01");
			break;
		case 2:
			P_skinModelRender->Init(L"modelData /planet02");
			break;
		case 3:
			P_skinModelRender->Init(L"modelData /planet03");
			break;
		case 4:
			P_skinModelRender->Init(L"modelData /planet04");
			break;
		case 5:
			P_skinModelRender->Init(L"modelData /planet05");
			break;
		case 6:
			P_skinModelRender->Init(L"modelData /planet06");
			break;
		case 7:
			P_skinModelRender->Init(L"modelData /planet07");
			break;
		case 8:
			P_skinModelRender->Init(L"modelData /planet08");
			break;
		case 9:
			P_skinModelRender->Init(L"modelData /planet09");
			break;
		case 10:
			P_skinModelRender->Init(L"modelData /planet010");
			break;
		}
		
		Planet* m_planet = NewGO<Planet>(0, "planet");
		m_planet->p_position = { 1000.0f,100.0f,0.0f, };
		m_planet->init(m_planet->p_position, P_skinModelRender);
	}

}
void Planet::init(CVector3 position, prefab::CSkinModelRender* skinModelRender)
{
	//¯‚Ì¶¬
	//¯‚Ìƒ|ƒWƒVƒ‡ƒ“
	p_position = position;
	//“–‚½‚è”»’è’²®
	CVector3 pa_position = position;
	pa_position.y -= position.y + 30.0f;
	
	p_skinModelRender0 = skinModelRender;
	
	p_CharaCon.Init(150.0f, 1.0f, pa_position);
	p_skinModelRender0->SetScale(scale);

	p_skinModelRender0->SetPosition(position);
}
void Planet::Update() {

	Move();
}