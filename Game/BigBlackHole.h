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
	float BBHradius = { 100.0f };     //	î{f¯Ì¼aB
	float BBHSearchment = { 15000.0f };//	BBHÌdÍÍÍÌ²®B
	float BBHG_limitar = { 100000.0f };//   BBHÌdÍifj²®B
};

