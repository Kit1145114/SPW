#include "stdafx.h"
#include "BigBlackHole.h"


BigBlackHole::BigBlackHole()
{
}


BigBlackHole::~BigBlackHole()
{
	if (effect != nullptr) {
		DeleteGO(effect);
	}
}

bool BigBlackHole::Start()
{
	m_game = Game::GetInstance();
	//�G�t�F�N�g���쐬�B
	effect = NewGO<prefab::CEffect>(0);
	//�G�t�F�N�g���Đ��B
	effect->Play(L"effect/BH.efk");
	effect->SetScale(scale*radius);
	effect->SetPosition(BBHposition);
	return true;
}

void BigBlackHole::Generate(CVector3 position, float magnification, float Search, float Limit)
{
	BigBlackHole* bh = NewGO<BigBlackHole>(0, "BigBlackHole");
	//�ۑ��B
	bh->position = position;
	bh->radius *= magnification;
	bh->Searchment = Search;//	BH�̏d�͔͈͂̒����B
	bh->G_limitar = Limit;//   BH�̏d�́i�f�j�����B
}

void BigBlackHole::Gravity()
{
	//Player�T�[�`�B
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//�v���C���[�����G�Ȃ�z������߂�B
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//�ΏۂƂ̋����𑪒�B
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - position;
			//�ΏۂƂ̋������قڒ��S�ł͋z������߂�B
			if (radius * Searchment / 10 < kyori.Length() && kyori.Length() < radius * Searchment) {
				//�f���S�ɉ�����Ύキ�A�߂���΋����B
				float G = radius * Searchment - kyori.Length();
				//�Ώۂɓn���d�́Bkyori��G��������G_limitar�Ő����������āA���]�i-1�j����Ώd�͂ƂȂ�B
				Game::GetInstance()->m_player[i]->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
				//�ΏۂƂ̋��������S�ɋ߂��Ȃ�����B
				if (kyori.Length() < radius * Searchment / 5) {
					//�j��B
					Game::GetInstance()->m_player[i]->Death();
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
			CVector3 kyori = Game::GetInstance()->memoryPP[i]->GetPosition() - position;
			//�ΏۂƂ̋������قڒ��S�ł͋z������߂�B
			if (radius * Searchment / 10 < kyori.Length() && kyori.Length() < radius * Searchment) {
				//�ΏۂƂ̋��������ȉ��ɂȂ�����B
				if (kyori.Length() < radius * Searchment) {
					//�f���S�ɉ�����Ύキ�A�߂���΋����B
					float G = radius * Searchment - kyori.Length();
					//�Ώۂɓn���d�́Bkyori��G��������G_limitar�Ő����������āA���]�i-1�j����Ώd�͂ƂȂ�B
					Game::GetInstance()->memoryPP[i]->SetPosition(((kyori*G) / G_limitar)*-1);
					//�ΏۂƂ̋��������S�ɋ߂��Ȃ�����B
					if (kyori.Length() < radius * Searchment / 5) {
						//�j��B
						Game::GetInstance()->memoryPP[i]->explosion();
					}
				}
			}
		}
	}
	//Star�T�[�`�B
	QueryGOs<Star>("Star", [&](Star* star)->bool {
		CVector3 Kyori = star->GetPosition() - position;
		if (Kyori.Length() < radius * Searchment) {
			m_game->SetStarCount(-1);
			star->Death();
		}
		return true;
	});
	//Bullet�T�[�`�B
	QueryGOs<Bullet>("PlayerBullet", [&](Bullet* b) ->bool {
		//�ΏۂƂ̋����𑪒�B
		CVector3 kyori = b->GetPosition() - position;
		//�ΏۂƂ̋��������ȉ��ɂȂ�����B
		if (kyori.Length() < radius * Searchment) {
			//�f���S�ɉ�����Ύキ�A�߂���΋����B
			float G = radius * Searchment - kyori.Length();
			//�Ώۂɓn���d�́Bkyori��G��������G_limitar�Ő����������āA���]�i-1�j����Ώd�͂ƂȂ�B
			b->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
		}
		return true;
	});
}

void BigBlackHole::Update()
{
	Gravity();
}
