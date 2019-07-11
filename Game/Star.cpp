#include "stdafx.h"
#include "Star.h"
#include"Game.h"

Star::Star()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	/*p_Cpointlit = NewGO < prefab::CPointLight >(0);
	p_Cpointlit->SetAttn({ 8000, 1, 0 });
	p_Cpointlit->SetColor({ 70.0f, 70.0f, 70.0f });*/
	m_skinModelRender->Init(L"modelData/star.cmo");
	m_scale = { 8.0f, 8.0, 8.0f };
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetEmissionColor({ 1.25, 1.25, 1.25 }); //物自体を光らせるコード。
	m_game = Game::GetInstance();
}

Star::~Star()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(p_Cpointlit);
}
//常に行う処理。
void Star::Update()
{
	Rotation();
	Push();
	time += GameTime().GetFrameDeltaTime();
	if (time > Limit)
	{
		time = time0;		//時間で削除。
		Death();
	}
	if (p_Cpointlit != nullptr) {
		p_Cpointlit->SetPosition(m_position);
	}
}
//惑星の大きさに合わせて☆の大きさを決める。
void Star::Pop(CVector3 position,CVector3 scale)
{
	m_position = position;
	m_scale = scale;
	m_scale *= 1.2;
	//☆の大きさによってポイントを変える。
	if (m_scale.x< StarScale/2) {
		StarPoint = 1;
	}
	else if (m_scale.x < StarScale) {
		StarPoint = 2;
	}
	else  {
		StarPoint = 3;
	}

	m_position.y += 30.0f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
};
//太陽の大きさに合わせて☆の大きさを決める。
void Star::SunPop(CVector3 position, CVector3 scale)
{
	m_position = position;
	m_position.y += 30.0f;
	m_scale = scale;
	Limit = 15.0f;
	m_skinModelRender->Init(L"modelData/PlayerStar.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
};
//☆を出現させる場所の設定。
void Star::Push()
{
	m_skinModelRender->SetPosition(m_position);
}
//☆の回転
void Star::Rotation()
{
	float SpeedY = 2.0f;
	angle += SpeedY;
	m_rotation.SetRotationDeg(CVector3::AxisY, angle);
	m_skinModelRender->SetRotation(m_rotation);
}
//☆の死亡
void Star::Death()
{
	DeleteGO(this);
}

