#pragma once

class Game;

class Star: public IGameObject
{
public:
	Star();
	~Star();
	void Update();
	void Push();
	void Rotation();
	void Death();
	void Pop(CVector3 position, CVector3 scale);
	void SunPop(CVector3 position, CVector3 scale);
	CVector3 GetPosition()
	{
		return m_position;
	}
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}
	void SetScale(CVector3 sca)
	{
		m_scale = sca;
	}
	int GetPoint() {
		return StarPoint;
	}
private:
	Game* m_game = nullptr;					//�Q�[��class�̃|�C���^�O�O
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = { 1.0f,1.0f,1.0f };
	CQuaternion m_rotation = CQuaternion::Identity;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CPointLight* p_Cpointlit = nullptr;//�����Ƃ炷���C�g�B
	int StarPoint = 1;
	float time = 0.0f;
	float time0 = 0.0f;
	float Limit = 5.0f;
	float StarScale = 125.0f;
	float angle = 0.0f;
};

