#include "stdafx.h"
#include "Sun.h"


Sun::Sun()
{
}


Sun::~Sun()
{
	DeleteGO(p_skinModelRender);
	DeleteGO(p_Cpointlit);
	//DeleteGO(SoundSource2);
	//DeleteGO(sunFlareSS);
}

bool Sun::Start()
{
	p_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	p_skinModelRender->Init(L"modelData/Sun.cmo");
	p_skinModelRender->SetPosition(p_position);
	//ライト系。
	p_Cpointlit = NewGO < prefab::CPointLight >(0);
	p_Cpointlit->SetAttn({ 40000, 5, 0 });
	emissionColorLow = { 2.3f,2.3f,-0.5f };
	emissionColorHigh = emissionColorLow * 2.0f;
	p_Cpointlit->SetColor(emissionPointLigColorLow);
	//太陽フレア系。
	emissionPointLigColorLow = { 100.0f, 50.0f, 25.0f };
	emissionPointLigColorHigh = emissionPointLigColorLow * 5.0f;
	p_skinModelRender->SetEmissionColor(emissionColorLow);
	//スケール系。	
	p_skinModelRender->SetScale(scale*(radius/30.0f));
	//radius *= SunSize;
	radius += 100.0f;//当たり判定増やす調整。
	return true;
}

void Sun::Move()
{
	if (radius > 1.0f) {
		//おっす！おら太陽！！プレイヤー破壊すっぞ！！。
		for (int i = 0;i < Game::GetInstance()->GetSansenKazu();i++) {
			//プレイヤーが無敵なら攻撃をやめる。
			if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
				//2点間の距離を計算する。
				CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - p_position;
				//互いの半径の合計が距離以下なら。
				if (Game::GetInstance()->m_player[i]->Getradius() + radius > kyori.Length()
					&& Game::GetInstance()->m_player[i]->GetDeathCount() == false) {
					Game::GetInstance()->m_player[i]->AddHP(-100);
					Game::GetInstance()->m_player[i]->SetLABulletNum(-1);

				}
			}
		}

		//惑星個数分回す。
		for (int i = 0;i < Planetnumber_Num;i++) {
			//QueryGOs<Planet>("planet", [&](Planet* planet)->bool{
				//ちっ、、、癇に障る野郎だぜ、追いついたと思ったらすぐ爆破して来やがる(惑星同士の距離判定。
			if (Game::GetInstance()->memoryPP[i] != nullptr) {
				//2点間の距離を計算する。
				CVector3 diff = Game::GetInstance()->memoryPP[i]->GetPosition() - p_position;
				//互いの半径の合計が距離以下なら。
				if (Game::GetInstance()->memoryPP[i]->GetRadius() + radius > diff.Length()) {
					Game::GetInstance()->memoryPP[i]->explosion();
				}
			}
		}
	}
}

void Sun::Reflection()
{	//Bulletサーチ。
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		//対象との距離を測定。
		CVector3 kyori = b->GetPosition() - p_position;
		//対象との距離が一定以下になったら。
		if (kyori.Length() < radius *1.25f) {
			b->Death();
			SunHP--;
		}
		return true;
	});
}
//回転
void Sun::Rotation()
{
	//クォータニオンを単位クォータニオンで初期化する。
	CQuaternion qRot = CQuaternion::Identity;
	//Y軸周りに0.15度回す。
	angle += 0.15f;
	qRot.SetRotationDeg(CVector3::AxisZ, angle);
	//回転を加算する。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	m_rotation.Multiply(qRot);
	//回転を設定。
	p_skinModelRender->SetRotation(m_rotation);
}

void Sun::Light()
{
	if (p_Cpointlit != nullptr) {
		p_Cpointlit->SetPosition(p_position);
	}
}
//太陽フレア発生。
void Sun::Flare()
{
	
	switch (m_state) {
	case eState_Low: {
			const float emissionEndTime = 1.0f;

			m_timer += GameTime().GetFrameDeltaTime();
			m_timer = min(emissionEndTime, m_timer);
			m_emissionTimer += GameTime().GetFrameDeltaTime();
			if (m_emissionTimer > 1.0f) {
				m_emissionTimer = 0.0f;
				//1秒ごとに10%の確率で太陽フレア発生。
				if (Random().GetRandDouble() < 0.1f) {
					m_timer = 0.0f;
					m_state = eState_High;
					//効果音（磁気嵐）;
					sunFlareSS = NewGO<prefab::CSoundSource>(0);
					sunFlareSS->Init(L"sound/atmosphere4.wav");
					sunFlareSS->Play(false);
					sunFlareSS->SetVolume(1.0f);
					break;
				}

			}
			CVector3 emissionColor;
			emissionColor.Lerp(m_timer / emissionEndTime, emissionColorHigh, emissionColorLow);
			p_skinModelRender->SetEmissionColor(emissionColor);
			CVector3 ptLigColor;
			ptLigColor.Lerp(m_timer / emissionEndTime, emissionPointLigColorHigh, emissionPointLigColorLow);
			p_Cpointlit->SetColor(ptLigColor);

		}break;
	case eState_High: {

			const float emissionEndTime = 0.5f;
			m_timer += GameTime().GetFrameDeltaTime();
			m_timer = min(emissionEndTime, m_timer);

			m_emissionTimer += GameTime().GetFrameDeltaTime();
			if (m_emissionTimer > 1.0f) {
				m_emissionTimer = 0.0f;
				//1秒ごとに50%の確率で太陽フレア終了。
				if (Random().GetRandDouble() < 0.5f) {
					m_timer = 0.0f;
					m_state = eState_Low;
					//DeleteGO(sunFlareSS);
					break;
				}

			}

			CVector3 emissionColor;
			emissionColor.Lerp(m_timer / emissionEndTime, emissionColorLow, emissionColorHigh);
			p_skinModelRender->SetEmissionColor(emissionColor);

			CVector3 ptLigColor;
			ptLigColor.Lerp(m_timer / emissionEndTime, emissionPointLigColorLow, emissionPointLigColorHigh);
			p_Cpointlit->SetColor(ptLigColor);

		}break;
	case eState_death: {

		
		if (Sountziki == false) {
			//効果音（磁気嵐）;
			SoundSource = NewGO<prefab::CSoundSource>(0);
			SoundSource->Init(L"sound/atmosphere4.wav");
			SoundSource->Play(false, 0.8f);                //ワンショット再生。
			SoundSource->SetVolume(1.0f);                 //音量調節。
			Sountziki = true;
		}
			const float emissionEndTime = 2.5f;
			m_timer += GameTime().GetFrameDeltaTime();
			m_timer = min(emissionEndTime, m_timer);


			
			CVector3 emissionColor;
			emissionColor.Lerp(m_timer / emissionEndTime, emissionColorHigh*2.5, emissionColorLow * 0.1f);
			p_skinModelRender->SetEmissionColor(emissionColor);

			CVector3 ptLigColor;
			ptLigColor.Lerp(m_timer / emissionEndTime, emissionPointLigColorHigh*3.5, emissionPointLigColorLow * 0.5f);
			p_Cpointlit->SetColor(ptLigColor);
		}break;
	}
		
}

void Sun::HPCount(){

	//死亡処理。
	if (SunHP < 0) {
		/*Size -=  0.005f;
		float minsize =  0.005f;*/

		//死亡してからカウント開始。
		m_Deathtimer += GameTime().GetFrameDeltaTime();
		//太陽色死亡。
		m_state = eState_death; 

		//2秒で爆発する。
		if (m_Deathtimer >= 2.0f) {
			Size = 0.0f;
			//スターポップ。
			Star* m_star = NewGO<Star>(0, "Star");
			CVector3 iti = { 1.0f,1.0f,1.0f };
			float tyousei = 30.0f; //惑星と星のモデルの大きさの差を調整↓。
			m_star->Pop(this->p_position, iti*this->Maxradius / tyousei);
			Game::GetInstance()->SetStarCount(1);
			
			//エフェクトを作成。
			prefab::CEffect* effect;
			effect = NewGO<prefab::CEffect>(0);
			effect->Play(L"effect/BigExplosion.efk");//エフェクトを再生。
			effect->SetScale(CVector3(Maxradius / 200, 1.0f, Maxradius / 200) * 0.1f);//エフェクトに半径/（Ｍａｘと差）をかける
			effect->SetPosition(this->p_position);

			
			//効果音（爆発）;
			SoundSource2 = NewGO<prefab::CSoundSource>(0);
			SoundSource2->Init(L"sound/bakuhatu.wav");
			SoundSource2->Play(false);                     //ワンショット再生。
			SoundSource2->SetVolume(1.0f);                 //音量調節。

			
			SunHP = 50;            //死亡処理終了。
			SunRevivalFlag = true; //太陽死亡。
		}
		//反映と更新。
		radius = Maxradius * Size;
		p_Cpointlit->SetAttn({ 40000* Size, 5, 0 });
		//p_Cpointlit->SetColor(emissionColorLow * 0.1f);//死んだ色。
		p_skinModelRender->SetScale(scale*(radius / 30.0f));
	}
	//復活処理。
	if (SunRevivalFlag == true) {
		//死亡してからカウント開始。
		m_Deathtimer += GameTime().GetFrameDeltaTime();
		Revival();
	}
}
void Sun::Revival() {

		//復活させる。
		if (m_Deathtimer >= m_Revivaltimer) {
			Size += 0.01f;
			//元の大きさに戻ったら完全復活。
			if (Size >= 1.0f) {
				m_Deathtimer = 0.0f;//リセット。
				SunHP = 5;			//フル回復。
				m_state = eState_Low;
				Sountziki = false;
				m_timer = 0.0f;
				SunRevivalFlag = false;
			}
		}
		//反映と更新。
		radius = Maxradius * Size;
		p_Cpointlit->SetAttn({ 40000 * Size, 5, 0 });
		p_skinModelRender->SetScale(scale*(radius / 30.0f));
	
};

void Sun::Update()
{
	Reflection();
	Move();
	Light();
	Rotation();
	Flare();
	HPCount();
}
