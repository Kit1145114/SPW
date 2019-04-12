#include "stdafx.h"
#include "GameWait.h"
#include "PNetworkLogic.h"

using namespace PhotonLib;

GameWait::GameWait() {}

GameWait::~GameWait() {
	delete network;
	/*for (int i = 0; i < iconArrayNum; i++) {
		DeleteGO(iconArray[i]);
	}*/
	DeleteGO(icon);
}

void GameWait::Init(PNetworkLogic * network) {
	inited = true;
	if (network != nullptr) {
		this->network = network;
	} else {
		this->network = new PNetworkLogic(appID, version);
	}
}

bool GameWait::Start() {
	if (!inited) {
		//NewGOÇµÇΩå„ÅAInitä÷êîÇé¿çsÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB
		return false;
	}

	const int width = Engine().GetGraphicsEngine().Get2DSpaceScreenWidth();
	const int height = Engine().GetGraphicsEngine().Get2DSpaceScreenHeight();
	icon = NewGO<prefab::CSpriteRender>(0);
	icon->Init(L"sprite/Icon.dds", 200.0f, 200.0f);
	icon->SetMulColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	/*for (int i = 0; i < 1; i++) {
		iconArray[i] = NewGO<prefab::CSpriteRender>(0);
		iconArray[i]->Init(L"sprite/Icon.dds",200.0f, 200.0f);
		iconArray[i]->SetMulColor({ 1.0f, 0.0f, 0.0f, 1.0f});
	}
	iconArray[0]->SetPosition(pos);*/
	/*iconArray[1]->SetPosition({ 0, 0, 0 });
	iconArray[2]->SetPosition({ 0, 0, 0 });
	iconArray[3]->SetPosition({ 0, 0, 0 });*/
	return true;
}

void GameWait::Update() {
	network->connect();
	network->Update();

	icon->SetMulColor(color);
	CQuaternion cq;
	cq.SetRotation(CVector3::AxisZ, 0.01);
	cq.Multiply(pos);
	icon->SetPosition(pos);

	if (Pad(0).IsTrigger(enButtonB)) {
		color = { 0,1,1,1 };
	}

	if (network->isError()) {
		icon->SetMulColor({1,1,1,1});
		return;
	}

	if (network->isConnecting()) {
		color = { 0,1,0,1 };
		network->joinOrCreateRoom("Room", 4);
	} else {
		return;
	}

	if (network->isRoomIn()) {
		color = { 0,0,1,1 };
	}
}
