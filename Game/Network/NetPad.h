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
		*@brief	���X�e�B�b�N��X���̓��͗ʂ��擾�B
		*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
		*/
	float GetLStickXF() const {
		return buff.getPad()->m_lStickX;
	}
	/*!
	*@brief	���X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetLStickYF() const {
		return buff.getPad()->m_lStickY;
	}
	/*!
	*@brief	�E�X�e�B�b�N��X���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickXF() const {
		return buff.getPad()->m_rStickX;
	}
	/*!
	*@brief	�E�X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickYF() const {
		return buff.getPad()->m_rStickY;
	}

	/*nByte GetFlameNum() const {
		return buff.getPad()->flameNum;
	}*/

	/***�X�V�p�֐�***/

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
