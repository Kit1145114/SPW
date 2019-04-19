#pragma once
#include "..\tkEngine\Input\tkPad.h"
#include "PNetworkLogic.h"
#include "PadRingBuffer.h"

class NetPad {
public:
	NetPad(int playerNum) : playerNum(playerNum) {};
	~NetPad() {};

	bool IsPress(EnButton button) const {
		return buff.getPad()->m_press[button];
	}

	bool IsTrigger(EnButton button) const {
		return buff.getPad()->m_trigger[button];
	}

	/*!
		*@brief	左スティックのX軸の入力量を取得。
		*@return	-1.0～1.0の正規化された値を返す。
		*/
	float GetLStickXF() const {
		return buff.getPad()->m_lStickX;
	}
	/*!
	*@brief	左スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetLStickYF() const {
		return buff.getPad()->m_lStickY;
	}
	/*!
	*@brief	右スティックのX軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickXF() const {
		return buff.getPad()->m_rStickX;
	}
	/*!
	*@brief	右スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickYF() const {
		return buff.getPad()->m_rStickY;
	}

	/*nByte GetFlameNum() const {
		return buff.getPad()->flameNum;
	}*/

	/***更新用関数***/

	bool hasNext() {
		return buff.hasNext();
	}

	void nextFlame() {
		buff.nextData();
	}

	void SetFromCPad(const CPad& pad/*, nByte flame*/);
	void SetFromArray(nByte* array/*, nByte flame*/);
	bool isUpdated() {
		return updated;
	}
	void resetUpdateFlag() {
		updated = false;
	}

	void sendState(PhotonLib::PNetworkLogic& network/*, nByte flame*/);

private:
	const int playerNum;

	PadRingBuffer buff;

	unsigned int count=0;

	bool updated = false;
};
