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
	m_trepot->Init(L"modelData/terepot.cmo"); //試作(作り直す)
	//m_position.x = -4000;

	scela = { 45.0, 45.0, 45.0 };  //大きさ　
	m_trepot->SetPosition(m_position);
	m_trepot->SetScale(scela);
	return true;
}
void TrepotHole::Update()
{
	for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
			CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - m_position;

			//クールタイム
			if (m_trepot_flag == false) {
				
				timer++;
				if (timer == 400) {
					TrepotHole2* tere2 = FindGO<TrepotHole2>("テレポート2");
					m_trepot_flag = true;
					timer = 0;

					if (m_trepot_flag == true) {
						m_trepot->Init(L"modelData/terepot.cmo");
						tere2->m_trepot2->Init(L"modelData/terepot.cmo");
					}
				}
			}
			//trueで当たったらワープする
			if (kyori.Length() < 1200 && m_trepot_flag == true) {
				//スキンモデルレンダラーをプライベ－トする

				m_trepot->Init(L"modelData/terepot_false.cmo");
				QueryGOs<TrepotHole2>("テレポート2", [&](TrepotHole2* tere2)->bool {
					tere2->m_trepot2->Init(L"modelData/terepot_false.cmo");
					//ワープする
					Game::GetInstance()->m_player[j]->SetPosition(tere2->GetPosition2());
					Game::GetInstance()->m_player[j]->SetCharaCon(tere2->GetPosition2());
					m_trepot_flag = false;
					return true;
				});
			}
	}
}