#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"
#include "Fade.h"
#include "SansenGamen.h"

void StageIcon::Init(const wchar_t * image, CVector3 position, float wait) {
	movePos.setSpeed(8.0f, 40.0f);
	movePos.setTargetPos(position);
	position.y -= 500.0f;
	movePos.setNowPos(position);
	movePos.setWaitTime(wait);

	texture.CreateFromDDSTextureFromFile(image);
	sprite.Init(texture, 250, 150);
	sprite.Update(position, CQuaternion::Identity, CVector3::One);
};



StageSelect::~StageSelect() {
	DeleteGO(selectSprite);
	DeleteGO(backSprite);
	DeleteGO(titleSprite);
}

bool StageSelect::Start() {
	assert(sansenKazu > 0 && "setSansenKazu(int)で参戦人数を設定してください");

	if (backSprite == nullptr) {
		backSprite = NewGO<prefab::CSpriteRender>(0);
		backSprite->Init(L"sprite/BackTile.dds", MainCamera2D().GetWidth(), MainCamera2D().GetHeight());
	}

	titleSprite = NewGO<MoveSprite>(1);
	titleSprite->Init(L"sprite/StageSelect.dds", MainCamera2D().GetWidth(), 147.6f);
	titleSprite->setNowPos({0,500,0});
	titleSprite->setTargetPos({0,240,0});
	titleSprite->setSpeed(4.0f, 16.0f);

	CVector3 pos = { -400, 30, 0 };
	for (int i = 0; i < iconNum-1; i++) {
		wchar_t path[20];
		swprintf(path, L"sprite/Stage%d.dds", i + 1);
		iconArray[i].Init(path, pos, i * 0.1f);
		pos.x += 400;
		if (pos.x > 500) {
			pos.x = -400;
			pos.y -= 250;
		}
	}
	iconArray[iconNum-1].Init(L"sprite/RandomStage.dds", pos, (iconNum-1)*0.1f);

	selectSprite = NewGO<MoveSprite>(1);
	selectSprite->Init(L"sprite/Selector.dds", 270, 200);
	selectSprite->setNowPos(iconArray[0].getNowPos());
	selectSprite->setTargetPos(iconArray[0].getTargetPos());
	selectSprite->setSpeed(8.0f, 40.0f);

	Fade::fadeOut();
	return true;
}

void StageSelect::Update() {
	//参戦画面に戻る(実際に遷移)
	if (waitSansen > 0.0f) {
		waitSansen -= GameTime().GetFrameDeltaTime();
		if (waitSansen <= 0.0f) {
			NewGO<SansenGamen>(1)->setBackGround(backSprite);
			backSprite = nullptr;
			DeleteGO(this);
		}
		return;
	}


	//参戦画面に戻る(操作)
	if (Pad(0).IsTrigger(enButtonB)) {
		finishAnim();
		waitSansen = 0.3f;
	}

	//選んだステージでゲーム開始
	if (Pad(0).IsTrigger(enButtonA)) {
		finishAnim();
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

	//ステージを選ぶ
	int oldSelect = selectNumber;
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
	if (oldSelect != selectNumber) {
		selectSprite->setTargetPos(iconArray[selectNumber].getTargetPos());
	}
}

void StageSelect::PostRender(CRenderContext & rc) {
	for (int i = 0; i < iconNum; i++) {
		iconArray[i].Update();
		iconArray[i].draw(rc);
	}
}
//効果音
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

void StageSelect::finishAnim() {
	titleSprite->setTargetPos({ 0, 500, 0 });
	for (int i = 0; i < iconNum; i++) {
		iconArray[i].finishAnim((iconNum -1 - i)*0.03f);
	}
	selectSprite->setTargetPos(selectSprite->getNowPos() + CVector3(0, -500, 0));
}
