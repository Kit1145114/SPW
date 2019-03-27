#include "stdafx.h"
#include "Planet.h"
#include "Game.h"
#include <string>

Planet::Planet()
{
}


Planet::~Planet()
{
	DeleteGO(p_skinModelRender0);
}
bool Planet::Start() {
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("Player");

	

	return true;
}

void Planet::Generate(int Reload) {
	
	Game* m_game = nullptr;
	m_game = FindGO<Game>("Game");
	//Planetnumber_Num分の作成
	for (int i = 0, w = Planetnumber_00;i < Reload;i++, w++) {
		//常にGetPlanetAgeinCount＝＝11が出現するように
		//if (m_game->GetPlanetAgeinCount() < Planetnumber_Num) {
			//m_game->SetPlanetAgeinCount(+1);
			prefab::CSkinModelRender* P_skinModelRender;
			P_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
			
			//惑星のモデリング指定。
			switch (w) {
			case Planetnumber_00:
				P_skinModelRender->Init(L"modelData/planet0fire.cmo");
				break;
			case Planetnumber_01:
				P_skinModelRender->Init(L"modelData/planet01.cmo");
				break;
			case Planetnumber_02:
				P_skinModelRender->Init(L"modelData/planet02.cmo");
				break;
			case Planetnumber_03:
				P_skinModelRender->Init(L"modelData/planet03.cmo");
				break;
			case Planetnumber_04:
				P_skinModelRender->Init(L"modelData/planet04.cmo");
				break;
			case Planetnumber_05:
				P_skinModelRender->Init(L"modelData/planet05.cmo");
				break;
			case Planetnumber_06:
				P_skinModelRender->Init(L"modelData/planet06.cmo");
				break;
			case Planetnumber_07:
				P_skinModelRender->Init(L"modelData/planet07.cmo");
				break;
			case Planetnumber_08:
				P_skinModelRender->Init(L"modelData/planet08.cmo");
				break;
			case Planetnumber_09:
				P_skinModelRender->Init(L"modelData/planet09.cmo");
				break;
			case Planetnumber_10:
				P_skinModelRender->Init(L"modelData/planet_10.cmo");
				break;
			case Planetnumber_11:
				P_skinModelRender->Init(L"modelData/planet11.cmo");
				break;
			default:w = Planetnumber_00;
			}
			Planet* m_planet = NewGO<Planet>(0, "planet");
			m_game->memoryPP[i] = m_planet;
			m_planet->myPlanetnumber = w;    //自分のPlametナンバー保存

			//ランダムポップ。
			float vx = Random().GetRandDouble();
			float vz = Random().GetRandDouble();
			CVector3 hako;
			hako.x = vx;
			hako.z = vz;
			if (Random().GetRandDouble() <= 0.5f)
				hako.x *= -1;
			if (Random().GetRandDouble() <= 0.5f)
				hako.z *= -1;

			//ランダム生成する場所の制限。
			float PosLimitx = 20000.0f;
			float PosLimitz = 10000.0f;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			m_planet->p_position = hako;

			m_planet->init(m_planet->p_position, P_skinModelRender);
		}
	//}
}
//星の生成。
void Planet::init(CVector3 position, prefab::CSkinModelRender* skinModelRender)
{
	//星のポジション。
	p_position = position;
	
	//惑星の大きさランダム。
	float v = 50 * Random().GetRandDouble();
	scale.x *= v;
	scale.z *= v;
	radius *= v;

	p_skinModelRender0 = skinModelRender;
	p_skinModelRender0->SetScale(scale);
	p_skinModelRender0->SetPosition(position);
}
void Planet::Move() {
	//ランダム移動。
	
	if (movecount == false) {
		
		randomspeed.x = Random().GetRandDouble() * 100 * GameTime().GetFrameDeltaTime();
		randomspeed.z = Random().GetRandDouble() * 100 * GameTime().GetFrameDeltaTime();
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.x *= -1;
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.z *= -1;
		
		movecount = true;
	}
	p_position += randomspeed;
	p_skinModelRender0->SetPosition(p_position);
}
//ドカーン（爆発）きたねぇ、花火だぜ、、、。
void Planet::explosion()
{
	Star* m_star = NewGO<Star>(0, "star");
	m_star->Pop(this->p_position);
	Generate(1); //新たな惑星を生成（自分のナンバーの惑星を）
	DeleteGO(this);
	//m_game->SetPlanetAgeinCount(-1);
}
//惑星死亡判定。
void Planet::Death(){
	
	//おっす！おら惑星！！プレイヤー破壊すっぞ！！。
	m_sansenkazu = FindGO<SansenKazu>("SansenKazu");
	for (int i = 0;i < m_sansenkazu->GetKazu();i++) {
		CVector3 p_kyori = m_game->GetPosition() - p_position;
		if (p_kyori.Length() < radius
			&& m_game->m_player[i]->GetDeathCount() == false) {
			m_game->m_player[i]->Death();
		}
	}
	//弾だけは勘弁してくだせぇ。
	if (m_player->GetShortCount()==true) {
		m_bullet = FindGO<Bullet>("PlayerBullet");
		CVector3 b_kyori = m_bullet->GetPosition() - p_position;
		if (b_kyori.Length() < radius) {
			explosion();
		}
	}

	//惑星同士の距離判定。
	for (int i = 0;i < Planetnumber_Num;i++) {
		//もし比較する惑星が自分でなければ。
		if (m_game->memoryPP[i] != this) {
			//2点間の距離を計算する。
			CVector3 diff = m_game->memoryPP[i]->p_position - p_position;
			//距離が半径以下なら。
			if (diff.Length() < radius) {
				explosion();
			}
			else if (m_game->memoryPP[i]->radius + radius > diff.Length()) {
				explosion();
			}
		}
	}
}

void Planet::Update() {
	
	Move();
	Death();
}