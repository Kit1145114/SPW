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

private:
	static constexpr wchar_t* appID = L"0a51cad7-3a38-45c2-960d-98cbebf4e701"; //photon�ڑ��Ɏg�p����appID
	static constexpr wchar_t* version = L"alpha"; //�o�[�W�����A���R�Ɍ��߂Ă���

	PhotonLib::PNetworkLogic* network = nullptr;

	bool inited = false; //Init�֐������s�������ǂ����B

	static constexpr int iconArrayNum = 4;
	prefab::CSpriteRender* icon;
	CVector4 color = {1,0,0,1};
	CVector3 pos = {0, 100, 0};
};

