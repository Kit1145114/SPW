#pragma once
namespace PhotonLib {
	class PNetworkLogic;
}

/// <summary>
/// NewGO������AInit�֐������s���Ă��������B
/// </summary>
class GameWait : public IGameObject {
public:
	GameWait();
	~GameWait();

	/// <summary>
	/// NewGO������A���̃t���[���܂łɎ��s���Ă�������
	/// </summary>
	void Init(PhotonLib::PNetworkLogic* network = nullptr);
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;

private:
	static constexpr wchar_t* appID = L"0a51cad7-3a38-45c2-960d-98cbebf4e701"; //photon�ڑ��Ɏg�p����appID
	static constexpr wchar_t* version = L"alpha"; //�o�[�W�����A���R�Ɍ��߂Ă���

	PhotonLib::PNetworkLogic* network = nullptr;

	bool inited = false; //Init�֐������s�������ǂ����B
	bool disco = false;

	unsigned int flame = 0;

	const wchar_t* NetMessage = L"";
	CFont font;
};

