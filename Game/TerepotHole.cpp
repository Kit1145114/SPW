#include "stdafx.h"
#include "TerepotHole.h"
#include "Game.h"

TerepotHole::TerepotHole()
{
}


TerepotHole::~TerepotHole()
{
	DeleteGO(m_terepot);
}
bool TerepotHole::Start()
{
	m_terepot = NewGO<prefab::CSkinModelRender>(0);
	m_terepot->Init(modelFilePath.c_str());
	scale = { 45, 45, 45 };

	m_terepot->SetPosition(m_position);
	m_terepot->SetScale(scale);
	return true;
}
void TerepotHole::Update()
{

	for (int playerNo = 0; playerNo < Game::GetInstance()->GetSansenKazu(); playerNo++) {
		CVector3 kyori = Game::GetInstance()->m_player[playerNo]->GetPosition() -
			m_position;
		//ワープ
		if (terepot_flag == false) {
			timer++;
			if (timer == 200) {  //タイム200　大体3秒
				timer = 0;
				terepot_flag = true;
					//Gameクラスで教えたワープオブジェクトファイルパス(trueの時)
					m_terepot->Init(modelFilePath.c_str());
			}
		}
		if (kyori.Length() < 1000  && linkTerepotHole->terepot_flag  == true) {
			//ワープ先のflag
			linkTerepotHole->terepot_flag = false;
			CVector3 pos = linkTerepotHole->GetPosi();
			Game::GetInstance()->m_player[playerNo]->SetPosition(pos);
			//Game::GetInstance()->m_player[playerNo]->SetCharaCon(linkTerepotHole->GetPosi());
			
			linkTerepotHole->m_terepot->Init(L"modelData/terepot_false.cmo");
		}
		
		//ワープ先
		if (linkTerepotHole->terepot_flag == false) {
			timer++;
			if (timer == 200) {  //タイム200　大体3秒
				timer = 0;
				linkTerepotHole->terepot_flag = true;
				//Gameクラスで教えたワープオブジェクトファイルパス(trueの時)
				m_terepot->Init(modelFilePath.c_str());
			}
		}
		if (kyori.Length() < 1000 && terepot_flag == true) {
			//ワープのフラグ
			terepot_flag = false;
			CVector3 pos = linkTerepotHole->GetPosi();
			Game::GetInstance()->m_player[playerNo]->SetPosition(pos);
			//Game::GetInstance()->m_player[playerNo]->SetCharaCon(linkTerepotHole->GetPosi());

			m_terepot->Init(L"modelData/terepot_false.cmo");
		}
	}
}	
	  
