#pragma once
class RadarRing : public IGameObject
{
public:
	RadarRing();
	~RadarRing();
	bool Start();
	void Update();
	void SetPlayerRadar(const wchar_t* player, int num);
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSpriteRender* arrowSprite = nullptr;
	const wchar_t* draw_P = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 scale = CVector3::Zero;

	int pNum = 0;
	CVector4 color = {};
};

