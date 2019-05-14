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
	void SetBulletKazu(int kazu)
	{
		bullet = kazu;
	}
	void SetBullet(const wchar_t* star)
	{
		draw_B = star;
	}
	void SetB_kazuPosition(float x, float y)
	{
		B_kazuposition.x = x;
		B_kazuposition.y = y;
	}
	void SetBulletposition(float x, float y)
	{
		BulletPosition.x = x;
		BulletPosition.y = y;
	}
private:
	prefab::CSpriteRender* Star = nullptr;
	prefab::CSpriteRender* Bullet = nullptr;
	CFont m_font;
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	CVector2 S_kazuposition = CVector2::Zero;
	CVector3 Starposition = CVector3::Zero;

	CVector2 B_kazuposition = CVector2::Zero;
	CVector3 BulletPosition = CVector3::Zero;

	CVector4 Color = { 0.0f,0.0f,0.0f,0.0f };
	int star = 0;
	int bullet = 0;
	const wchar_t* draw_S = nullptr;
	const wchar_t* draw_B = nullptr;
};

