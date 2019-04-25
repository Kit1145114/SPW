#include "stdafx.h"
#include "ResultGamen.h"


ResultGamen::ResultGamen()
{
}


ResultGamen::~ResultGamen()
{
	DeleteGO(r_spriteRender);
	if (P1_spriteRender != nullptr)
	{
		DeleteGO(P1_spriteRender);
	}
	if (P2_spriteRender != nullptr)
	{
		DeleteGO(P2_spriteRender);
	}
	if (P3_spriteRender != nullptr)
	{
		DeleteGO(P3_spriteRender);
	}
	if (P4_spriteRender != nullptr)
	{
		DeleteGO(P4_spriteRender);
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
}

bool ResultGamen::Start()
{
	r_spriteRender = NewGO<prefab::CSpriteRender>(0);
	r_spriteRender->Init(L"sprite/Reslut.dds", 1280.0f, 720.0f);
	switch (PadKazu)
	{
	case 1:
		m_player[0] = FindGO<Player>("Player");
		r_Draw[0] = NewGO<ResultDraw>(0);
		r_Draw[0]->SetPlayer(1);
		PS[0] = m_player[0]->GetStarCount();
		P1_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P1_spriteRender->Init(L"sprite/1Player.dds", 300.0f, 125.0f);
		P1_spriteRender->SetPosition(N1position);
		break;
	case 2:
		m_player[0] = FindGO<Player>("Player");
		PS[0] = m_player[0]->GetStarCount();
		r_Draw[0] = NewGO<ResultDraw>(0);
		r_Draw[0]->SetPlayer(1);
		m_player[1] = FindGO<Player>("Player1");
		r_Draw[1] = NewGO<ResultDraw>(0);
		PS[1] = m_player[1]->GetStarCount();
		r_Draw[1]->SetPlayer(2);
		P1_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P1_spriteRender->Init(L"sprite/1Player.dds", 300.0f, 125.0f);
		P1_spriteRender->SetPosition(N1position);
		P2_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P2_spriteRender->Init(L"sprite/2Player.dds", 300.0f, 125.0f);
		P2_spriteRender->SetPosition(N2position);
break;
	case 3:
		m_player[0] = FindGO<Player>("Player");
		PS[0] = m_player[0]->GetStarCount();
		r_Draw[0] = NewGO<ResultDraw>(0);
		r_Draw[0]->SetPlayer(1);
		m_player[1] = FindGO<Player>("Player1");
		PS[1] = m_player[1]->GetStarCount();
		r_Draw[1] = NewGO<ResultDraw>(0);
		r_Draw[1]->SetPlayer(2);
		m_player[2] = FindGO<Player>("Player2");
		PS[2] = m_player[2]->GetStarCount();
		r_Draw[2] = NewGO<ResultDraw>(0);
		r_Draw[2]->SetPlayer(3);
		P1_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P1_spriteRender->Init(L"sprite/1Player.dds", 300.0f, 125.0f);
		P1_spriteRender->SetPosition(N1position);
		P2_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P2_spriteRender->Init(L"sprite/2Player.dds", 300.0f, 125.0f);
		P2_spriteRender->SetPosition(N2position);
		P3_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P3_spriteRender->Init(L"sprite/3Player.dds", 300.0f, 125.0f);
		P3_spriteRender->SetPosition(N3position);
		break;
	case 4:
		m_player[0] = FindGO<Player>("Player");
		PS[0] = m_player[0]->GetStarCount();
		r_Draw[0] = NewGO<ResultDraw>(0);
		r_Draw[0]->SetPlayer(1);
		m_player[1] = FindGO<Player>("Player1");
		PS[1] = m_player[1]->GetStarCount();
		r_Draw[1] = NewGO<ResultDraw>(0);
		r_Draw[1]->SetPlayer(2);
		m_player[2] = FindGO<Player>("Player2");
		PS[2] = m_player[2]->GetStarCount();
		r_Draw[2] = NewGO<ResultDraw>(0);
		r_Draw[2]->SetPlayer(3);
		m_player[3] = FindGO<Player>("Player3");
		r_Draw[3] = NewGO<ResultDraw>(0);
		r_Draw[3]->SetPlayer(4);
		PS[3] = m_player[3]->GetStarCount();
		P1_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P1_spriteRender->Init(L"sprite/1Player.dds", 300.0f, 125.0f);
		P1_spriteRender->SetPosition(N1position);
		P2_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P2_spriteRender->Init(L"sprite/2Player.dds", 300.0f, 125.0f);
		P2_spriteRender->SetPosition(N2position);
		P3_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P3_spriteRender->Init(L"sprite/3Player.dds", 300.0f, 125.0f);
		P3_spriteRender->SetPosition(N3position);
		P4_spriteRender = NewGO<prefab::CSpriteRender>(0);
		P4_spriteRender->Init(L"sprite/4Player.dds", 300.0f, 125.0f);
		P4_spriteRender->SetPosition(N4position);
		break;
	}
	return true;
}

void ResultGamen::Update()
{
	Result();
	if (Pad(0).IsPress(enButtonSelect) == true)
	{
		NewGO<Title_2>(0, "Title_2");
		DeleteGO(this);
	}
}

void ResultGamen::Result()
{
	switch (PadKazu)
	{
	case 1:
		r_Draw[0]->SetJuni(1);
		break;
	case 2:
		if (PS[0] < PS[1])
		{
			r_Draw[0]->SetJuni(2);
			r_Draw[1]->SetJuni(1);
		}
		else if (PS[0] > PS[1])
		{
			r_Draw[0]->SetJuni(1);
			r_Draw[1]->SetJuni(2);
		}
		else if (PS[0] == PS[1])
		{
			r_Draw[0]->SetJuni(1);
			r_Draw[1]->SetJuni(1);
		}
		break;
	case 3:
		if (PS[0] < PS[1]) // 1P< 2P
		{
			if(PS[0] < PS[2]) //1P < 3P
			{
				r_Draw[0]->SetJuni(3);
				if (PS[1] > PS[2]) //2P < 3P
				{
					r_Draw[1]->SetJuni(2);
					r_Draw[2]->SetJuni(1);
				}
			}
			else if (PS[0] > PS[2]) //1P > 3P
			{
				r_Draw[0]->SetJuni(2);
				r_Draw[1]->SetJuni(1);
				r_Draw[2]->SetJuni(3);
			}
		}

		if (PS[1] < PS[2]) // 2P < 3P
		{
			if (PS[1] < PS[0]) //2P < 1P
			{
				r_Draw[1]->SetJuni(3);
				if (PS[0] > PS[2]) //3P < 1P
				{
					r_Draw[0]->SetJuni(1);
					r_Draw[2]->SetJuni(2);
				}
			}
			else if (PS[0] < PS[1]) //1P < 2P
			{
				r_Draw[0]->SetJuni(1);
				r_Draw[1]->SetJuni(2);
				r_Draw[2]->SetJuni(3);
			}
		}

		if (PS[2] < PS[0]) // 3P < 1P
		{
			if (PS[2] < PS[1]) //3P < 2P
			{
				r_Draw[2]->SetJuni(3);
				if (PS[0] > PS[1]) //3P < 2P
				{
					r_Draw[0]->SetJuni(2);
					r_Draw[1]->SetJuni(1);
				}
			}
			else if (PS[2] > PS[1]) //3P > 2P
			{
				r_Draw[0]->SetJuni(1);
				r_Draw[1]->SetJuni(3);
				r_Draw[2]->SetJuni(2);
			}
		}

		else if (PS[0] == PS[1] && PS[1] == PS[2])
		{
			r_Draw[0]->SetJuni(1);
			r_Draw[1]->SetJuni(1);
			r_Draw[2]->SetJuni(1);
		}
		/*for (int i = 2; i < PadMaxKazu; i++) {
			for (int j = 1; j < i - 1; j++) {

				if (PS[i] > PS[j])
					PS[j]->rank++;
				if (PS[i] < PS[j])
					ps[i]->rank++;
			}
		}*/
		break;
	case 4:
		if (PS[0] < PS[1]) // 1P< 2P
		{
			if (PS[0] < PS[2]) //1P < 3P
			{
				if (PS[0] < PS[3]) //1P < 4P
				{
					r_Draw[0]->SetJuni(4); //1P = 4
					if (PS[2] < PS[3]) //3P < 4P
					{
						if (PS[1] < PS[3])//2P < 4P
						{
							r_Draw[3]->SetJuni(1); //4P = 1
							if (PS[1] < PS[2])	//2P < 3P
							{
								r_Draw[2]->SetJuni(3); //2P =3
								r_Draw[3]->SetJuni(2); //3P =2		  
							}
							else if (PS[2] < PS[1])//3P < 2P
							{
								r_Draw[2]->SetJuni(2); //2P =2
								r_Draw[3]->SetJuni(3); //3P =3	
							}
						}
						else if (PS[3] < PS[1])//2P > 4P
						{
							r_Draw[1]->SetJuni(1);	//2P = 1
							r_Draw[2]->SetJuni(3);	//3P = 3
							r_Draw[3]->SetJuni(2);	//4P = 2
						}
					}
				}
			}
		}

		if (PS[1] < PS[0]) // 2P< 1P
		{
			if (PS[1] < PS[2]) //2P < 3P
			{
				if (PS[1] < PS[3]) //2P < 4P
				{
					r_Draw[1]->SetJuni(4); //2P = 4
					if (PS[2] < PS[3]) //3P < 4P
					{
						if (PS[0] < PS[3])//1P < 4P
						{
							r_Draw[3]->SetJuni(1); //4P = 1
							if (PS[0] < PS[2])	//1P < 3P
							{
								r_Draw[0]->SetJuni(3); //1P =3
								r_Draw[3]->SetJuni(2); //3P =2		  
							}
							else if (PS[2] < PS[0])//3P < 1P
							{
								r_Draw[0]->SetJuni(2); //1P =2
								r_Draw[3]->SetJuni(3); //3P =3	
							}
						}
						else if (PS[0] > PS[3])//1P > 4P
						{
							r_Draw[0]->SetJuni(1);	//1P = 1
							r_Draw[2]->SetJuni(3);	//3P = 3
							r_Draw[3]->SetJuni(2);	//4P = 2
						}
					}
				}
			}
		}

		if (PS[2] < PS[0]) // 3P< 1P
		{
			if (PS[2] < PS[1]) //3P < 2P
			{
				if (PS[2] < PS[3]) //3P < 4P
				{
					r_Draw[2]->SetJuni(4); //3P = 4
					if (PS[0] < PS[3]) //1P < 4P
					{
						if (PS[1] < PS[3])//2P < 4P
						{
							r_Draw[3]->SetJuni(1); //4P = 1
							if (PS[0] < PS[1])	//1P < 2P
							{
								r_Draw[0]->SetJuni(3); //1P =3
								r_Draw[1]->SetJuni(2); //2P =2		  
							}
							else if (PS[1] < PS[0])//2P < 1P
							{
								r_Draw[0]->SetJuni(2); //1P =2
								r_Draw[1]->SetJuni(3); //2P =3	
							}
						}
						else if (PS[1] > PS[3])//2P > 4P
						{
							r_Draw[0]->SetJuni(3);	//1P = 3
							r_Draw[1]->SetJuni(1);	//2P = 1
							r_Draw[3]->SetJuni(2);	//4P = 2
						}
					}
				}
			}
		}

		if (PS[3] < PS[0]) // 4P< 1P
		{
			if (PS[3] < PS[1]) //4P < 2P
			{
				if (PS[3] < PS[2]) //4P < 3P
				{
					r_Draw[3]->SetJuni(4); //4P = 4
					if (PS[1] < PS[2]) //2P < 3P
					{
						if (PS[0] < PS[2])//1P < 3P
						{
							r_Draw[1]->SetJuni(1); //3P = 1
							if (PS[0] < PS[1])	//1P < 2P
							{
								r_Draw[0]->SetJuni(3); //1P =3
								r_Draw[1]->SetJuni(2); //2P =2		  
							}
							else if (PS[1] < PS[0])//2P < 1P
							{
								r_Draw[0]->SetJuni(2); //1P =2
								r_Draw[1]->SetJuni(3); //2P =3	
							}
						}
						else if (PS[0] > PS[2])//1P > 3P
						{
							r_Draw[0]->SetJuni(3);	//1P = 3
							r_Draw[1]->SetJuni(1);	//2P = 1
							r_Draw[3]->SetJuni(2);	//4P = 2
						}
					}
				}
			}
		}
		else if (PS[0] == PS[1] && PS[1] == PS[2] && PS[2] == PS[3])
		{
			r_Draw[0]->SetJuni(1);
			r_Draw[1]->SetJuni(1);
			r_Draw[2]->SetJuni(1);
			r_Draw[3]->SetJuni(1);
		}
		break;
	}
}