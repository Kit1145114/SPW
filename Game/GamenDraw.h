#pragma once
#include"Game.h"
#include"SetumeiGamen.h"
#include"Title_2.h"

class Game;
class SetumeiGamen;
class Title_2;
class GamenDraw : public IGameObject
{
public:
	GamenDraw();
	~GamenDraw();

	void Update();
	void PostRender(CRenderContext& rc) override;
	void GemenDrawSound(int SoundNum);

private:
	CFont m_font;
	CVector2 m_position = CVector2::Zero;
	Game* m_game = nullptr;
	Title_2* tl2 = nullptr;
	prefab::CSoundSource * m_push = nullptr;
	int mode = 0;

	static constexpr float wordMaxScale = 1.3f;
	static constexpr float wordMinScale = 1.25f;
	float wordScale[2] = { wordMinScale ,wordMinScale };
};

