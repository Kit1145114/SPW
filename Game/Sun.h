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
	enum EState {
		eState_Low,		//光が弱い。
		eState_High,	//光が強い。
	};
	prefab::CSkinModelRender* p_skinModelRender = nullptr;
	prefab::CPointLight* p_Cpointlit = nullptr;
	CVector3 p_position = CVector3::Zero;
	float radius = { 30.0f };  //基本惑星の半径。
	float SunSize = 250.0f;    //SetScale;
	float angle = 0;           //回転。
	float G_limitar = { 50000.0f };//   Sunの重力（Ｇ）調整。
	float nizyou = { 1000.0f }; //   二乗調整。
	float m_timer = 0.0f;
	float m_emissionTimer = 0.0f;
	EState m_state = eState_Low;
	CVector3 emissionPointLigColorLow;		//光が弱い時のポイントライトのカラー。
	CVector3 emissionPointLigColorHigh;		//光が強い時のポイントライトのカラー。
	CVector3 emissionColorLow;		//光が弱い時のエミッションカラー。
	CVector3 emissionColorHigh;		//光が強い時のエミッションカラー。
};

