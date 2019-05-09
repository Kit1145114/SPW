#pragma once
#include"Game.h"
#include"SetumeiGamen.h"
class Game;
class SetumeiGamen;
class GamenDraw : public IGameObject
{
public:
	GamenDraw();
	~GamenDraw();

	void Update();
	void PostRender(CRenderContext& rc) override;

private:
	CFont m_font;
	CVector2 m_position = CVector2::Zero;
	Game* m_game = nullptr;
	prefab::CSoundSource * m_push = nullptr;
	int mode = 0;
};

