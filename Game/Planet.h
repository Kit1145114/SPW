#pragma once
#include"Game.h"
#include"Draw_Player.h"
#include"BlackHole.h"
#include "tkEngine/light/tkPointLight.h"
class Game;
class Bullet;
class Star;
class BlackHole;

class Planet : public IGameObject
{
public:
	Planet();
	~Planet();
	bool Start();
	void Update();
	void Move();
	void Size();
	void Death();
	void explosion();
	/// <summary>
	/// 惑星を一斉に生成する、↓を惑星分ここでランダム指定呼びだしている。
	/// </summary>
	/// <param name="Reload">生成させる惑星数</param>
	/// <param name="Planetnum">リスポーンの場合ここで渡したナンバーの惑星を作る</param>
	/// <returns></returns>
	static bool Generate(int Reload,int Planetnum);
	/// <summary>
	/// 惑星の生成させる。
	/// </summary>
	/// <param name="position">場所</param>
	/// <param name="skinModelRender">スキンモデル指定</param>
	/// <param name="scale">大きさ</param>
	/// <param name="cpointlight">ライト</param>
	void init(CVector3 position, prefab::CSkinModelRender* skinModelRender, float scale, prefab::CPointLight* cpointlight);
	void Light();
	CVector3 GetPosition() {
		return p_position;
	} 
	void SetPosition(CVector3 plpos)
	{
		p_position = plpos;
	}
	void SetMoveSpeed(CVector3 Speed) {
		p_position+= Speed;
	}
	float GetRadius() {
		return radius;
	}
protected:
	CVector3 p_position = CVector3::Zero;//ポジション。
	CVector3 scale = { 1.0f,1.0f,1.0f };//サイズ。
	CVector3 p_Size = { 1.0f,1.0f,1.0f };           //pop時の少しづつ大きくなるSizeで使う。
	CQuaternion p_rotation = CQuaternion::Identity;
	CVector3 randomspeed = CVector3::Zero;//ランダムスピード。
	prefab::CSkinModelRender* p_skinModelRender = nullptr;
	prefab::CSoundSource* SoundSource = nullptr;//BGM用のサウンドソース。
	prefab::CPointLight* p_Cpointlit = nullptr;//他を照らすライト。
	Bullet* m_bullet = nullptr;
	Planet* hoge = nullptr;
	float radius = { 30.0f };  //基本惑星の半径。
	float PosMaxLimitx = 37000.0f;//惑星が生存できるx範囲、フィールドに合わせて調節した。
	float PosMaxLimitz = 20000.0f;//惑星が生存できるy範囲、フィールドに合わせて調節した。
	float angle = 0;           //回転。
	float sizecount = 0.01f;    //pop時の少しづつ大きくなるSizeで使う。
	bool movecount = false;//ランダムに移動するフラグ、trueにすると一回またランダムに向きを変える。
	bool CountExplosion = false;//爆発フラグ、trueで爆発エフェクトと効果音を出してDeleteする。
	bool repopflag = false;    //ポップ時いきなり他と被るのを防ぐのに使うフラグ。
	int myPlanetnumber =0;     //自分のPlametナンバー保存用。
	int time = 0;              //plametが誕生してからの時間。
};

