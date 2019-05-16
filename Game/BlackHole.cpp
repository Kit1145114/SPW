#include "stdafx.h"
#include "BlackHole.h"
#include "Star.h"

BlackHole::BlackHole()
{
}


BlackHole::~BlackHole()
{
	if (effect !=nullptr) {
		DeleteGO(effect);
	}
}

bool BlackHole::Start()
{
	m_game = Game::GetInstance();

	//�G�t�F�N�g���쐬�B
	effect = NewGO<prefab::CEffect>(0);
	//�G�t�F�N�g���Đ��B
	effect->Play(L"effect/BH.efk");
	effect->SetScale(scale*radius);
	effect->SetPosition(m_position);
	return true;
}

void BlackHole::Generate(CVector3 position, float magnification)
{
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	//�ۑ��B
	bh->m_position = position;
	bh->radius *= magnification/500;
}

void BlackHole::Generate2(CVector3 position, float magnification)
{
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	//�ۑ��B
	bh->m_position = position;
	bh->radius *= magnification / 500;
	bh->Countflg = true;  //true�ɂ��邱�ƂŎ��R���ł��Ȃ��Ȃ�B
}

void BlackHole::Move()
{
	//Player�T�[�`�B
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		//�v���C���[�����G�Ȃ�z������߂�B
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//�ΏۂƂ̋����𑪒�B
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			//�ΏۂƂ̋������قڒ��S�ł͋z������߂�B
				if (radius * Searchment / 6<kyori.Length()&& kyori.Length() < radius * Searchment) {
					//�f���S�ɉ�����Ύキ�A�߂���΋����B
					float G = radius * Searchment - kyori.Length();
					//�Ώۂɓn���d�́Bkyori��G��������G_limitar�Ő����������āA���]�i-1�j����Ώd�͂ƂȂ�B
					Game::GetInstance()->m_player[i]->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
					//�ΏۂƂ̋��������S�ɋ߂��Ȃ�����B
					if (kyori.Length() < radius * Searchment / 3) {
						//�j��B
						Game::GetInstance()->m_player[i]->Death();
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
				//�f���S�ɉ�����Ύキ�A�߂���΋����B
				float G = radius * Searchment - kyori.Length();
				//�Ώۂɓn���d�́Bkyori��G��������G_limitar�Ő����������āA���]�i-1�j����Ώd�͂ƂȂ�B
				Game::GetInstance()->memoryPP[i]->SetPosition(((kyori*G) / G_limitar)*-1);
				//�ΏۂƂ̋��������S�ɋ߂��Ȃ�����B
				if (kyori.Length() < radius * Searchment / 3) {
					//�j��B
					Game::GetInstance()->memoryPP[i]->explosion();
				}
			}
		}
	}
	//Star�T�[�`�B
	QueryGOs<Star>("Star", [&](Star* star)->bool {
		CVector3 Kyori = star->GetPosition() - m_position;
		if (Kyori.Length() < radius * Searchment) {
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
			//�f���S�ɉ�����Ύキ�A�߂���΋����B
			float G = radius * Searchment - kyori.Length();
			//�Ώۂɓn���d�́Bkyori��G��������G_limitar�Ő����������āA���]�i-1�j����Ώd�͂ƂȂ�B
			b->SetMoveSpeed(((kyori*G) / G_limitar)*-1);
		}
		return true;
	});
}

void BlackHole::Gravity()
{

}

void BlackHole::Count()
{
	if (Countflg == false) {
		timer++;
		if (timer > 720) {
			Death();
		}
	}
}

void BlackHole::Death()
{
	DeleteGO(this);
	//effect = nullptr;
}

void BlackHole::Update()
{
	Move();
	Count();
}
