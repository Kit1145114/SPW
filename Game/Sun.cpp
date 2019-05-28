#include "stdafx.h"
#include "Sun.h"


Sun::Sun()
{
}


Sun::~Sun()
{
	DeleteGO(p_skinModelRender);
}

bool Sun::Start()
{
	p_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	p_skinModelRender->Init(L"modelData/Sun.cmo");
	p_skinModelRender->SetPosition(p_position);
	//ライト系。
	p_Cpointlit = NewGO < prefab::CPointLight >(0);
	p_Cpointlit->SetAttn({ 100000, 5, 0 });
	emissionColorLow = { 2.3f,2.3f,-0.5f };
	emissionColorHigh = emissionColorLow * 2.0f;
	p_Cpointlit->SetColor(emissionPointLigColorLow);

	emissionPointLigColorLow = { 100.0f, 50.0f, 25.0f };
	emissionPointLigColorHigh = emissionPointLigColorLow * 5.0f;
	p_skinModelRender->SetEmissionColor(emissionColorLow);
	//スケール系。	
	CVector3 scale = { 1.0f,1.0f,1.0f };
	p_skinModelRender->SetScale(scale*SunSize);
	radius *= SunSize;
	radius += 100.0f;//当たり判定増やす調整。
	return true;
}

void Sun::Move()
{
	//おっす！おら惑星！！プレイヤー破壊すっぞ！！。
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

void Sun::Reflection()
{	//Bulletサーチ。
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		//対象との距離を測定。
		CVector3 kyori = b->GetPosition() - p_position;
		//対象との距離が一定以下になったら。
		if (kyori.Length() < radius *1.25f) {
			//Ｇ中心に遠ければ弱く、近ければ強く。
			float G = radius * 1.25f - kyori.Length();
			//対象に渡す重力。すれば重力となる。
			G_limitar = { 1.0f };//   BBHの重力（Ｇ）調整。
			CVector3 Migawari = kyori;
			Migawari.Normalize();
			G = G * G / nizyou;
			b->SetMoveSpeed(((Migawari * G) / G_limitar));
			//b->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
		}
		return true;
	});
}

void Sun::Rotation()
{
	//回転
	//クォータニオンを単位クォータニオンで初期化する。
	CQuaternion qRot = CQuaternion::Identity;
	//Y軸周りに0.1度回す。
	angle += 0.1f;
	qRot.SetRotationDeg(CVector3::AxisY, angle);
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

void Sun::Update()
{
	Reflection();
	Move();
	Light();
	Rotation();
	
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
				break;
			}
			
		}

		CVector3 emissionColor;
		emissionColor.Lerp(m_timer / emissionEndTime, emissionColorLow, emissionColorHigh );
		p_skinModelRender->SetEmissionColor(emissionColor);

		CVector3 ptLigColor;
		ptLigColor.Lerp(m_timer / emissionEndTime, emissionPointLigColorLow, emissionPointLigColorHigh);
		p_Cpointlit->SetColor(ptLigColor);

	}break;
	}
}
