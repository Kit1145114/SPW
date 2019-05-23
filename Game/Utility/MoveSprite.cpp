#include "stdafx.h"
#include "MoveSprite.h"

void MoveSprite::Update() {
	movePos.Update();
	sprite.Update(movePos.getNowPos(), CQuaternion::Identity, CVector3::One);
}

void MoveSprite::PostRender(CRenderContext & rc) {
	sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
