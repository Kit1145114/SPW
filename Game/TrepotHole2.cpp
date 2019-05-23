#include "stdafx.h"
#include "TrepotHole2.h"
#include "TrepotHole.h"
#include "Game.h"


TrepotHole2::TrepotHole2()
{
}


TrepotHole2::~TrepotHole2()
{
	DeleteGO(m_trepot2);
}
bool TrepotHole2::Start()
{
	m_trepot2 = NewGO<prefab::CSkinModelRender>(0);
	m_trepot2->Init(L"modelData/terepot.cmo");

	m_position2.x = 4000;

	scela = { 45.0, 45.0, 45.0 };
	m_trepot2->SetPosition(m_position2);
	m_trepot2->SetScale(scela);
	return true;
}
void TrepotHole2::Update()
{
	for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
		 
			CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - m_position2;

			TrepotHole* tere = FindGO<TrepotHole>("テレポート");
				//クールタイム
				if (tere->GetTrepotFlag() == false) {
				
					tere->TasuTime(1);
					if (tere->GetTime() == 400) {
						tere->SetTrepotFlag(true);
						tere->SetTime(0);
						if (tere->GetTrepotFlag() == true) {
							m_trepot2->Init(L"modelData/terepot.cmo");
							tere->m_trepot->Init(L"modelData/terepot.cmo");
						}
					}
				}
				//trueで当たったらワープする
				if (kyori.Length() < 1200 && tere->GetTrepotFlag() == true) {


					m_trepot2->Init(L"modelData/terepot_false.cmo");
					QueryGOs<TrepotHole>("テレポート", [&](TrepotHole* tere)->bool {
						tere->m_trepot->Init(L"modelData/terepot_false.cmo");
						Game::GetInstance()->m_player[j]->SetPosition(tere->GetPosition());
						Game::GetInstance()->m_player[j]->SetMoveSpeed(tere->GetPosition()); //キャラコンにも教える
						tere->SetTrepotFlag(false);
						return true;
					});
				}
				//return true;
			//});
		
	}

}
