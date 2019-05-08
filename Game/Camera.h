#pragma once
class Player;

class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	void TOP();
	void Move();
	void SetKyori(float a)
	{
		st_kyori += a;
	}
	void SetPos(float p)
	{
		up = p;
	}
	float GetKyori()
	{
		return st_kyori;
	}
	float MaxCameraPos()
	{
		return MaxCamera;
	}
	float MinCameraPos()
	{
		return MinCamera;
	}
private:
	Player* m_player = nullptr;
	float st_kyori = 2000.0f;
	float MaxCamera = 10000.0f;
	float MinCamera = 1500.0f;
	float up = 0.0f;
	float Syoki = 5000.0f;
};

