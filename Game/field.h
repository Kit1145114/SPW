#pragma once
class field : public IGameObject
{
public:
	field();
	~field();
	bool Start();
	void Update();

	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSkinModelRender* Haikei = nullptr;
	//静的物理オブジェクト。
	CPhysicsStaticObject m_phyStaticObject;
	CVector3 scale = { 1.0f,1.0f,1.0f };
	CVector3 pos = { 0.0f, -35.0f, 0.0f };
	CVector3 h_pos = { 0.0f, -2000.0f, 0.0f };
	CShader psShader;
};

