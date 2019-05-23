#pragma once

class TrepotHole : public IGameObject
{
public:
	TrepotHole();
	~TrepotHole();
	bool Start();
	void Update();
	void SetPosition(CVector3 m_pos)
	{
		m_position = m_pos;
	}
	CVector3 GetPosition() 
	{
		return m_position;
	}

	void TasuTime(float m_timer)
	{
		timer += m_timer;
	}
	void SetTime(float m_time)
	{
		timer = m_time;
	}
	int GetTime()
	{
		return timer;
	}

	void SetTrepotFlag(bool trepo_flag)
	{
		m_trepot_flag = trepo_flag;
	}
	bool GetTrepotFlag()
	{
		return m_trepot_flag;
	}

	prefab::CSkinModelRender* m_trepot = nullptr;
private:

	CVector3 m_position = CVector3::Zero;
	CVector3 scela;
	float timer = 0;
	bool m_trepot_flag = true;
};

