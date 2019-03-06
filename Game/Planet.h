#pragma once
class Planet : public IGameObject

{
public:
	Planet();
	~Planet();
	bool Start();
	void Update();
	void Move();
	static void Generate();
	void init(CVector3 position, prefab::CSkinModelRender* skinModelRender);
	CCharacterController p_CharaCon;
	CVector3 p_position;
	
	CVector3 scale = { 5.0f,3.0f,5.0f };
	CVector3 p_moveSpeed = CVector3::Zero;
	CQuaternion p_rotation = CQuaternion::Identity;

	prefab::CSkinModelRender* p_skinModelRender0 = nullptr;
};

