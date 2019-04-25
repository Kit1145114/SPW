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
