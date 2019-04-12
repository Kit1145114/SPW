#pragma once
namespace PhotonLib {
	class PNetworkLogic;
}

/// <summary>
/// NewGOした後、Init関数を実行してください。
/// </summary>
class GameWait : public IGameObject {
public:
	GameWait();
	~GameWait();

	/// <summary>
	/// NewGOした後、次のフレームまでに実行してください
	/// </summary>
	void Init(PhotonLib::PNetworkLogic* network = nullptr);
	bool Start() override;
	void Update() override;

private:
	static constexpr wchar_t* appID = L"0a51cad7-3a38-45c2-960d-98cbebf4e701"; //photon接続に使用するappID
	static constexpr wchar_t* version = L"alpha"; //バージョン、自由に決めていい

	PhotonLib::PNetworkLogic* network = nullptr;

	bool inited = false; //Init関数を実行したかどうか。

	static constexpr int iconArrayNum = 4;
	prefab::CSpriteRender* icon;
	CVector4 color = {1,0,0,1};
	CVector3 pos = {0, 100, 0};
};

