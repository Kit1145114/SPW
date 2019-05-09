#pragma once
class RadarRing : public IGameObject
{
public:
	RadarRing();
	~RadarRing();
	bool Start();
	void Update();
	void SetPlayerRadar(const wchar_t* player)
	{
		draw_P = player;
	}
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	const wchar_t* draw_P = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 scale = CVector3::Zero;
};

