#include "stdafx.h"
#include "Planet.h"
#include "Game.h"
#include <string>

//惑星生成時、他のオブジェクトに被った時の再リポップ用。
class RepopPlanet : public IGameObject {
	int numpla=0;
public:
	void Set(int SetNum) {
		numpla = SetNum;
	}
	void Update()
	{
		if (Game::GetInstance()!=false) {
			if (Planet::Generate(1, numpla) == true) {
				DeleteGO(this);
			}
		}
	}
};

Planet::Planet()
{
	
}

Planet::~Planet()
{
	DeleteGO(p_skinModelRender);
	DeleteGO(p_Cpointlit);
}

bool Planet::Start() 
{

	return true;
}

bool Planet::Generate(int Reload, int Planetnum) {
	
	//Planetnumber_Num分の作成。
	for (int i = 0, w = Planetnumber_00;i < Reload;i++, w++) {
			//リスポーン用処理。
			int myplanetnum = 0;
			if (Reload != Planetnumber_Num) { //リスポーンのため例外。
				w = Planetnum;               //惑星の指定。
				myplanetnum = Planetnum;
			}
			else {                           //初期ポップ。
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
			float PosMaxLimitx = 35000.0f;
			float PosMaxLimitz = 20000.0f;
			hako.x *= PosMaxLimitx;
			hako.z *= PosMaxLimitz;

			//惑星の大きさランダム。
			float v = 30.0f;//最低限の大きさを予め入れておく。
			v += 50.0f * Random().GetRandDouble();
			float radius = { 30.0f };//	基本惑星の半径
			radius *= v;
			bool isCreatePlanet = true;//フラグ
			////ポップ時にプレイヤーとぶつからないように。
			for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
					CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - hako;
					if (kyori.Length() < radius + 5000.0f) {
						isCreatePlanet = false;
					}
			}
			//ポップ時に惑星とぶつからないように。
			for (int j = 0; j < Planetnumber_Num; j++) {
				if (j != myplanetnum) {       //自分でなければ。
					Planet* planet = Game::GetInstance()->memoryPP[j];
					if (planet !=nullptr//初期ポップの時まだ生成されていない惑星と比較しないように。
						) {               //リポップはＯＫ。
						CVector3 kyori = planet -> p_position - hako;
						if (kyori.Length() < radius + 500.0f) {
							isCreatePlanet = false;
						}
					}
				}
			}
			//プラネットを生成できるなら作成する。
			if (isCreatePlanet) {
			//惑星のモデリング指定。
				prefab::CSkinModelRender* P_skinModelRender;
				prefab::CPointLight* p_Cpointlit =nullptr;
				P_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
				switch (w) {
				case Planetnumber_00://マグマ
					P_skinModelRender->Init(L"modelData/planet0fire.cmo");
					P_skinModelRender->SetEmissionColor({ 6.0f,6.0f,6.0f });
					p_Cpointlit = NewGO < prefab::CPointLight > (0);
					p_Cpointlit->SetAttn({ 20000, 2.0, 0});
					p_Cpointlit->SetColor({ 400.0f, 30.0f, 0.0f });
					break;
				case Planetnumber_01://砂利。
					P_skinModelRender->Init(L"modelData/planet01.cmo");
					P_skinModelRender->SetEmissionColor({ -1.5f,-1.5f,-1.5f });
					break;
				case Planetnumber_02:
					P_skinModelRender->Init(L"modelData/planet02.cmo");
					break;
				case Planetnumber_03://地球
					P_skinModelRender->Init(L"modelData/planet03.cmo");
					if (Game::GetInstance()->GetSunflag() == false) {//もし通常ステージなら。
						P_skinModelRender->SetEmissionColor({ -0.5f,-0.5f,20.0f });
					}
					else {											 //太陽ステージなら。
						P_skinModelRender->SetEmissionColor({ -0.1f,-0.1f,1.0f });
					}
					break;
				case Planetnumber_04://灰青
					P_skinModelRender->Init(L"modelData/planet04.cmo");
					if (Game::GetInstance()->GetSunflag() == false) {//もし通常ステージなら。
						P_skinModelRender->SetEmissionColor({ -0.5f,-0.5f,20.0f });
					}
					else {											 //太陽ステージなら。
						P_skinModelRender->SetEmissionColor({ -0.1f,-0.1f,3.0f });
					}
					break;
				case Planetnumber_05://赤月
					P_skinModelRender->Init(L"modelData/planet05.cmo");
					if (Game::GetInstance()->GetSunflag() == false) {//もし通常ステージなら。
						P_skinModelRender->SetEmissionColor({ 6.0f,-0.5f,-0.5f });
					}
					else {											 //太陽ステージなら。
						P_skinModelRender->SetEmissionColor({ 1.2f,-0.1f,-0.1f });
					}
					break;
				case Planetnumber_06:
					P_skinModelRender->Init(L"modelData/planet06.cmo");
					break;
				case Planetnumber_07:
					P_skinModelRender->Init(L"modelData/planet07.cmo");
					break;
				case Planetnumber_08://イエロー。
					P_skinModelRender->Init(L"modelData/planet08.cmo");
					P_skinModelRender->SetEmissionColor({ 0.5f,0.5f,-0.25f });
					break;
				case Planetnumber_09://ブルー。
					P_skinModelRender->Init(L"modelData/planet09.cmo");
					break;
				case Planetnumber_10://青紫。
					P_skinModelRender->Init(L"modelData/planet_10.cmo");
					if (Game::GetInstance()->GetSunflag() == false) {//もし通常ステージなら。
						P_skinModelRender->SetEmissionColor({ -0.5f,-0.5f,20.0f });
					}
					else {											 //太陽ステージなら。
						P_skinModelRender->SetEmissionColor({ -0.1f,-0.1f,4.0f });
					}
					break;
				case Planetnumber_11:
					P_skinModelRender->Init(L"modelData/planet11.cmo");
					break;
				default:w = Planetnumber_00;
				}
				Planet* planet = NewGO<Planet>(0, "planet");
				planet->p_skinModelRender = P_skinModelRender;

				//初期リスポーンの場合。
				if (Planetnum == Planetnumber_Num) {
					Game::GetInstance()->memoryPP[i] = planet;
					planet->myPlanetnumber = i;    //自分のPlametナンバー保存。
				}
				//リポップ。
				else if (Planetnum != Planetnumber_Num) {
					Game::GetInstance()->memoryPP[w] = planet;
					planet->myPlanetnumber = w;    //自分のPlametナンバー保存。
				}
				planet->p_position = hako;
				planet->init(planet->p_position, P_skinModelRender,v, p_Cpointlit);
			}
			else {
				NewGO<RepopPlanet>(0)->Set(myplanetnum);
			}
	}
	return true;
}
//星の生成。
void Planet::init(CVector3 position, prefab::CSkinModelRender* skinModelRender,float scale,prefab::CPointLight* cpointlight)
{
	//星のポジション保存。
	p_position = position;

	//保存
	p_Size.x *= scale;
	p_Size.z *= scale;
	p_Size.y *= scale;
	radius *= scale;
	
	p_skinModelRender = skinModelRender;
	p_Cpointlit = cpointlight;
	p_skinModelRender->SetScale(p_Size*sizecount);
	p_skinModelRender->SetPosition(position);
}
void Planet::Light()
{
	if (p_Cpointlit != nullptr) {
		p_Cpointlit->SetPosition(p_position);
	}
	if (Game::GetInstance()->GetSunflag() == true//もし太陽ステージなら。
		&& myPlanetnumber != 0 ) {				 //恒星のマグマ惑星以外なら。
		if (Game::GetInstance()->m_sun->GetSize() < 0.2f) {//太陽サイズが20％以下なら。
			auto game = Game::GetInstance();
			auto planet = game->memoryPP[myPlanetnumber];
			if (planet != nullptr) {
				auto skinModelRender = planet->p_skinModelRender;
				skinModelRender->SetEmissionColor({ -0.5f,-0.5f,-0.5f });
			}

		}
	}


}
//ランダム移動。
void Planet::Move() {
	
	if (movecount == false) {
		//ランダム指定。
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

	//回転
	//クォータニオンを単位クォータニオンで初期化する。
	CQuaternion qRot = CQuaternion::Identity;
	//Y軸周りに0.5度回す。
	angle += 0.5f;
	qRot.SetRotationDeg(CVector3::AxisY, angle);
	//回転を加算する。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	m_rotation.Multiply(qRot);
	//回転を設定。
	p_skinModelRender->SetRotation(m_rotation);
	
}
//pop時少しづつ拡大する。
void Planet::Size()
{
	if (sizecount <= 1.0f) {
		sizecount += 0.01f;
		p_skinModelRender->SetScale(p_Size*sizecount);
	}
}
//ドカーン（爆発）きたねぇ、花火だぜ、、、。
void Planet::explosion()
{
	//爆発フラグオンならば、自分で爆発する。
	if (this->CountExplosion == false) {
		CountExplosion = true;
		//残す☆を作っておく。
		Star* m_star = NewGO<Star>(0, "Star");
		float tyousei = 20.0f; //惑星と星のモデルの大きさの差を調整↓。
		m_star->Pop(this->p_position, this->scale*this->radius/ tyousei);
		Game::GetInstance()->SetStarCount(1);
		Game::GetInstance()->memoryPP[this->myPlanetnumber] = nullptr;
		Generate(1, myPlanetnumber); //新たな惑星を生成（自分のナンバーの惑星を）。
		//NewGO<RepopPlanet>(0)->Set(myPlanetnumber);
		DeleteGO(this);

		//エフェクトを作成。
		prefab::CEffect* effect;
		effect = NewGO<prefab::CEffect>(0);
		//エフェクトを再生。
		effect->Play(L"effect/BigExplosion.efk");
		//エフェクトに半径/（Ｍａｘと差）をかける
		effect->SetScale( CVector3(radius/200,1.0f,radius/200 ) * 0.1f);
		effect->SetPosition(this->p_position);

		//効果音（爆発）;
		SoundSource = NewGO<prefab::CSoundSource>(0);
		SoundSource->Init(L"sound/bakuhatu.wav");
		SoundSource->Play(false);                     //ワンショット再生。
		SoundSource->SetVolume(0.3f);                 //音量調節。
	}
}
//惑星死亡判定。
void Planet::Death() {

	//おっす！おら惑星！！プレイヤー破壊すっぞ！！。
	for (int i = 0;i < Game::GetInstance()->GetSansenKazu();i++) {
		//プレイヤーが無敵なら攻撃をやめる。
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//2点間の距離を計算する。
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - p_position;
			//互いの半径の合計が距離以下なら。
			if (Game::GetInstance()->m_player[i]->Getradius()+ radius > kyori.Length()
				&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
				Game::GetInstance()->m_player[i]->AddHP(-100);
				Game::GetInstance()->m_player[i]->SetLABulletNum(-1);
				if (time > 2) { //ＰＯＰ時は勘弁してやっぞ！
					explosion();
				}
			}
		}
	}
	//弾だけは勘弁してくだせぇ。
		QueryGOs<Bullet>("PlayerBullet", [&](Bullet* bullet)->bool
		{
			CVector3 b_kyori = bullet->GetPosition() - p_position;
			if (b_kyori.Length() < radius) {
				explosion();
			}
			return true;
		});
	//惑星個数分回す。
	for (int i = 0;i < Planetnumber_Num;i++) {
	//QueryGOs<Planet>("planet", [&](Planet* planet)->bool{
		//ちっ、、、癇に障る野郎だぜ、追いついたと思ったらすぐ爆破して来やがる(惑星同士の距離判定。
		//もし比較する惑星が自分でなければ。
		if (Game::GetInstance()->memoryPP[i] != this
			&&Game::GetInstance()->memoryPP[i] != nullptr) {
			//2点間の距離を計算する。
			CVector3 diff = Game::GetInstance()->memoryPP[i]->p_position - p_position;
			//互いの半径の合計が距離以下なら。
			if (Game::GetInstance()->memoryPP[i]->radius + radius > diff.Length()) {
				explosion();
				int MaxBHCount = 8;//MAxBH発生制限;
				if (Game::GetInstance()->GetBHflag() == false
					&& Game::GetInstance()->GetBHCount() < MaxBHCount) {
					BlackHole::Generate(p_position, radius);
				}
			}
		}
	}
	//ほーっほぉほぉほぉお素晴らしい！ホラ、見てご覧なさい！ザーボンさんドドリアさん、エリア外にでて爆発する綺麗な花火ですよぉ。
	//指定の範囲外ならば。
	if (p_position.x> PosMaxLimitx || p_position.x< -PosMaxLimitx
			||p_position.z>PosMaxLimitz || p_position.z < -PosMaxLimitz) {
			explosion();
	}
	
}

void Planet::Update() {
	if (Game::GetInstance()->isWait())return;
	Size();
	Move();
	Death();
	Light();
}