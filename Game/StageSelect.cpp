#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"

StageSelect::~StageSelect() {
}

bool StageSelect::Start() {
	assert(sansenKazu > 0 && "setSansenKazu(int)で参戦人数を設定してください");

	backTexture.CreateFromDDSTextureFromFile(L"sprite/StageSelect.dds");
	backSprite.Init(backTexture, MainCamera2D().GetWidth(),MainCamera2D().GetHeight());
	selectTexture.CreateFromDDSTextureFromFile(L"sprite/Selector.dds");
	selectSprite.Init(selectTexture, 270, 200);

	CVector3 pos = { -400, 100, 0 };
	for (int i = 0; i < iconNum; i++) {
		wchar_t path[20];
		swprintf(path, L"sprite/Stage%d.dds", i + 1);
		iconArray[i].Init(path, pos);
		pos.x += 400;
		if (pos.x > 500) {
			pos.x = -400;
			pos.y -= 300;
		}
	}
	iconArray[0].setStageFunc([&]() {
		NewGO<Game>(0, "Game")->SetSanSenkazu(sansenKazu); DeleteGO(this);
	});
	iconArray[1].setStageFunc([&]() {
		//ここにステージ生成コードを書いてください
	});
	iconArray[2].setStageFunc([&]() {
		//ここにステージ生成コードを書いてください
	});
	iconArray[3].setStageFunc([&]() {
		//ここにステージ生成コードを書いてください
	});
	iconArray[4].setStageFunc([&]() {
		//ここにステージ生成コードを書いてください
	});
	return true;
}

void StageSelect::Update() {
	if (Pad(0).IsTrigger(enButtonA)) {
		iconArray[selectNumber].goStage();
		return;
	}
	if (Pad(0).IsTrigger(enButtonRight)) {
		selectNumber++;
	}
	if (Pad(0).IsTrigger(enButtonLeft)) {
		selectNumber--;
	}
	if (Pad(0).IsTrigger(enButtonUp)) {
		selectNumber -= 3;
	}
	if (Pad(0).IsTrigger(enButtonDown)) {
		selectNumber += 3;
	}
	if (selectNumber < 0) {
		selectNumber = iconNum + (selectNumber % iconNum);
	} else if (selectNumber >= iconNum) {
		selectNumber %= iconNum;
	}
}

void StageSelect::PostRender(CRenderContext & rc) {
	backSprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	for (int i = 0; i < iconNum; i++) {
		if (selectNumber == i) {
			selectSprite.Update(iconArray[i].getPos(), CQuaternion::Identity, CVector3::One);
			selectSprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
		}
		iconArray[i].draw(rc);
	}
}