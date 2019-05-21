#pragma once
#include "Utility/CircleGaugeSp.h"

class Player;
class Camera;

class RadarRing : public IGameObject
{
public:
	RadarRing();
	~RadarRing();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& rc) override;
	void SetPlayerRadar(const wchar_t* path, Player* player);
private:
	Camera* camera = nullptr;

	prefab::CSkinModelRender* m_skinModelRender = nullptr;//���@���̉~

	prefab::CSpriteRender* arrowSprite = nullptr;//�E�X�e�B�b�N�̖��

	//�c�e���Q�[�W�Ƃ��̃e�N�X�`��
	CShaderResourceView tex;
	CircleGaugeSp gaugeIn;

	const wchar_t* draw_P = nullptr;//���@���̉~�̃��f���p�X
	Player* player = nullptr;

	CVector4 color = {};//�v���C���[�̐F

	static constexpr float cameraScaleDev = 12000.0f;//�J�����̉��ߖ@�̌v�Z���ʂ��ł�������̂ł���Ŋ���
};

