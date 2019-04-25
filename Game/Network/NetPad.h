#pragma once
#include "..\tkEngine\Input\tkPad.h"
#include "PNetworkLogic.h"
#include "PadRingBuffer.h"

class NetPad {
public:
	NetPad(int playerNum) : playerNum(playerNum) {};
	~NetPad() {};

	bool IsPress(EnButton button) const {
		return buff.getPad()->getPress(button);
	}

	bool IsTrigger(EnButton button) const {
		return buff.getPad()->getTrigger(button);
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

	void clearBuffer() {
		buff.clearBuffer();
	}

	bool hasNext() {
		return buff.hasNext();
	}

	void nextFlame() {
		buff.nextData();
	}

	void SetFromCPad(const CPad& pad);
	void SetFromArray(nByte* array);

	void sendState(PhotonLib::PNetworkLogic& network);
	unsigned int getBuffSize() {
		return buff.size;
	}
private:
	const int playerNum;

	PadRingBuffer buff;
};
