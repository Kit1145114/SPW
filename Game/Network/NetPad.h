#pragma once
#include "..\tkEngine\Input\tkPad.h"
#include "PNetworkLogic.h"
#include "PadRingBuffer.h"

class NetPad {
public:
	NetPad(int playerNum) : playerNum(playerNum) {};
	~NetPad() {};

	bool IsPress(EnButton button) const {
		return buff.getStart()->m_press[button];
	}

	bool IsTrigger(EnButton button) const {
		return buff.getStart()->m_trigger[button];
	}

	/*!
		*@brief	左スティックのX軸の入力量を取得。
		*@return	-1.0～1.0の正規化された値を返す。
		*/
	float GetLStickXF() const {
		return buff.getStart()->m_lStickX;
	}
	/*!
	*@brief	左スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetLStickYF() const {
		return buff.getStart()->m_lStickY;
	}
	/*!
	*@brief	右スティックのX軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickXF() const {
		return buff.getStart()->m_rStickX;
	}
	/*!
	*@brief	右スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickYF() const {
		return buff.getStart()->m_rStickY;
	}

	/***更新用関数***/
	bool cacheIsEmpty() {
		return buff.isEmpty();
	}

	void nextFlame() {
		buff.moveStart();
	}

	void SetFromCPad(const CPad& pad);
	void SetFromArray(nByte* array);
	bool isUpdated() {
		return updated;
	}
	void resetUpdateFlag() {
		updated = false;
	}

	void sendState(PhotonLib::PNetworkLogic& network);

	struct PadData {
		float m_lStickX = 0.0f;		//!<左スティックのX軸の入力量。
		float m_lStickY = 0.0f;		//!<左スティックのY軸の入力量。
		float m_rStickX = 0.0f;		//!<右スティックのX軸の入力量。
		float m_rStickY = 0.0f;		//!<右スティックのY軸の入力量。
		bool m_press[enButtonNum] = {};
		bool m_trigger[enButtonNum] = {};
	};

private:
	const int playerNum;

	PadRingBuffer buff;

	unsigned int count=0;

	bool updated = false;
};
