#pragma once
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();

	CVector3 m_CameraPos = { 0.0f,0.0f,10.0f, };

};

