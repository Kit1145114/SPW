#pragma once
namespace PhotonLib {
	class PJoinListener {
	public:
		/// <summary>
		/// �N�������������Ƃ��̏���
		/// </summary>
		/// <param name="playerNr">�v���C���[�ԍ�</param>
		virtual void onJoin(int playerNr) = 0;
	};
}