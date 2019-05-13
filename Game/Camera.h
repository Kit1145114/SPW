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
	Game* game = nullptr;
	CVector3 Tyuou = CVector3::Zero;
	float tyuou = 0;
	float Saityou = 0.0f;
	float st_kyori = 2000.0f;
	float MaxCamera = 10000.0f;
	float MinCamera = 5000.0f;
	float cameraUp = 0.0f;
	float up = 0.0f;
};

