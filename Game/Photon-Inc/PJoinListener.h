#pragma once
namespace PhotonLib {
	class PJoinListener {
	public:
		/// <summary>
		/// 誰かが入室したときの処理
		/// </summary>
		/// <param name="playerNr">プレイヤー番号</param>
		virtual void onJoin(int playerNr) = 0;
	};
}