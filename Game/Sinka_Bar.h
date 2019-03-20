#pragma once
#include"Game.h"

class Game;
class Sinka_Bar : public IGameObject
{
public:
	Sinka_Bar();
	~Sinka_Bar();
	bool Start();
	void Update();
	//void PostRender(CRenderContext& renderContext) override;

private:
	Game * m_game = nullptr;
	prefab::CSpriteRender* sinka_bar = nullptr;
	prefab::CSpriteRender* sinka_gezi = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	//CShaderResourceView texture;
	float Max = 5.0f;
	float Min = 0.0f;
	float Now = 0.0f;
	bool Gezi = false;
};

