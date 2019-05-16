#pragma once
#include "BlackHole.h"

class BigBlackHole : public BlackHole
{
public:
	BigBlackHole();
	~BigBlackHole();
	bool Start();
	void Update();

private:
	CVector3 BBHposition = { 0.0f,  0.0f,  0.0f };;
	CVector3 BBHscale = { 100.0f,100.0f,100.0f };
	float BBHradius = { 100.0f };     //	基本惑星の半径。
	float BBHSearchment = { 15000.0f };//	BBHの重力範囲の調整。
	float BBHG_limitar = { 100000.0f };//   BBHの重力（Ｇ）調整。
};

