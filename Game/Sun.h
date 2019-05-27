#pragma once
//#include "Game.h"
#include"Planet.h"

class Sun : public IGameObject
{
public:
	Sun();
	~Sun();
	bool Start();
	void Move();
	void Reflection();
	void Rotation();
	void Light();
	void Update();
private:
	prefab::CSkinModelRender* p_skinModelRender = nullptr;
	prefab::CPointLight* p_Cpointlit = nullptr;
	CVector3 p_position = CVector3::Zero;
	float radius = { 30.0f };  //��{�f���̔��a�B
	float SunSize = 250.0f;    //SetScale;
	float angle = 0;           //��]�B
	float G_limitar = { 50000.0f };//   Sun�̏d�́i�f�j�����B
	float nizyou = { 1000.0f }; //   ��撲���B
};

