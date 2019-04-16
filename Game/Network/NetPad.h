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
		*@brief	���X�e�B�b�N��X���̓��͗ʂ��擾�B
		*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
		*/
	float GetLStickXF() const {
		return m_lStickX;
	}
	/*!
	*@brief	���X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetLStickYF() const {
		return m_lStickY;
	}
	/*!
	*@brief	�E�X�e�B�b�N��X���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickXF() const {
		return m_rStickX;
	}
	/*!
	*@brief	�E�X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickYF() const {
		return m_rStickY;
	}

	/***�X�V�p�֐�***/
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

	float m_lStickX = 0.0f;		//!<���X�e�B�b�N��X���̓��͗ʁB
	float m_lStickY = 0.0f;		//!<���X�e�B�b�N��Y���̓��͗ʁB
	float m_rStickX = 0.0f;		//!<�E�X�e�B�b�N��X���̓��͗ʁB
	float m_rStickY = 0.0f;		//!<�E�X�e�B�b�N��Y���̓��͗ʁB
	bool m_press[enButtonNum] = {};
	bool m_trigger[enButtonNum] = {};

	bool updated = false;
};
