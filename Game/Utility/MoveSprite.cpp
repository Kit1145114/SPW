#include "stdafx.h"
#include "MoveSprite.h"


MoveSprite::MoveSprite() {
}


MoveSprite::~MoveSprite() {
}

void MoveSprite::Update() {
	if (state != moveEnd) {

		CVector3 length = targetPos - nowPos;
		if (state == speedSave) {
			speed = length * goSpeed;
			springPower = speed * -backSpeed;
			state = goTarget;
		}

		float delta = GameTime().GetFrameDeltaTime();
		nowPos += speed * delta;

		if (state == spring) {
			speed += springPower * delta;
			if (length.Dot(springPower) < 0) {
				nowPos = targetPos;
				state = moveEnd;
			}
		} else if (length.Dot(speed) < 0) {
			state = spring;
		}
	}
	sprite.Update(nowPos, CQuaternion::Identity, CVector3::One);
}

void MoveSprite::PostRender(CRenderContext & rc) {
	sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
