#pragma once
namespace PhotonLib {
	class PNetworkLogic;
}
class NetPadManager;

/// <summary>
/// NewGOした後、Init関数を実行してください。
/// </summary>
class GameWait : public IGameObject {
public:
	GameWait();
	~GameWait();

	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;

private:
	static constexpr wchar_t* appID = L"0a51cad7-3a38-45c2-960d-98cbebf4e701"; //photon接続に使用するappID
	static constexpr wchar_t* version = L"alpha"; //バージョン、自由に決めていい

	PhotonLib::PNetworkLogic* network = nullptr;

	bool roomIn = false; //入室までを終えたかどうか

	CFont font;
};

