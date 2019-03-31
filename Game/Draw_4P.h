#pragma once
class Draw_4P : public IGameObject 
{
public:
	Draw_4P();
	~Draw_4P();
	bool Start();
	void Update();
	void SetDeath(bool a)
	{
		Death = a;
	}
	void SetPosition(int x, int y)
	{
		m_position.x = x;
		m_position.y = y;
	}
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	int timer = 0;
	bool Death = false;
	bool State = false;
};

