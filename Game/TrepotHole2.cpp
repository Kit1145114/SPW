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
	Game::GetInstance()->tere2[0]->m_trepot2 = NewGO<prefab::CSkinModelRender>(0);
	Game::GetInstance()->tere2[0]->m_trepot2->Init(L"modelData/terepot.cmo"); //緑
	Game::GetInstance()->tere2[1]->m_trepot2 = NewGO<prefab::CSkinModelRender>(0);
	Game::GetInstance()->tere2[1]->m_trepot2->Init(L"modelData/terepot2.cmo"); //青
	Game::GetInstance()->tere2[2]->m_trepot2 = NewGO<prefab::CSkinModelRender>(0);
	Game::GetInstance()->tere2[2]->m_trepot2->Init(L"modelData/terepot3.cmo"); //黄

	scela = { 45.0, 45.0, 45.0 };  //大きさ　
	m_trepot2->SetPosition(m_position2);
    m_trepot2->SetScale(scela);
	return true;
}
void TrepotHole2::Update()
{
	//ワープのtere2[0]
	for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {
		 
			CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - Game::GetInstance()->tere2[0]->GetPosition2();
			                                                                   //m_position
			TrepotHole* tere = FindGO<TrepotHole>("テレポート");
				//クールタイム
				if (Game::GetInstance()->tere[0]->GetTrepotFlag() == false) {
				
					Game::GetInstance()->tere[0]->TasuTime(1);
					if (Game::GetInstance()->tere[0]->GetTime() == 900) { //タイム
						Game::GetInstance()->tere[0]->SetTrepotFlag(true);
						Game::GetInstance()->tere[0]->SetTime(0);
						if (Game::GetInstance()->tere[0]->GetTrepotFlag() == true) {
							Game::GetInstance()->tere2[0]->m_trepot2->Init(L"modelData/terepot.cmo");
							Game::GetInstance()->tere[0]->m_trepot->Init(L"modelData/terepot.cmo");
						}
					}
				}
				//trueで当たったらワープする
				if (kyori.Length() < 2100 && Game::GetInstance()->tere[0]->GetTrepotFlag() == true && Game::GetInstance()->tere2[0]) {

					Game::GetInstance()->tere2[0]->m_trepot2->Init(L"modelData/terepot_false.cmo");
					QueryGOs<TrepotHole>("テレポート", [&](TrepotHole* tere)->bool {
						Game::GetInstance()->tere[0]->m_trepot->Init(L"modelData/terepot_false.cmo");

						//Game::GetInstance()->m_player[j]->SetPosition(tere->GetPosition());
						//Game::GetInstance()->m_player[j]->SetCharaCon(tere->GetPosition()); //キャラコンにも教える
						//tere->SetTrepotFlag(false);

						if (Game::GetInstance()->tere[0]) {
							Game::GetInstance()->m_player[j]->SetPosition(Game::GetInstance()->tere[0]->GetPosition());
							Game::GetInstance()->m_player[j]->SetCharaCon(Game::GetInstance()->tere[0]->GetPosition());

						    tere->SetTrepotFlag(false);
						}
						
						return true;
					});
				}
	}

	//ワープのtere2[1]
	for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {

		CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - Game::GetInstance()->tere2[1]->GetPosition2();

		TrepotHole* tere = FindGO<TrepotHole>("テレポート");
		//クールタイム
		if (Game::GetInstance()->tere[1]->GetTrepotFlag() == false) {

			Game::GetInstance()->tere[1]->TasuTime(1);
			if (Game::GetInstance()->tere[1]->GetTime() == 900) {
				Game::GetInstance()->tere[1]->SetTrepotFlag(true);
				Game::GetInstance()->tere[1]->SetTime(0);
				if (Game::GetInstance()->tere[1]->GetTrepotFlag() == true) {
					Game::GetInstance()->tere2[1]->m_trepot2->Init(L"modelData/terepot2.cmo");
					Game::GetInstance()->tere[1]->m_trepot->Init(L"modelData/terepot2.cmo");
				}
			}
		}
		//trueで当たったらワープする
		if (kyori.Length() < 2100 && tere->GetTrepotFlag() == true && Game::GetInstance()->tere2[1]) {

			Game::GetInstance()->tere2[1]->m_trepot2->Init(L"modelData/terepot_false.cmo");
			QueryGOs<TrepotHole>("テレポート", [&](TrepotHole* tere)->bool {
				Game::GetInstance()->tere[1]->m_trepot->Init(L"modelData/terepot_false.cmo");

				//Game::GetInstance()->m_player[j]->SetPosition(tere->GetPosition());
				//Game::GetInstance()->m_player[j]->SetCharaCon(tere->GetPosition()); //キャラコンにも教える
				//tere->SetTrepotFlag(false);

				if (Game::GetInstance()->tere[1]) {
					Game::GetInstance()->m_player[j]->SetPosition(Game::GetInstance()->tere[1]->GetPosition());
					Game::GetInstance()->m_player[j]->SetCharaCon(Game::GetInstance()->tere[1]->GetPosition());

					tere->SetTrepotFlag(false);
				}

				return true;
			});
		}
	}

	//ワープのtere2[2]
	for (int j = 0; j < Game::GetInstance()->GetSansenKazu(); j++) {

		CVector3 kyori = Game::GetInstance()->m_player[j]->GetPosition() - Game::GetInstance()->tere2[2]->GetPosition2();

		TrepotHole* tere = FindGO<TrepotHole>("テレポート");
		//クールタイム
		if (Game::GetInstance()->tere[2]->GetTrepotFlag() == false) {

			Game::GetInstance()->tere[2]->TasuTime(1);
			if (Game::GetInstance()->tere[2]->GetTime() == 900) {
				Game::GetInstance()->tere[2]->SetTrepotFlag(true);
				Game::GetInstance()->tere[2]->SetTime(0);

				if (Game::GetInstance()->tere[2]->GetTrepotFlag() == true) {
					Game::GetInstance()->tere2[2]->m_trepot2->Init(L"modelData/terepot3.cmo");
					Game::GetInstance()->tere[2]->m_trepot->Init(L"modelData/terepot3.cmo");
				}
			}
		}
		//trueで当たったらワープする
		if (kyori.Length() < 2100 && tere->GetTrepotFlag() == true && Game::GetInstance()->tere2[2]) {

			Game::GetInstance()->tere2[2]->m_trepot2->Init(L"modelData/terepot_false.cmo");
			QueryGOs<TrepotHole>("テレポート", [&](TrepotHole* tere)->bool {
				Game::GetInstance()->tere[2]->m_trepot->Init(L"modelData/terepot_false.cmo");

				//Game::GetInstance()->m_player[j]->SetPosition(tere->GetPosition());
				//Game::GetInstance()->m_player[j]->SetCharaCon(tere->GetPosition()); //キャラコンにも教える
				//tere->SetTrepotFlag(false);

				if (Game::GetInstance()->tere[2]) {
					Game::GetInstance()->m_player[j]->SetPosition(Game::GetInstance()->tere[2]->GetPosition());
					Game::GetInstance()->m_player[j]->SetCharaCon(Game::GetInstance()->tere[2]->GetPosition());

					tere->SetTrepotFlag(false);
				}

				return true;
			});
		}
	}

	
}
