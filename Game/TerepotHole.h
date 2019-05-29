#pragma once
class TerepotHole : public IGameObject
{
public:
	TerepotHole();
	~TerepotHole();
	bool Start();
	void Update();
	void SetPosi(CVector3 posi) {
		m_position = posi;
	}
	CVector3 GetPosi() {
		return m_position;
	}
	prefab::CSkinModelRender* m_terepot = nullptr;
	void SetFilePath(const wchar_t* filepath)
	{
		modelFilePath = filepath;
	}
	void SetLinkTerepotHole(TerepotHole* hole)
	{
		linkTerepotHole = hole;
	}


private:
	std::wstring modelFilePath;
	int timer = 0;
	bool terepot_flag = true;
	CVector3 m_position = CVector3::Zero;
	CVector3 scale;
	TerepotHole* linkTerepotHole = nullptr; //つながっているテレポート。
};

