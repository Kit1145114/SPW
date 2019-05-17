#include "stdafx.h"
#include "MeteoGene.h"
#include"Game.h"
#include"Meteo.h"

MeteoGene::~MeteoGene()
{

}

void MeteoGene::Update()
{

	timer += GameTime().GetFrameDeltaTime();
	if (timer > Inittime)
	{
		timer = 0.0f;

		CVector3 hako;

		hako.x = Random().GetRandDouble() - 0.5f;
		hako.z = Random().GetRandDouble() - 0.5f;

		//�����_����������ꏊ�̐����B
		const float PosLimitx = 30000.0f * 2;
		const float PosLimitz = 20000.0f * 2;
		hako.x *= PosLimitx;
		hako.z *= PosLimitz;

		Game* game = Game::GetInstance();
		float v = 10.0f;//�傫��
		v += 50.0f * Random().GetRandDouble();
		float radius = { 30.0f };//	覐΂̔��a
		radius *= v;
		bool isCreatePlanet = true;//�t���O

		for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
			CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - hako;
			if (kyori.Length() < radius + 5000.0f) {
				isCreatePlanet = false;
			}
		}
		if (isCreatePlanet) {
			Meteo* meteo = NewGO<Meteo>(0, "Meteo");

			meteo->SetPosition(hako);
			//meteo->init(planet->p_position, P_skinModelRender, v);
		}
	}
}

