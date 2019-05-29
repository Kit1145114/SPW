#pragma once
#include"Game.h"

class Game;
class Draw_Skazu : public IGameObject
{
public:
	Draw_Skazu();
	~Draw_Skazu();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc) override;
	void AddKazu(int kazu)
	{
		star += kazu;
	}
	void SetKazu(int kazu)
	{
		star = kazu;
	}
	void SetS_kazuPosition(float x, float y)
	{
		S_kazuposition.x = x;
		S_kazuposition.y = y;
	}
	void SetS_position(float x, float y)
	{
		Starposition.x = x;
		Starposition.y = y;
	}
	void SetColor(float x, float y, float z, float w)
	{
		Color.x = x;
		Color.y = y;
		Color.z = z;
		Color.w = w;
	}
	void SetStar(const wchar_t* star)
	{
		draw_S = star;
	}
private:
	prefab::CSpriteRender* Star = nullptr;
	prefab::CSpriteRender* Bullet = nullptr;
	CFont m_font;
	Game* m_game = nullptr;
	CVector2 S_kazuposition = CVector2::Zero;	//☆の数を出すポジション
	CVector3 Starposition = CVector3::Zero;
	CVector4 Color = { 0.0f,0.0f,0.0f,0.0f };
	int star = 0;
	const wchar_t* draw_S = nullptr;
};

