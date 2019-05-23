#pragma once

class TrepotHole2 : public IGameObject
{
public:
	TrepotHole2();
	~TrepotHole2(); 
	bool Start();
	void Update();
	void SetPosition2(CVector3 m_pos2)
	{
		m_position2 = m_pos2;
	}
	CVector3 GetPosition2() 
	{
		return m_position2;
	}

	/*void SetInit( )
	{
	}*/
	
	prefab::CSkinModelRender* m_trepot2 = nullptr;
private:
	
	CVector3 m_position2 = CVector3::Zero;
	CVector3 scela;
	//int timer2 = 0;
	//bool m_trepot_flag2 = true; //ÉèÅ[ÉvÇ™égÇ¶ÇÈÇ©Ç«Ç§Ç©
};

