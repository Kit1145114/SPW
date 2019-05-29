#pragma once
//#include "Game.h"
#include"Planet.h"

class Camera;

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
	void Flare();
	void HPCount();
	void Revival();
	void Update();
	float GetSize()
	{
		return Size;
	}
private:
	enum EState {
		eState_Low,		//光が弱い。
		eState_High,	//光が強い。
		eState_death,
	};
	prefab::CSkinModelRender* p_skinModelRender = nullptr;
	prefab::CPointLight* p_Cpointlit = nullptr;
	CVector3 p_position = CVector3::Zero;
	CVector3 scale = { 1.0f,1.0f,1.0f };
	float radius = { 7500.0f };				 //基本惑星の半径。
	float Maxradius = 7500.0f;
	float SunSize = 250.0f;					//SetScale;
	float angle = 0;						//回転。
	float G_limitar = { 50000.0f };			//Sunの重力（Ｇ）調整。
	float nizyou = { 1000.0f };				//二乗調整。
	float m_timer = 0.0f;
	float m_Deathtimer = 0.0f;				//死亡時間。
	float m_Revivaltimer = 10.0f;			//復活時間。
	float m_emissionTimer = 0.0f;
	EState m_state = eState_Low;
	CVector3 emissionPointLigColorLow;		//光が弱い時のポイントライトのカラー。
	CVector3 emissionPointLigColorHigh;		//光が強い時のポイントライトのカラー。
	CVector3 emissionColorLow;				//光が弱い時のエミッションカラー。
	CVector3 emissionColorHigh;				//光が強い時のエミッションカラー。
	prefab::CSoundSource* SoundSource = nullptr;//BGM用のサウンドソース。
	prefab::CSoundSource* SoundSource2 = nullptr;//BGM用のサウンドソース。
	prefab::CSoundSource* sunFlareSS = nullptr;	//太陽フレアの時のサウンド。
	int SunHP = 200;
	float Size = 1.0f;
	bool SunRevivalFlag = false;

	Camera* camera = nullptr;
	bool Sountziki = false;
	
};

