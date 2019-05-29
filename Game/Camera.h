#pragma once
class Player;
class Game;
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	float MaxCameraPos()
	{
		return MaxCamera;
	}
	float MinCameraPos()
	{
		return MinCamera;
	}

	float getUpLength() {
		return cameraUp;
	}

	/// <summary>
	/// カメラを揺らす。
	/// </summary>
	/// <param name="power">揺れの大きさ。振れ幅。</param>
	/// <param name="spring">揺れが戻る速さ。</param>
	/// <param name="decay">減衰。値が大きいほど早く揺れが収まる。0～1.0。</param>
	void shake(float power, float spring, float decay);

private:

	Game* game = nullptr;
	float cameraUp = 0.0f;//カメラの地面からの距離

	//一機追従モード用(ネットワーク)
	void UpDownZoom();

	Player* m_player = nullptr;
	static constexpr float MaxCamera = 10000.0f;//地面からの最大距離
	static constexpr float MinCamera = 5000.0f;//地面からの最小距離

	//複数機を1画面内に収めるモード用(ローカル)
	void AutoZoom(const CVector3& center);
	CVector3 calcCenter();

	//カメラの揺れを行う関連
	CVector3 shakeProcess();

	float beforeDot = 1;
	float shakeSpring = 0.0f;
	float shakeDecay = 0.0f;
	CVector3 shakeSpeed; //揺れのスピード
	CVector3 shakePos; //揺れがなかった場合の注視点からの相対座標
};

