#pragma once
#include"Bullet.h"
#include"Camera.h"
#include"Game.h"
#include"Star.h"
#include"PlayerStar.h"
#include"Draw_Player.h"
#include"Draw_Skazu.h"
#include"RadarRing.h"
#include "tkEngine/character/tkCharacterController.h"

class Bullet;
class Camera;
class Game;
class Star;
class PlayerStar;
class Draw_Player;
class Draw_Skazu;
class RadarRing;
class Sinka_Bar;
class Crown;

class Player: public IGameObject
{
public:
	Player();
	void OnDestroy() override;

	bool Start();
	void Update();
	void Move();
	void PBullet();
	void PBullet2();
	void PBullet3();
	void Pevolution();
	void Rotation();
	void Death();
	void Respawn();
	void Houdai();
	void S_Hantei();
	void B_Hantei();
	void MutekiTimes();
	void HP();
	void StarPop();
	void SetPadNum(int num);
	void Sound(int SoundNum);
	void StarPos();
	void Playerwarp();
	void Upper();
	CVector3 GetPosition() const {
		return m_position;
	}
	void SetPosition(CVector3 plpos)
	{
		m_position = plpos;
	}
	void AddPosition(CVector3 plpos)
	{
		m_position += plpos;
	}
	void SetPositionX(float x)
	{
		m_position.x = x;
	}
	void SetPositionZ(float z)
	{
		m_position.z = z;
	}
	CVector3 GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	void SetCharaCon(CVector3 move)
	{
		m_CharaCon.SetPosition(move);
	}
	void SetMoveSpeed(CVector3 a) {
		m_moveSpeed += a;
		m_CharaCon.SetPosition(m_position += m_moveSpeed);
	}
	void SetVer(float a)
	{
		Ver = a;
	}
	int GetVer()
	{
		return Ver;
	}
	int GetMode()
	{
		return m_mode;
	}
	void SetStarCount(int a)
	{
		StarCount += a;
	}
	int GetStarCount()
	{
		return StarCount;
	}
	void SetShortCount(bool a)
	{
		ShortCount = a;
	}
	bool GetShortCount()
	{
		return ShortCount;
	}
	bool GetDeathCount()
	{
		return DeathCount;
	}
	CVector3 GetMemoryPosition()
	{
		return memory_position;
	}
	int GetPadNum()
	{
		return PadNum;
	}
	void AddHP(int Minasuhp)
	{
		PlHP += Minasuhp;
	}
	void SetPLST(PlayerStar* Plstar)
	{
		Plstar = Plstar;
	}
	bool GetMuteki() {
		return Muteki;
	}
	void SetRespown(float x, float y, float z)
	{
		Res.x = x;
		Res.y = y;
		Res.z = z;
	}
	CVector3 GetmoveSpeedFrame()
	{
		return moveSpeedFrame = m_moveSpeed * 8.0f;
	}
	void SetLABulletNum(int num)
	{
		LABulletNum = num;
	}
	int getBulletAmount() {
		return m_Short;
	}
	float Getradius() {//プレイヤーの半径を取得;
		return radius;
	}
	float getBulletPercentage();

	//勝利演出関連
	void setWinner();
	void doTiesMove(const CVector3& pos) {
		tiesMovePos = pos;
		tiesMove = c_tiseMove;
	}
	CVector4 getColor();

private:
	Player * m_player[4] = { nullptr };
	Draw_Player * draw_Pl = nullptr;
	Draw_Skazu * draw_S = nullptr;
	RadarRing* r_ring = nullptr;
	Bullet* m_bullet = nullptr;
	Game* m_game = nullptr;
	Star* m_star = nullptr;
	Camera* camera = nullptr;
	PlayerStar* Plstar = nullptr;
	Sinka_Bar* bar = nullptr;
	CCharacterController m_CharaCon;
	CVector3 m_position = CVector3::Zero;
	CVector3 memory_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 b_moveSpeed = CVector3::Zero;
	CVector3 m_scale = { 1.0f,1.0f,1.0f };
	CVector3 Tyuou = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
	//CVector3 b_position = CVector3::Zero;
	CVector3 moveSpeedFrame = m_moveSpeed * 12.0f;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSoundSource* SoundSource = nullptr;//BGM用のサウンドソース。
	
	float m_timer = 0.0f;
	float p_timer = 0.0f;
	float d_timer = 0.0f;
	float Timer0 = 0.0f;
	int m_Short = 0;
	int m_mode = 0;
	int MutekiTime = 0;
	int Ver = 0;		//デバックで強制進化させる。
	int StarCount = 0;
	int MaxStarCount = 99;
	int Star30 = 30;
	int Star50 = 50;
	int PopStar = 0;
	int PadNum = 0;
	int PadMaxKazu = 0;
	int PlHP = 100;
	int MaxHP = 100;
	int Damage = 20;
	float SeiseiVer_1 = 0.4f;
	float SeiseiVer_2 = 0.3f;
	float SeiseiVer_3 = 0.2f;
	int MaxSeiseiVer_1 = 99;
	int MaxSeiseiVer_2 = 70;
	int MaxSeiseiVer_3 = 30;
	int LABulletNum = 5;
	int syoki = 5;
	float SyokiSpped = 10.5f;
	float HoukouX = 0.0f;
	float HoukouZ = 0.0f;
	float memoryHX = 0.0f;
	float memoryHZ = 0.0f;
	float SpeedX = 0.0f;	
	float SpeedZ = 0.0f;
	float memorySX = 0.0f;
	float memorySZ = 0.0f;
	float BulletHantei = 1200.0f;
	float StarHantei = 1500.0f;
	float radius = { 800.0f };
	CVector3 Res = CVector3::Zero;

	bool DeathCount = false;
	bool ShortCount = false;
	bool MyBullet = true;
	bool Muteki = false;
	bool Alive = true;
	bool CountExplosion = false;
	
	//ゲーム終了後の勝利演出関連
	bool isWinner = false;       //勝者
	Crown* crown = nullptr;      //王冠
	float tiesMove = 0.0f;       //同点1位の場合、一人の元にワープする
	CVector3 tiesMovePos;        //同点1位ワープのポジション
public:
	static constexpr float c_tiseMove = 1.0f; //同点1位ワープにかける時間
};

