#pragma once
#include "..\tkEngine\Input\tkPad.h"
#include "PNetworkLogic.h"

class NetPad{
public:
	NetPad(int playerNum) : playerNum(playerNum) {};
	~NetPad() {};

	bool IsPress(EnButton button) {
		return m_press[button];
	}

	bool IsTrigger(EnButton button) {
		return m_trigger[button];
	}

	/*!
		*@brief	左スティックのX軸の入力量を取得。
		*@return	-1.0～1.0の正規化された値を返す。
		*/
	float GetLStickXF() const {
		return m_lStickX;
	}
	/*!
	*@brief	左スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetLStickYF() const {
		return m_lStickY;
	}
	/*!
	*@brief	右スティックのX軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickXF() const {
		return m_rStickX;
	}
	/*!
	*@brief	右スティックのY軸の入力量を取得。
	*@return	-1.0～1.0の正規化された値を返す。
	*/
	float GetRStickYF() const {
		return m_rStickY;
	}

	/***更新用関数***/
	void SetFromCPad(const CPad& pad);
	void SetFromArray(nByte* array);
	bool isUpdated() {
		return updated;
	}
	void resetUpdateFlag() {
		updated = false;
	}

	void sendState(PhotonLib::PNetworkLogic& network);

private:
	const int playerNum;

	float m_lStickX = 0.0f;		//!<左スティックのX軸の入力量。
	float m_lStickY = 0.0f;		//!<左スティックのY軸の入力量。
	float m_rStickX = 0.0f;		//!<右スティックのX軸の入力量。
	float m_rStickY = 0.0f;		//!<右スティックのY軸の入力量。
	bool m_press[enButtonNum] = {};
	bool m_trigger[enButtonNum] = {};

	bool updated = false;
};
