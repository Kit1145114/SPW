#include "stdafx.h"
#include "Planet.h"
#include "Game.h"
#include <string>


class RepopPlanet : public IGameObject {
	int numpla=0;
public:
	void Update()
	{
		if (Planet::Generate(1, numpla) == true) {
			DeleteGO(this);
		}
	}
	void Set(int SetNum) {
		numpla = SetNum;
	}
};
Planet::Planet()
{
}

Planet::~Planet()
{
	DeleteGO(p_skinModelRender);
	
}

bool Planet::Start() 
{
	return true;
}
void Planet::GenerateAll(int Reload, int Planetnum) {

	Game* m_game = nullptr;
	m_game = FindGO<Game>("Game");
	//Planetnumber_Num分の作成
	for (int i = 0, w = Planetnumber_00; i < Reload; i++, w++) {
		prefab::CSkinModelRender* P_skinModelRender;
		P_skinModelRender = NewGO<prefab::CSkinModelRender>(0);

		//惑星のモデリング指定。
		if (Reload != Planetnumber_Num) //Numは初期リスポーンのため例外。
			w = Planetnum;          //惑星の指定。

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
		//初期リスポーンの場合。
		if (Planetnum == Planetnumber_Num) {
			m_game->memoryPP[i] = m_planet;
			m_planet->myPlanetnumber = i;    //自分のPlametナンバー保存。
		}
		//リポップ。
		else if (Planetnum != Planetnumber_Num) {
			m_game->memoryPP[w] = m_planet;
			m_planet->myPlanetnumber = w;    //自分のPlametナンバー保存。
		}

		CVector3 hako;
		do {
			m_planet->repopflag = false;
			//ランダムポップ。
			float vx = Random().GetRandDouble();
			float vz = Random().GetRandDouble();

			hako.x = vx;
			hako.z = vz;
			if (Random().GetRandDouble() <= 0.5f)
				hako.x *= -1;
			if (Random().GetRandDouble() <= 0.5f)
				hako.z *= -1;

			//ランダム生成する場所の制限。
			float PosLimitx = 30000.0f;
			float PosLimitz = 20000.0f;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			m_planet->p_position = hako;

			m_planet->initAll(m_planet->p_position, P_skinModelRender);

			//ポップ時にプレイヤーとぶつからないように。
			for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
				if (j != Game::GetInstance()->GetSansenKazu()) { //自分でなければ
					CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - m_planet->p_position;
					if (kyori.Length() < m_planet->radius + 500.0f) {
						m_planet->repopflag = true;
					}
				}
			}
			//ポップ時に惑星とぶつからないように。
			//for (int j = 0; j < Planetnumber_Num; j++) {
			//	if (j == m_planet->myPlanetnumber) {//自分でなければ
			//		CVector3 kyori = Game::GetInstance()->memoryPP[i]->p_position - m_planet->p_position;
			//		if (kyori.Length() < m_planet->radius + 500.0f) {
			//			m_planet->repopflag = true;
			//		}
			//	}
			//}
		} while (m_planet->repopflag == true);
	}
}
bool Planet::Generate(int Reload, int Planetnum) {
	
	Game* game = nullptr;
	game = FindGO<Game>("Game");
	//Planetnumber_Num分の作成
	for (int i = 0, w = Planetnumber_00;i < Reload;i++, w++) {
			prefab::CSkinModelRender* P_skinModelRender;
			P_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
			int myplanetnum = 0;
			if (Reload != Planetnumber_Num) { //Numは初期リスポーンのため例外。
				w = Planetnum;          //惑星の指定。
				int myplanetnum = Planetnum;
			}
			else {
				myplanetnum = i;
			}

			CVector3 hako;
			
			//ランダムポップ。
			float vx = Random().GetRandDouble();
			float vz = Random().GetRandDouble();
			
			hako.x = vx;
			hako.z = vz;
			if (Random().GetRandDouble() <= 0.5f)
				hako.x *= -1;
			if (Random().GetRandDouble() <= 0.5f)
				hako.z *= -1;

			//ランダム生成する場所の制限。
			float PosLimitx = 30000.0f;
			float PosLimitz = 20000.0f;
			hako.x *= PosLimitx;
			hako.z *= PosLimitz;

			//惑星の大きさランダム。
			float v = 10.0f;//最低限の大きさを予め入れておく。
			v += 50.0f * Random().GetRandDouble();
			float radius = { 30.0f };//	基本惑星の半径
			radius *= v;

			bool isCreatePlanet = true;//フラグ
			////ポップ時にプレイヤーとぶつからないように。
			for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
					CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - hako;
					if (kyori.Length() < radius + 500.0f) {
						isCreatePlanet = false;
					}
				
			}
			//ポップ時に惑星とぶつからないように。
			//for (int j = 0; j < Planetnumber_Num; j++) {
			//	if (j == m_planet->myPlanetnumber) {//自分でなければ
			//		CVector3 kyori = Game::GetInstance()->memoryPP[i]->p_position - hako;
			//		if (kyori.Length() < m_planet->radius + 500.0f) {
			//			isCreatePlanet = false;
			//		}
			//	}
			//}

			if (isCreatePlanet) {
				//プラネットを生成できるなら作成する。

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
				Planet* planet = NewGO<Planet>(0, "planet");
				//初期リスポーンの場合。
				if (Planetnum == Planetnumber_Num) {
					game->memoryPP[i] = planet;
					planet->myPlanetnumber = i;    //自分のPlametナンバー保存。
				}
				//リポップ。
				else if (Planetnum != Planetnumber_Num) {
					game->memoryPP[w] = planet;
					planet->myPlanetnumber = w;    //自分のPlametナンバー保存。
				}
				planet->p_position = hako;

				planet->init(planet->p_position, P_skinModelRender,v);

			}
	}
	return true;
}
//星の生成。
void Planet::initAll(CVector3 position, prefab::CSkinModelRender* skinModelRender)
{
	//星のポジション保存。
	p_position = position;

	//惑星の大きさランダム。

	float v = 10.0f;//最低限の大きさを予め入れておく。
	v += 50.0f * Random().GetRandDouble();
	scale.x *= v;
	scale.z *= v;
	radius *= v;

	p_skinModelRender = skinModelRender;
	p_skinModelRender->SetScale(scale);
	p_skinModelRender->SetPosition(position);
}
//星の生成。
void Planet::init(CVector3 position, prefab::CSkinModelRender* skinModelRender,float scale)
{
	//星のポジション保存。
	p_position = position;

	//保存
	CVector3 hoge = { 1.0f,1.0f,1.0f };
	hoge.x *= scale;
	hoge.z *= scale;
	radius *= scale;
	
	p_skinModelRender = skinModelRender;
	p_skinModelRender->SetScale(hoge);
	p_skinModelRender->SetPosition(position);
}
//ランダム移動。
void Planet::Move() {
	
	if (movecount == false) {
		
		randomspeed.x = Random().GetRandDouble() * 1000 * GameTime().GetFrameDeltaTime();
		randomspeed.z = Random().GetRandDouble() * 1000 * GameTime().GetFrameDeltaTime();
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.x *= -1;
		if (Random().GetRandDouble() <= 0.5f)
			randomspeed.z *= -1;
		
		movecount = true;
	}
	p_position += randomspeed;
	p_skinModelRender->SetPosition(p_position);
}
//ドカーン（爆発）きたねぇ、花火だぜ、、、。
void Planet::explosion()
{
	if (this->CountExplosion == false) {
		CountExplosion = true;
		Star* m_star = NewGO<Star>(0, "Star");
		float tyousei = 30.0f; //惑星と星のモデルの大きさの差を調整↓。
		m_star->Pop(this->p_position, this->scale*this->radius/ tyousei);
		Game::GetInstance()->SetStarCount(1);
		//Generate(1, myPlanetnumber); //新たな惑星を生成（自分のナンバーの惑星を）。
		NewGO<RepopPlanet>(0)->Set(myPlanetnumber);
		DeleteGO(this);

		//エフェクトを作成。
		prefab::CEffect* effect;
		effect = NewGO<prefab::CEffect>(0);
		//エフェクトを再生。
		effect->Play(L"effect/explosion1.efk");
		//エフェクトに半径/（Ｍａｘと差）をかける
		effect->SetScale({ radius/200,1.0f,radius/200 });
		effect->SetPosition(this->p_position);

		//効果音（爆発）;
		SoundSource = NewGO<prefab::CSoundSource>(0);
		SoundSource->Init(L"sound/bakuhatu.wav");
		SoundSource->Play(false);                     //ワンショット再生。
		SoundSource->SetVolume(0.1f);                 //音量調節。
	}
}

void Planet::Timer()
{
	time++;
}
//惑星死亡判定。
void Planet::Death() {

	//おっす！おら惑星！！プレイヤー破壊すっぞ！！。
	
	for (int i = 0;i < Game::GetInstance()->GetSansenKazu();i++) {
		//プレイヤーが無敵なら攻撃をやめる。
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - p_position;
			if (kyori.Length() < radius
				&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
				Game::GetInstance()->m_player[i]->AddHP(-100);
				if (time > 2) { //ＰＯＰ時は勘弁してやっぞ！
					explosion();
				}
			}
		}
	}
	//弾だけは勘弁してくだせぇ。
	if (Game::GetInstance()->GetPBInit() == true) {
		int a = 0;
		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* bullet)->bool
		{
			CVector3 b_kyori = bullet->GetPosition() - p_position;
			if (b_kyori.Length() < radius) {
				a++;
				explosion();
			}
			return true;
		});
	}
	//惑星個数分回す。
	for (int i = 0;i < Planetnumber_Num;i++) {
		//ちっ、、、癇に障る野郎だぜ、、追いついたと思ったらすぐ爆破して来やがる(惑星同士の距離判定。
			//もし比較する惑星が自分でなければ。
		if (Game::GetInstance()->memoryPP[i] != this) {
			//2点間の距離を計算する。
			CVector3 diff = Game::GetInstance()->memoryPP[i]->p_position - p_position;
			//距離が半径以下なら。
		/*	if (diff.Length() < radius) {
				explosion();
				BlackHole::Generate(p_position, radius);
			}
			else*/ if (Game::GetInstance()->memoryPP[i]->radius + radius > diff.Length()) {
				explosion();
				BlackHole::Generate(p_position, radius);
			}
		}
	}
	//ほーっほぉほぉほぉお素晴らしい！ホラ、見てご覧なさい！ザーボンさんドドリアさん、エリア外にでて爆発する綺麗な花火ですよぉ。

	if (p_position.x> 32000.0f || p_position.x< -32000.0f
			||p_position.z>20000.0f || p_position.z < -20000.0f) {
			explosion();
	}
	
}

void Planet::Update() {
	
	Timer();
	Move();
	Death();
}