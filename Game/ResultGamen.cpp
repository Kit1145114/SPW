#include "stdafx.h"
#include "ResultGamen.h"
#include "Fade.h"

ResultGamen::ResultGamen()
{
	//Gameクラスが消えてしまう前にコンストラクタで星の数を読み込んでおく
	Player** playerArray = Game::GetInstance()->m_player;
	int padKazu_ = Game::GetInstance()->GetSansenKazu();
	for (int i = 0; i < padKazu_; i++) {
		PS[i] = playerArray[i]->GetStarCount();
	}
}


ResultGamen::~ResultGamen()
{
	DeleteGO(r_spriteRender);
	for (int i = 0; i < 4; i++) {
		if (P_spriteRender[i] != nullptr)
		{
			DeleteGO(P_spriteRender[i]);
		}
	}
	for (int i = 0; i < 4; i++) {
		if (G_spriteRender[i] != nullptr)
		{
			DeleteGO(G_spriteRender[i]);
		}
	}
	if (r_Draw[0] != nullptr)
	{
		DeleteGO(r_Draw[0]);
	}
	if (r_Draw[1] != nullptr)
	{
		DeleteGO(r_Draw[1]);
	}
	if (r_Draw[2] != nullptr)
	{
		DeleteGO(r_Draw[2]);
	}
	if (r_Draw[3] != nullptr)
	{
		DeleteGO(r_Draw[3]);
	}
	DeleteGO(resultSound);
}

bool ResultGamen::Start()
{
	resultSound = NewGO<prefab::CSoundSource>(0);
	resultSound->Init(L"sound/Result.wav");
	resultSound->Play(true);
	resultSound->SetVolume(0.5f);

	//バックの画像
	r_spriteRender = NewGO<prefab::CSpriteRender>(0);
	r_spriteRender->Init(L"sprite/Reslut1.dds", 1280.0f, 720.0f);

	//ゲート
	junban = PadKazu-1;
	for (int i = 0; i < PadKazu; i++) {
		//ここもゲート
		G_spriteRender[i] = NewGO<prefab::CSpriteRender>(2);
		G_spriteRender[i]->Init(L"sprite/Gate.dds", GateSizeX, GateSizeY);
		G_spriteRender[i]->SetPosition(G_pos_array[i]);

		//順位表示に使うResultDrawの初期化
		r_Draw[i] = NewGO<ResultDraw>(0);
		r_Draw[i]->SetJuni(i + 1);

		//プレイヤーの名前を表示するCSpriteRenderにポジションをセット
		//順位によって入れ替えるので名前が描かれた画像はまだ読まない
		P_spriteRender[i] = NewGO<prefab::CSpriteRender>(0);
		P_spriteRender[i]->SetPosition(N_pos_array[i]);
	}
	Result();
	Fade::fadeOut();
	return true;
}

void ResultGamen::Update()
{
	if (Pad(0).IsTrigger(enButtonA) == true)
	{
		if (gate_skip) {

			Fade::fadeIn([&]() {
				NewGO<Title_2>(0, "Title_2");
				DeleteGO(this);
			}, resultSound);

		} else {
			gate_skip = true;
		}
	}
	GateDraw();
}

void ResultGamen::Result()
{
	int PNums[4];
	for (int i = 0; i < 4; i++) {
		PNums[i] = i;
	}

	for (int i = 0; i < PadKazu; i++) {
		for (int j = (PadKazu-1); j > i; j--) {
			 if (PS[PNums[j-1]] < PS[PNums[j]]) {
				 //プレイヤーナンバーを入れ替える
				int n = PNums[j];
				PNums[j]= PNums[j - 1];
				PNums[j - 1] = n;

				//プレイヤーの名前画像パスも入れ替える
				const wchar_t* p = draw_P[j];
				draw_P[j] = draw_P[j - 1];
				draw_P[j - 1] = p;
			}
		}
	}

	//同一順位がいたときはその順位のひとつ下を非表示にする。
	for (int i = 0; i < PadKazu-1; i++) {
		if (PS[PNums[i]] == PS[PNums[i+1]]){
			r_Draw[i+1]->Inactivate();
		}
	}

	//スターカウントに入れるのと、名前画像の初期化
	for (int i = 0; i < PadKazu; i++) {
		StarCount[i] = PS[PNums[i]];
		P_spriteRender[i]->Init(draw_P[i], 500.0f, 135.0f);
	}
	int i = 0;
}

void ResultGamen::PostRender(CRenderContext& rc)
{
	wchar_t text[4];//星を1000個以上取るようならここの要素数を増やしてください

	m_font.Begin(rc);

	for (int i = 0; i < PadKazu; i++) {
		swprintf_s(text, L"%d", StarCount[i]);
		m_font.Draw(
			text,
			star_pos_array[i],
			{ 1.0f, 0.95f, 0.0f, 1.0f },
			0.0f,
			1.675f
		);
	}

	m_font.End(rc);
}

void ResultGamen::GateDraw()
{
	//ゲートの速さを上げる。
	if (gate_skip) {
		for (int i = 0; i < PadKazu; i++) {
			if (G_pos_array[i].x < change) {
				G_pos_array[i].x += 250.0f;
				G_spriteRender[i]->SetPosition(G_pos_array[i]);
			}
		}

		return;
	}

	//skipでない、ゆっくり動く場合

	if (junban >= 0) {//junbanが0より小さくなったら開扉終了

		if (timer > Limit) {//ゲート開扉前の待機時間

			//今のjunbanのゲートポジションを動かす
			G_pos_array[junban].x += 10.0f;

			if (G_pos_array[junban].x > change) {
				//changeまで扉が動いたらjunbanをデクリメントして次へ移る
				G_pos_array[junban].x = change;
				junban--;

			} else {
				//ゲートの画像を動かす
				G_spriteRender[junban]->SetPosition(G_pos_array[junban]);
			}

		} else {
			timer++;//ゲート開扉前の待機時間(待機終了前だけtimerを増やしていく)
		}

	} else {
		gate_skip = true;//動き終わった場合
	}
}
