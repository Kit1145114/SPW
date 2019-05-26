#include "stdafx.h"
#include "TrepotHole.h"
#include "TrepotHole2.h"
#include "Game.h"



TrepotHole::TrepotHole()
{
}
TrepotHole::~TrepotHole()
{
	DeleteGO(m_trepot);
}
bool TrepotHole::Start()
{
	
	//m_trepot->Init(L"modelData/terepot.cmo"); //����(��蒼��)
	Game::GetInstance()->tere[0]->m_trepot = NewGO<prefab::CSkinModelRender>(0);
	Game::GetInstance()->tere[0]->m_trepot->Init(L"modelData/terepot.cmo"); //��
	Game::GetInstance()->tere[1]->m_trepot = NewGO<prefab::CSkinModelRender>(0);
	Game::GetInstance()->tere[1]->m_trepot->Init(L"modelData/terepot2.cmo"); //��
	Game::GetInstance()->tere[2]->m_trepot = NewGO<prefab::CSkinModelRender>(0);
	Game::GetInstance()->tere[2]->m_trepot->Init(L"modelData/terepot3.cmo"); //��
	

	scela = { 45.0, 45.0, 45.0 };  //�傫���@
	m_trepot->SetPosition(m_position);
	m_trepot->SetScale(scela);
	return true;
}
void TrepotHole::Update()
{
	//���[�v��tere[0]
	for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
			CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - Game::GetInstance()->tere[0]->GetPosition();
		
			//�N�[���^�C��
			if (Game::GetInstance()->tere[0]->m_trepot_flag == false) {
				
				Game::GetInstance()->tere[0]->timer++;
				if (Game::GetInstance()->tere[0]->timer == 900) { //�^�C��
					TrepotHole2* tere2 = FindGO<TrepotHole2>("�e���|�[�g2");
					Game::GetInstance()->tere[0]->m_trepot_flag = true;
					Game::GetInstance()->tere[0]->timer = 0;

					if (Game::GetInstance()->tere[0]->m_trepot_flag == true) {
						 Game::GetInstance()->tere[0]->m_trepot->Init(L"modelData/terepot.cmo");
						 Game::GetInstance()->tere2[0]->m_trepot2->Init(L"modelData/terepot.cmo");
					}
				}
			}
			//true�œ��������烏�[�v����
			if (kyori.Length() < 2100 && m_trepot_flag == true && Game::GetInstance()->tere2[0]) {
				//�X�L�����f�������_���[���v���C�x�|�g����
			
				Game::GetInstance()->tere[0]->m_trepot->Init(L"modelData/terepot_false.cmo");
				
				QueryGOs<TrepotHole2>("�e���|�[�g2", [&](TrepotHole2* tere2)->bool {
					Game::GetInstance()->tere2[0]->m_trepot2->Init(L"modelData/terepot_false.cmo");
					//���[�v����
					/*Game::GetInstance()->m_player[j]->SetPosition(tere2->GetPosition2());
					Game::GetInstance()->m_player[j]->SetCharaCon(tere2->GetPosition2());

					m_trepot_flag = false;*/

					if (Game::GetInstance()->tere2[0]) {
						
						Game::GetInstance()->m_player[j]->SetPosition(Game::GetInstance()->tere2[0]->GetPosition2());
						Game::GetInstance()->m_player[j]->SetCharaCon(Game::GetInstance()->tere2[0]->GetPosition2());

					     m_trepot_flag = false;
					}

					
					return true;
				});
			}
	}

	//���[�v��tere[1]
	for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
		CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - Game::GetInstance()->tere[1]->GetPosition();
	
		//�N�[���^�C��
		if (Game::GetInstance()->tere[1]->m_trepot_flag == false) {

			Game::GetInstance()->tere[1]->timer++;
			if (Game::GetInstance()->tere[1]->timer == 900) {
				TrepotHole2* tere2 = FindGO<TrepotHole2>("�e���|�[�g2");
				Game::GetInstance()->tere[1]->m_trepot_flag = true;
				Game::GetInstance()->tere[1]->timer = 0;

				if (Game::GetInstance()->tere[1]->m_trepot_flag == true) {
					Game::GetInstance()->tere[1]->m_trepot->Init(L"modelData/terepot2.cmo");
					Game::GetInstance()->tere2[1]->m_trepot2->Init(L"modelData/terepot2.cmo");
				}
			}
		}
		//true�œ��������烏�[�v����
		if (kyori.Length() < 2100 && m_trepot_flag == true && Game::GetInstance()->tere2[1]) {
			//�X�L�����f�������_���[���v���C�x�|�g����

			Game::GetInstance()->tere[1]->m_trepot->Init(L"modelData/terepot_false.cmo");

			QueryGOs<TrepotHole2>("�e���|�[�g2", [&](TrepotHole2* tere2)->bool {
				Game::GetInstance()->tere2[1]->m_trepot2->Init(L"modelData/terepot_false.cmo");
				//���[�v����
				/*Game::GetInstance()->m_player[j]->SetPosition(tere2->GetPosition2());
				Game::GetInstance()->m_player[j]->SetCharaCon(tere2->GetPosition2());
				m_trepot_flag = false;*/

				if (Game::GetInstance()->tere2[1]) {

					Game::GetInstance()->m_player[j]->SetPosition(Game::GetInstance()->tere2[1]->GetPosition2());
					Game::GetInstance()->m_player[j]->SetCharaCon(Game::GetInstance()->tere2[1]->GetPosition2());

					m_trepot_flag = false;
				}
				return true;
			});
		}
	}

	//���[�v��tere[2]
	for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
		CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - Game::GetInstance()->tere[2]->GetPosition();

		//�N�[���^�C��
		if (Game::GetInstance()->tere[2]->m_trepot_flag == false) {

			Game::GetInstance()->tere[2]->timer++;
			if (Game::GetInstance()->tere[2]->timer == 900) {
				TrepotHole2* tere2 = FindGO<TrepotHole2>("�e���|�[�g2");
				Game::GetInstance()->tere[2]->m_trepot_flag = true;
				Game::GetInstance()->tere[2]->timer = 0;

				if (Game::GetInstance()->tere[2]->m_trepot_flag == true) {
					Game::GetInstance()->tere[2]->m_trepot->Init(L"modelData/terepot3.cmo");
					Game::GetInstance()->tere2[2]->m_trepot2->Init(L"modelData/terepot3.cmo");
				}
			}
		}
		//true�œ��������烏�[�v����
		if (kyori.Length() < 2100 && m_trepot_flag == true && Game::GetInstance()->tere2[2]) {
			//�X�L�����f�������_���[���v���C�x�|�g����

			Game::GetInstance()->tere[2]->m_trepot->Init(L"modelData/terepot_false.cmo");

			QueryGOs<TrepotHole2>("�e���|�[�g2", [&](TrepotHole2* tere2)->bool {
				Game::GetInstance()->tere2[2]->m_trepot2->Init(L"modelData/terepot_false.cmo");
				//���[�v����
				/*Game::GetInstance()->m_player[j]->SetPosition(tere2->GetPosition2());
				Game::GetInstance()->m_player[j]->SetCharaCon(tere2->GetPosition2());
				m_trepot_flag = false;*/

				if (Game::GetInstance()->tere2[2]) {

					Game::GetInstance()->m_player[j]->SetPosition(Game::GetInstance()->tere2[2]->GetPosition2());
					Game::GetInstance()->m_player[j]->SetCharaCon(Game::GetInstance()->tere2[2]->GetPosition2());

					m_trepot_flag = false;
				}


				return true;
			});
		}
	}
}