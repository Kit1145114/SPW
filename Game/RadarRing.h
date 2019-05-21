#pragma once
#include "Utility/CircleGaugeSp.h"

class Player;
class Camera;

class RadarRing : public IGameObject
{
public:
	RadarRing();
	~RadarRing();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;
	void SetPlayerRadar(const wchar_t* path, Player* player);
private:
	Camera* camera = nullptr;

	prefab::CSkinModelRender* m_skinModelRender = nullptr;//自機下の円

	prefab::CSpriteRender* arrowSprite = nullptr;//右スティックの矢印

	//残弾数ゲージとそのテクスチャ
	CShaderResourceView tex;
	CircleGaugeSp gaugeIn;

	const wchar_t* draw_P = nullptr;//自機下の円のモデルパス
	Player* player = nullptr;

	CVector4 color = {};//プレイヤーの色

	static constexpr float cameraScaleDev = 12000.0f;//カメラの遠近法の計算結果がでかすぎるのでこれで割る
};

