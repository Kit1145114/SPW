#pragma once
class Player;
class Game;
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	float MaxCameraPos()
	{
		return MaxCamera;
	}
	float MinCameraPos()
	{
		return MinCamera;
	}

	float getUpLength() {
		return cameraUp;
	}

	/// <summary>
	/// �J������h�炷�B
	/// </summary>
	/// <param name="power">�h��̑傫���B�U�ꕝ�B</param>
	/// <param name="spring">�h�ꂪ�߂鑬���B</param>
	/// <param name="decay">�����B�l���傫���قǑ����h�ꂪ���܂�B0�`1.0�B</param>
	void shake(float power, float spring, float decay);

private:

	Game* game = nullptr;
	float cameraUp = 0.0f;//�J�����̒n�ʂ���̋���

	//��@�Ǐ]���[�h�p(�l�b�g���[�N)
	void UpDownZoom();

	Player* m_player = nullptr;
	static constexpr float MaxCamera = 10000.0f;//�n�ʂ���̍ő勗��
	static constexpr float MinCamera = 5000.0f;//�n�ʂ���̍ŏ�����

	//�����@��1��ʓ��Ɏ��߂郂�[�h�p(���[�J��)
	void AutoZoom(const CVector3& center);
	CVector3 calcCenter();

	//�J�����̗h����s���֘A
	CVector3 shakeProcess();

	float beforeDot = 1;
	float shakeSpring = 0.0f;
	float shakeDecay = 0.0f;
	CVector3 shakeSpeed; //�h��̃X�s�[�h
	CVector3 shakePos; //�h�ꂪ�Ȃ������ꍇ�̒����_����̑��΍��W
};

