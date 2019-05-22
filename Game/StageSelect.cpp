#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"
#include "Fade.h"
#include "SansenGamen.h"

StageSelect::~StageSelect() {
}

bool StageSelect::Start() {
	assert(sansenKazu > 0 && "setSansenKazu(int)Ç≈éQêÌêlêîÇê›íËÇµÇƒÇ≠ÇæÇ≥Ç¢");

	backTexture.CreateFromDDSTextureFromFile(L"sprite/StageSelect.dds");
	backSprite.Init(backTexture, MainCamera2D().GetWidth(),MainCamera2D().GetHeight());
	selectTexture.CreateFromDDSTextureFromFile(L"sprite/Selector.dds");
	selectSprite.Init(selectTexture, 270, 200);

	CVector3 pos = { -400, 30, 0 };
	for (int i = 0; i < iconNum-1; i++) {
		wchar_t path[20];
		swprintf(path, L"sprite/Stage%d.dds", i + 1);
		iconArray[i].Init(path, pos);
		pos.x += 400;
		if (pos.x > 500) {
			pos.x = -400;
			pos.y -= 250;
		}
	}
	iconArray[iconNum-1].Init(L"sprite/RandomStage.dds", pos);
	/*iconArray[0].setStageFunc([&]() {
	});
	iconArray[1].setStageFunc([&]() {
	});
	iconArray[2].setStageFunc([&]() {
	});
	iconArray[3].setStageFunc([&]() {
	});
	iconArray[4].setStageFunc([&]() {
	});*/

	Fade::fadeOut();
	return true;
}

void StageSelect::Update() {
	if (Pad(0).IsTrigger(enButtonB)) {
		Fade::fadeIn([&]() {
			NewGO<SansenGamen>(1);
			DeleteGO(this);
		});
	}
	if (Pad(0).IsTrigger(enButtonA)) {
		Fade::fadeIn([&]() {
			Game* game = NewGO<Game>(0, "Game");
			game->SetSanSenkazu(sansenKazu);
			if (selectNumber < iconNum - 1) {
				game->setStage(selectNumber);
			} else {
				game->setStage(Random().GetRandInt() % iconNum - 1);
			}
			DeleteGO(this);
		});
		Sound(1);
		return;
	}
	if (Pad(0).IsTrigger(enButtonRight)) {
		selectNumber++;
		Sound(0);
	}
	if (Pad(0).IsTrigger(enButtonLeft)) {
		selectNumber--;
		Sound(0);
	}
	if (Pad(0).IsTrigger(enButtonUp)) {
		selectNumber -= 3;
		Sound(0);
	}
	if (Pad(0).IsTrigger(enButtonDown)) {
		selectNumber += 3;
		Sound(0);
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
//å¯â âπ
void StageSelect::Sound(int SoundNum)
{
	if (SoundNum == 0) {
		m_push = NewGO<prefab::CSoundSource>(0);
		m_push->Init(L"sound/piko.wav");
		m_push->Play(false);
	}
	if (SoundNum == 1) {
		m_push = NewGO<prefab::CSoundSource>(0);
		m_push->Init(L"sound/tugihe.wav");
		m_push->Play(false);
	}
}