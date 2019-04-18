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
		*@brief	���X�e�B�b�N��X���̓��͗ʂ��擾�B
		*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
		*/
	float GetLStickXF() const {
		return buff.getStart()->m_lStickX;
	}
	/*!
	*@brief	���X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetLStickYF() const {
		return buff.getStart()->m_lStickY;
	}
	/*!
	*@brief	�E�X�e�B�b�N��X���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickXF() const {
		return buff.getStart()->m_rStickX;
	}
	/*!
	*@brief	�E�X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickYF() const {
		return buff.getStart()->m_rStickY;
	}

	/***�X�V�p�֐�***/
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
		float m_lStickX = 0.0f;		//!<���X�e�B�b�N��X���̓��͗ʁB
		float m_lStickY = 0.0f;		//!<���X�e�B�b�N��Y���̓��͗ʁB
		float m_rStickX = 0.0f;		//!<�E�X�e�B�b�N��X���̓��͗ʁB
		float m_rStickY = 0.0f;		//!<�E�X�e�B�b�N��Y���̓��͗ʁB
		bool m_press[enButtonNum] = {};
		bool m_trigger[enButtonNum] = {};
	};

private:
	const int playerNum;

	PadRingBuffer buff;

	unsigned int count=0;

	bool updated = false;
};
