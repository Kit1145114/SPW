#include "stdafx.h"
#include "BlackHole.h"


BlackHole::BlackHole()
{
}


BlackHole::~BlackHole()
{
	DeleteGO(effect);
}

bool BlackHole::Start()
{
	m_game = Game::GetInstance();

	//�G�t�F�N�g���쐬�B
	effect = NewGO<prefab::CEffect>(0);
	//�G�t�F�N�g���Đ��B
	effect->Play(L"effect/BH.efk");
	CVector3 scale = { 1.0f,1.0f,1.0f };
	effect->SetScale(scale*radius);
	effect->SetPosition(m_position);
	return true;
}

void BlackHole::Generate(CVector3 position, float magnification)
{
	//�|�W�V�����̕ۑ��B
	BlackHole* bh = NewGO<BlackHole>(0, "BlackHole");
	bh->m_position = position;
	bh->radius *= magnification/500;
}

void BlackHole::Move()
{
	//Player�T�[�`�B
	for (int i = 0; i < Game::GetInstance()->GetSansenKazu(); i++) {
		if (Game::GetInstance()->m_player[i]->GetMuteki() == false) {
			//�ΏۂƂ̋����𑪒�B
			CVector3 kyori = Game::GetInstance()->m_player[i]->GetPosition() - m_position;
			//�ΏۂƂ̋��������ȉ��ɂȂ�����B
			if (kyori.Length() < radius * Searchment) {
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
	timer++;
	if (timer >360) {
		Death();
	}
}

void BlackHole::Death()
{
	DeleteGO(this);
}

void BlackHole::Update()
{
	Move();
	//Count();
}
