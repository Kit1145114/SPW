#include "stdafx.h"
#include "Crown.h"

Crown::~Crown() {
	DeleteGO(model);
}

void Crown::Awake() {
	model = NewGO<prefab::CSkinModelRender>(0);
	model->Init(L"modelData/Crown.cmo");
	model->SetScale({ 6,6,6 });
}

void Crown::Update() {
	float delta = GameTime().GetFrameDeltaTime();

	speed += (0 - upDown)*0.2f;
	upDown += speed * delta;

	CQuaternion l_rot;
	l_rot.SetRotation(CVector3::AxisY, CMath::PI * delta);
	rot.Multiply(l_rot);
	model->SetRotation(rot);
}
