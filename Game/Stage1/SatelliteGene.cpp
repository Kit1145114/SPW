#include "stdafx.h"
#include "SatelliteGene.h"
#include "Satellite.h"

SatelliteGene::~SatelliteGene() {
}

void SatelliteGene::Update() {
	timer += GameTime().GetFrameDeltaTime();
	if (timer > interval) {
		//ランダムポップ。
		CVector3 hako;
		hako.x = Random().GetRandDouble() - 0.5f;
		hako.z = Random().GetRandDouble() - 0.5f;

		//ランダム生成する場所の制限。
		const float PosLimitx = 30000.0f*2;
		const float PosLimitz = 20000.0f*2;
		hako.x *= PosLimitx;
		hako.z *= PosLimitz;



		NewGO<Satellite>(0, "Satellite");
	}
}
