#pragma once
namespace PhotonLib {
	class PNetworkLogic;
}
class NetPadManager;

class GameWait : public IGameObject {
public:
	GameWait();
	~GameWait();

	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;

private:
	prefab::CSpriteRender* m_spriteRender = nullptr;

	static constexpr wchar_t* appID = L"0a51cad7-3a38-45c2-960d-98cbebf4e701"; //photon�ڑ��Ɏg�p����appID
	static constexpr wchar_t* version = L"alpha"; //�o�[�W�����A���R�Ɍ��߂Ă���
	bool read = false;

	bool allStart = false;

	CFont font;
};

