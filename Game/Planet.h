#pragma once
class Planet : public IGameObject

{
public:
	Planet();
	~Planet();
	bool Start();
	void Update();
	void Move();
	void Generate();
	CCharacterController p_CharaCon;
	CVector3 p_position[10];
	
	CVector3 scale = { 5.0f,3.0f,5.0f };
	CVector3 p_moveSpeed = CVector3::Zero;
	CQuaternion p_rotation = CQuaternion::Identity;

	prefab::CSkinModelRender* p_skinModelRender0 = nullptr;
};

