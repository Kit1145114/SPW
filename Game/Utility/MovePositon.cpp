#include "stdafx.h"
#include "MovePosition.h"

void MovePosition::Update() {
	if (state != moveEnd) {
		if (state == speedSave) {
			CVector3 firstLength = targetPos - nowPos;
			speed = firstLength * goSpeed;
			springPower = speed * -backSpeed;
			state = goTarget;
		}

		float delta = GameTime().GetFrameDeltaTime();

		if (waitTime > delta) {
			waitTime -= delta;
			return;
		}
		
		nowPos += speed * delta;

		CVector3 length = targetPos - nowPos;

		if (state != spring && length.Dot(speed) < 0) {
			state = spring;
		}

		if (state == spring) {
			speed += springPower * delta;
			if (length.Dot(springPower) < 0) {
				nowPos = targetPos;
				state = moveEnd;
			}
		}
	}
}