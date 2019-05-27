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
	float radius = { 30.0f };  //基本惑星の半径。
	float SunSize = 250.0f;    //SetScale;
	float angle = 0;           //回転。
	float G_limitar = { 50000.0f };//   Sunの重力（Ｇ）調整。
	float nizyou = { 1000.0f }; //   二乗調整。
};

