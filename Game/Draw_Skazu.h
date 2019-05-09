#pragma once
#include"Game.h"
#include"Player.h"

class Game;
class Player;

class Draw_Skazu : public IGameObject
{
public:
	Draw_Skazu();
	~Draw_Skazu();
	void Update();
	void PostRender(CRenderContext& rc) override;
	void AddKazu(int kazu)
	{
		S_kazu += kazu;
	}
	void SetKazu(int kazu)
	{
		S_kazu = kazu;
	}
	void SetPosition(float x, float y)
	{
		m_position.x = x;
		m_position.y = y;
	}
	void SetColor(float x, float y, float z, float w)
	{
		Color.x = x;
		Color.y = y;
		Color.z = z;
		Color.w = w;
	}
private:
	CFont m_font;
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	CVector2 m_position = CVector2::Zero;
	CVector4 Color = { 0.0f,0.0f,0.0f,0.0f };
	int S_kazu = 0;
};

