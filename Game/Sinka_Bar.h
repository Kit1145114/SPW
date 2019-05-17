#pragma once
#include"Game.h"
#include"Player.h"
class Game;
class Player;

class Sinka_Bar : public IGameObject
{
public:
	Sinka_Bar();
	~Sinka_Bar();
	bool Start();
	void Update();
	void SetbarPosition(float x, float y)
	{
		bar_position.x = x;
		bar_position.y = y;
	}
	void SetgeziPosition(float x, float y)
	{
		gezi_position.x = x;
		gezi_position.y = y;
	}
	void AddStarCount(int star)
	{
		StarCount += star;
	}
private:
	Game * m_game = nullptr;
	Player* m_player[4] = { nullptr };
	prefab::CSpriteRender* sinka_bar = nullptr;
	prefab::CSpriteRender* sinka_gezi = nullptr;
	CVector3 bar_position = CVector3::Zero;
	CVector3 bar_scale = CVector3::Zero;
	CVector3 gezi_position = CVector3::Zero;
	CVector3 gezi_scale = CVector3::Zero;
	//CShaderResourceView texture;
	int StarCount = 0;
	float Max = 5.0f;
	float Min = 0.0f;
	float Now = 0.0f;
	float gezi = 0.0f;
	bool Gezi = false;
};

