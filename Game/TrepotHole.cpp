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
	m_trepot = NewGO<prefab::CSkinModelRender>(0);
	m_trepot->Init(L"modelData/terepot.cmo"); //����(��蒼��)
	//m_position.x = -4000;

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
			if (m_trepot_flag == false) {
				
				timer++;
				if (timer == 400) {
					TrepotHole2* tere2 = FindGO<TrepotHole2>("�e���|�[�g2");
					m_trepot_flag = true;
					timer = 0;

					if (m_trepot_flag == true) {
						Game::GetInstance()->tere[0]->m_trepot->Init(L"modelData/terepot.cmo");
						Game::GetInstance()->tere2[0]->m_trepot2->Init(L"modelData/terepot.cmo");
					}
				}
			}
			//true�œ��������烏�[�v����
			if (kyori.Length() < 1200 && m_trepot_flag == true && Game::GetInstance()->tere2[0]) {
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
		if (m_trepot_flag == false) {

			timer++;
			if (timer == 400) {
				TrepotHole2* tere2 = FindGO<TrepotHole2>("�e���|�[�g2");
				m_trepot_flag = true;
				timer = 0;

				if (m_trepot_flag == true) {
					Game::GetInstance()->tere[1]->m_trepot->Init(L"modelData/terepot.cmo");
					Game::GetInstance()->tere2[1]->m_trepot2->Init(L"modelData/terepot.cmo");
				}
			}
		}
		//true�œ��������烏�[�v����
		if (kyori.Length() < 1200 && m_trepot_flag == true && Game::GetInstance()->tere2[1]) {
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
}