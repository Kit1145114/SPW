#pragma once
class Planet : public IGameObject

{
public:
	Planet();
	~Planet();
	bool Start();
	void Update();
	void Move();
	void Death();
	static void Generate();
	void init(CVector3 position, prefab::CSkinModelRender* skinModelRender);

	CCharacterController p_CharaCon;
	CVector3 p_position;
	float r = { 30.0f };
	CVector3 scale = { 1.0f,1.0f,1.0f };
	CVector3 p_moveSpeed = CVector3::Zero;
	CQuaternion p_rotation = CQuaternion::Identity;
	
	prefab::CSkinModelRender* p_skinModelRender0 = nullptr;
};

