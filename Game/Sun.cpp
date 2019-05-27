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
	p_skinModelRender->Init(L"modelData/planet0fire.cmo");
	p_skinModelRender->SetPosition(p_position);
	//ライト系。
	p_Cpointlit = NewGO < prefab::CPointLight >(0);
	p_Cpointlit->SetAttn({ 35000, 1, 0 });
	p_Cpointlit->SetColor({ 100.0f, 50.0f, 25.0f });
	p_skinModelRender->SetEmissionColor({ 6.0f,6.0f,-0.5f });
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
			G_limitar = { 10.0f };//   BBHの重力（Ｇ）調整。
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
}
