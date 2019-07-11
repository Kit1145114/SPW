#include "stdafx.h"
#include "BlackHole.h"
#include "Star.h"

BlackHole::BlackHole()
{
}

BlackHole::~BlackHole()
{
	if (effect != nullptr) {
		DeleteGO(effect);
	}
}

bool BlackHole::Start()
{
	//�V���O���g���ŃA�N�Z�X���邽�߁B
	m_game = Game::GetInstance();

	//�G�t�F�N�g���쐬�B
	effect = NewGO<prefab::CEffect>(0);
	//�G�t�F�N�g���Đ��B
	effect->Play(L"effect/BH.efk");
	scale = { 0.1f,0.1f,0.1f };
	//BH�̑傫���͂Ԃ������f���̑傫���ɔ�Ⴓ����B
	effect->SetScale(scale*radius);
	effect->SetPosition(m_position);
	//BH�J�E���g���Ă����B
	Game::GetInstance()->SetBHCount(1);
	effect->SetEffectFlag(true);
	return true;
}

void BlackHole::Generate(CVector3 position, float magnification)
{
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	//�ۑ��B
	//BH�����ꏊ�̎󂯓n���B
	bh->m_position = position;
	//BH�̑傫���͂Ԃ������f���̑傫���ɔ�Ⴓ����B
	bh->radius *= magnification / 500;
}

void BlackHole::Gravity()
{

	//Player�T�[�`�B
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//�v���C���[�����G�Ȃ�z������߂�B
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//�ΏۂƂ̋����𑪒�B
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			//�ΏۂƂ̋��������ȉ��ɂȂ�����B
			if (kyori.Length() < radius * Searchment * 1.2) {
				//BH���S�ƑΏۂƂ̋����B
				float G = radius * Searchment - kyori.Length();
				//BH�̏d�́i�f�j�����B
				G_limitar = { 50.0f };
				//�x�N�g���̌����B
				CVector3 kyori2 = kyori;
				kyori2.Normalize();
				//�ΏۂƂ̋������悷�邱�ƂŁ@�f���S�ɉ�����Ύキ�A�߂���΋����B
				G = G * G / BBHnizyou;
				//�v���C���[�֓n���x�N�g���B
				//kyori2 * G�@(����*�f) / G_limitar (�d�͂̒���)* -1 (���]����Β��S�ւƌ������d�͂ƂȂ�)�B
				Game::GetInstance()->m_player[i]->SetMoveSpeed(((kyori2 * G) / G_limitar) * -1);
				//�ΏۂƂ̋��������S�ɋ߂��Ȃ�����B
				if (kyori.Length() < radius * Searchment / 5) {
					//�j��B
					Game::GetInstance()->m_player[i]->AddHP(-100);
					Game::GetInstance()->m_player[i]->SetLABulletNum(-1);
				}
			}
		}
	}
	//Plamet�T�[�`�B
	for (int i = 0; i < Planetnumber_Num; i++) {
		//�Ώۂ�nullptr�łȂ���΁B
		if (Game::GetInstance()->memoryPP[i] != nullptr) {
			//�ΏۂƂ̋����𑪒�B
			CVector3 kyori = Game::GetInstance()->memoryPP[i]->GetPosition() - m_position;
			//�ΏۂƂ̋��������ȉ��ɂȂ�����B
			if (kyori.Length() < radius * Searchment) {
				//BH���S�ƑΏۂƂ̋����B
				float G = radius * Searchment - kyori.Length();
				//BH�̏d�́i�f�j�����B
				G_limitar = { 100.0f };
				//�x�N�g���̌����B
				CVector3 kyori2 = kyori;
				kyori2.Normalize();
				//�ΏۂƂ̋������悷�邱�ƂŁ@�f���S�ɉ�����Ύキ�A�߂���΋����B
				G = G * G / BBHnizyou;
				// �v���C���[�֓n���x�N�g���B
				//kyori2 * G�@(����*�f) / G_limitar (�d�͂̒���)*-1(���]����Β��S�ւƌ������d�͂ƂȂ�)�B
				Game::GetInstance()->memoryPP[i]->SetMoveSpeed(((kyori2 * G) / G_limitar) * -1);
				//�ΏۂƂ̋��������S�ɋ߂��Ȃ�����B
				if (kyori.Length() < radius * Searchment / 5) {
					//�j��B
					Game::GetInstance()->memoryPP[i]->explosion();
				}
			}
		}
	}
	//Star�T�[�`�B
	QueryGOs<Star>("Star", [&](Star* star)->bool {
		//�ΏۂƂ̋����𑪒�B
		CVector3 Kyori = star->GetPosition() - m_position;
		//�ΏۂƂ̋��������ȉ��ɂȂ�����B
		if (Kyori.Length() < radius * Searchment) {
			//�j��B
			m_game->SetStarCount(-1);
			star->Death();
		}
		return true;
	});
	//Bullet�T�[�`�B
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		//�ΏۂƂ̋����𑪒�B
		CVector3 kyori = b->GetPosition() - m_position;
		//�ΏۂƂ̋��������ȉ��ɂȂ�����B
		if (kyori.Length() < radius * Searchment) {
			//BH���S�ƑΏۂƂ̋����B
			float G = radius * Searchment - kyori.Length();
			//BH�̏d�́i�f�j�����B
			G_limitar = { 100.0f };
			//�x�N�g���̌����B
			CVector3 kyori2 = kyori;
			kyori2.Normalize();
			//�ΏۂƂ̋������悷�邱�ƂŁ@�f���S�ɉ�����Ύキ�A�߂���΋����B
			G = G * G / BBHnizyou;
			//�Ώۂ֓n���x�N�g���B
			//kyori2 * G�@(����*�f) / G_limitar (�d�͂̒���)*-1(���]����Β��S�ւƌ������d�͂ƂȂ�)�B
			b->SetMoveSpeed(((kyori2 * G) / G_limitar) * -1);
		}
		return true;
	});
	//���e�I�T�[�`�B
	QueryGOs<Meteo>("Meteo", [&](Meteo* m) ->bool {
		//�ΏۂƂ̋����𑪒�B
		CVector3 kyori = m->GetPosition() - m_position;
		//�ΏۂƂ̋��������ȉ��ɂȂ�����B
		if (kyori.Length() < radius * Searchment) {
			//BH���S�ƑΏۂƂ̋����B
			float G = radius * Searchment - kyori.Length();
			//BH�̏d�́i�f�j�����B
			G_limitar = { 600.0f };
			//�x�N�g���̌����B
			CVector3 kyori2 = kyori;
			kyori2.Normalize();
			//�ΏۂƂ̋������悷�邱�ƂŁ@�f���S�ɉ�����Ύキ�A�߂���΋����B
			G = G * G / BBHnizyou;
			//�Ώۂ֓n���x�N�g���B
			//kyori2 * G�@(����*�f) / G_limitar (�d�͂̒���)*-1(���]����Β��S�ւƌ������d�͂ƂȂ�)�B
			m->SetMoveSpeed(((kyori2 * G) / G_limitar) * -1);
			if (kyori.Length() < radius * Searchment / 5) {
				//�j��B
				m->Death();
			}
		}
		return true;
	});
}

void BlackHole::Count()
{
	if (Countflg == false) {
		timer += GameTime().GetFrameDeltaTime();
		//BH���������莞�Ԍo�ߌ�B
		if (timer > Deathtime) {
			//BH���ŁB
			DeathSize();
		}
	}
}

void BlackHole::Death()
{
	DeleteGO(this);
	//�����̃J�E���g�����炷�B
	Game::GetInstance()->SetBHCount(-1);
}

void BlackHole::PopSize()
{
	if (scale.x <= 1.0f
		&&timer < 8.0f) {
		//���t���[��0.01���Â傫���Ȃ�B
		scale += { 0.01f, 0.01f, 0.01f };
		effect->SetScale(scale*radius);
	}
}
void BlackHole::DeathSize() {

	if (scale.x >= 0.2f) {
		//���t���[��0.01���Â������Ȃ�B
		scale -= { 0.01f, 0.01f, 0.01f };
		effect->SetScale(scale*radius);
	}
	//scale.x >= 0.2f�ɂȂ�����B
	else {
		//�j��B
		Death();
	}

}

void BlackHole::Update()
{
	//�J�E���g�Ȃǂ͏����̒�~�B
	if (Game::GetInstance()->isWait())return;
	PopSize();
	Gravity();
	Count();
}
