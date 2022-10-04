#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/CameraComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Component/Arm.h"
#include "FSM.h"
#include "Component/NavAgent.h"

enum class Player_Joom_State
{
	None,
	JoomIn,
	JoomOut,
	End
};

struct PlayerInfo
{
	std::string	CharacterName;
	float	AttackMin;
	float	AttackMax;
	float	MaxHP;
	float	HP;
	float	MaxStamina;
	float	Stamina;
	float	Speed;

	PlayerInfo() :
		AttackMin(10.f),
		AttackMax(20.f),
		MaxHP(100.f),
		HP(100.f),
		MaxStamina(100.f),
		Stamina(100.f),
		Speed(-25.f)
	{
	}
};



class CPlayer :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer();
	CPlayer(const CPlayer& obj);
	virtual ~CPlayer();

private:
	CSharedPtr<CAnimationMeshComponent>    m_Mesh;
	CSharedPtr<CStaticMeshComponent>	m_Face;
	CSharedPtr<CCameraComponent>        m_Camera;
	CSharedPtr<CArm>                    m_Arm;
	CSharedPtr<CColliderBox3D>		m_ColliderBox;
	CSharedPtr<CColliderBox3D>		m_SlidingBox;
	CSharedPtr<CColliderBox3D>		m_CamPosBox;
	CSharedPtr<CNavAgent>     m_NavAgent;
	// 화면 중앙 위치
	POINT     m_CenterPoint;
	HWND        m_hWnd;
	CSharedPtr<class CBow>   m_Bow;
	CSharedPtr<class CBowBox>   m_BowBox;
	CSharedPtr<class CArrow>	m_Arrow;
	CSharedPtr<class CBowVfx>	m_BowVfx;
	CSharedPtr<class CChargingParticle>		m_ChargingParticle;
	Player_Joom_State			m_JoomState;
	PlayerInfo* m_PlayerInfo;
	Coating_State m_CoatingState;
	CGameObject* m_ColliderObj;

	// 해당 DPI를 올리면 회전이 느려지고 값을 내리면 회전속도가 빨라짐
	float       m_MouseDPI;
	float       m_RotationSpeed;        // 플레이어 회전 속도
	float       m_MoveSpeed;            // 플레이어 이동 속도
	float       m_QuickMoveSpeed;       // 플레이어 빠른 달리기 이동 속도
	float       m_MouseRotAccY;         // 플레이어 마우스 회전에 따른 회전값Y
	float       m_MouseRotAccX;         // 플레이어 마우스 회전에 따른 회전값X
	float		m_ArmRotAccY;		// 회전값 + 180도를 더한 변수
	float		m_EvadeShotSpeed;
	float		m_CorrectionAngle;

	bool    m_FrontDown;            // W키 Down
	bool    m_BackDown;             // S키 Down
	bool    m_LeftDown;             // A키 Down
	bool    m_RightDown;            // D키 Down

	// 빠르게 달리기 키 클릭 여부
	bool    m_RunQuickFrontDown;
	bool    m_RunQuickBackDown;
	bool    m_RunQuickLeftDown;
	bool    m_RunQuickRightDown;

	bool    m_EvadeEnable;          // 스페이스바 회피기 활성화 여부

	bool    m_ESCButton;            // ESC키 Down

	// BowDraw
	bool    m_DrawWeaponEnable;
	bool	m_DrawWalkToSheatheEnable;

	// 공격
	bool    m_ChargingEnable;
	bool	m_ShotEnable;

	int		m_ChargingCount;
	int		m_QuickShotCount;
	bool	m_QuickShotEnable;
	bool	m_PowerShotEnable;


	bool	m_EvadeFrontShotEnable;
	bool	m_EvadeBackShotEnable;
	bool	m_EvadeLeftShotEnable;
	bool	m_EvadeRightShotEnable;
	bool	m_EvadeChangeAttack;

	bool	m_DragonShotEnable;
	float	m_DragonSpeed;

	// 우클릭 줌
	bool	m_JoomEnable;
	float	m_CameraDist;
	float	m_JoomTime;


	// Time관련
	float   m_EvadeTime;
	float   m_ChargingTime;
	float   m_DrawWeaponTime;
	float	m_DrawToSheateWalkTime;
	float	m_ReturnChargingCountTime;
	float	m_ReloadTime;
	float	m_ReturnQuickTime;

	// return
	bool m_ReturnEnable;

	// 화살 카운트
	int		m_ArrowCount;

	// 힐 오브젝과의 충돌
	bool	m_HealEnable;
	char m_HealObjName[64];

	// Hit 관련
	bool	m_MonsterCollision;
	bool	m_TrippingEnable;
	bool	m_RollEnable;

	// Carving
	bool	m_CarvingEnable;

	// Monster Name
	char m_BarnosName[64];
	char m_JagrasName[64];
	char m_KestodonName[64];
	char m_VespoidName[64];
	char m_AnjanthName[64];
	char m_RathalosName[64];

	// Hit Breath
	bool	m_IsHitBreath;
	float	m_HitBreathTime;

	// Roaring
	bool	m_IsRoaring;

	// NPC 충돌
	bool	m_IsSignCollision;
	bool	m_IsQuestAcept;
	bool	m_IsJump;

	Vector3	m_SlidingVec;
	bool	m_IsFieldCollision;
	char	m_FieldObjName[32];
	char	m_FieldBoxName[32];
	std::vector<std::string>	m_vecFieldObjName;
	std::vector<char*>	m_vecFieldBoxName;

	// 아래에 추가 부탁
	bool    m_FlightMode;           // 자유카메라 활성상태
	

	//플레이어 FSM
	FSM<CPlayer> PlayerFSM;

	// 플레이어 HUD.    
	CSharedPtr<class CPlayerHUD>      m_PlayerHUD;
	CSharedPtr<class CBottleSlotWindow>	m_BottleWindow;
	CSharedPtr<class CCarvingWindow> m_CarvingWindow;
	CSharedPtr<class CCarvingRightWindow>	m_CarvingRightWindow;
	CSharedPtr<class CQuestWindow>	m_QuestWindow;
	CGameObject* m_Obj;

public:
	bool GetChargingEnable()	const
	{
		return m_ChargingEnable;
	}

	bool GetDragonShotEnable()	const
	{
		return m_DragonShotEnable;
	}

	CArm* GetArm()	const
	{
		return m_Arm;
	}

	float GetPlayerHP()	const
	{
		return m_PlayerInfo->HP;
	}

	float GetPlayerMaxHP()	const
	{
		return m_PlayerInfo->MaxHP;
	}

	float GetPlayerStamina()	const
	{
		return m_PlayerInfo->Stamina;
	}

	float GetPlayerMaxStamina()	const
	{
		return m_PlayerInfo->MaxStamina;
	}
	
	float GetPlayerMaxAttack()	const
	{
		return m_PlayerInfo->AttackMax;
	}

	float GetPlayerMinAttack()	const
	{
		return m_PlayerInfo->AttackMin;
	}

	int GetChargingCount()	const
	{
		return m_ChargingCount;
	}

	bool GetHitBreath()	const
	{
		return m_IsHitBreath;
	}

	bool GetIsJump()	const
	{
		return m_IsJump;
	}

	float GetChargingTime()	const
	{
		return m_ChargingTime;
	}

public:
	void SetPlayerHP(float HP)
	{
		m_PlayerInfo->HP = HP;
	}

	void SetTransformState(Transform_State State)
	{
		m_Mesh->SetTransformState(State);
	}

	void SetESCEnable(bool Enable)
	{
		m_ESCButton = Enable;
	}

	void SetIsJump(bool Enable)
	{
		m_IsJump = Enable;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPlayer* Clone();

private:
	void MouseRotation(float DeltaTime);

private:
	void MoveFrontDown(float DeltaTime);
	void MoveBackDown(float DeltaTime);
	void MoveLeftDown(float DeltaTime);
	void MoveRightDown(float DeltaTime);

	void MoveFront(float DeltaTime);
	void MoveBack(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);

	void MoveFrontUp(float DeltaTime);
	void MoveBackUp(float DeltaTime);
	void MoveLeftUp(float DeltaTime);
	void MoveRightUp(float DeltaTime);

	// RunQuick
	//void RunQuickFrontDown(float DeltaTime);
	//void RunQuickBackDown(float DeltaTime);
	//void RunQuickLeftDown(float DeltaTime);
	//void RunQuickRightDown(float DeltaTime);

	void RunQuickFront(float DeltaTime);
	void RunQuickBack(float DeltaTime);
	void RunQuickLeft(float DeltaTime);
	void RunQuickRight(float DeltaTime);


	void RunQuickFrontUp(float DeltaTime);
	void RunQuickBackUp(float DeltaTime);
	void RunQuickLeftUp(float DeltaTime);
	void RunQuickRightUp(float DeltaTime);

	void EvadeClick(float DeltaTime);

	// Attack관련
	void ShotStart(float DeltaTime);
	void BowCharging(float DeltaTime);
	void ShotEnd(float DeltaTime);

	void ChargingJoomDown(float DeltaTime);
	void ChargingJoomUp(float DeltaTime);

	void EvadeShotDown(float DeltaTime);

	// QuickShot
	void QuickShotDown(float DeltaTime);


	// Draw
	void DrawWeapon(float DeltaTime);

	// Sheathe
	void Sheathe(float DeltaTime);

	// Potion
	void PotionDown(float DeltaTime);

	// Coating
	void CoatingDown(float DeltaTime);

	// 상호작용(Interaction)
	void InteractionDown(float DeltaTime);

	void ESC(float DeltaTime);

	// 노티파이
private:
	// Add
	void ShotStartAddNotify();
	void ShotWalkStartAddNotify();
	void DrowedWeaponToChargingAddNotify();

	void IdleSheatheAddnotify();
	void WalkSheatheAddNotify();

	void QuickShotAddNotify();
	void PowerShotAddNotify();

	void DragonShotStartAddNotify();
	void DragonShotAddNotify();

	void EvadeFrontShotChangeAddNotify();
	void EvadeBackShotChangeAddNotify();
	void EvadeLeftShotChangeAddNotify();
	void EvadeRightShotChangeAddNotify();

	void EvadeShotAddNotify();

	void TrippingByFrontAddNotify();
	void RollByFrontAddNotify();

	// Add Sound Notify
	void RunSoundNotify();

	void CoatingSoundNotify();

	void CarvingSoundStartNotify();

private:
	// End
	void ShotEndNotify();
	void RunStartNotify();
	void RunEnd();
	void EvadeEndNotify();
	void DrawedEvadeEndNotify();
	void DrawedEvadeToWalkStartEndNotify();
	void DrawedEvadeToWalkEndNotify();
	void DrawWeaponEndNotify();
	void SheathEndNotify();
	void WalkSheathEndNotify();

	// Draw
	void DrawWalkStartEndNotify();
	void DrawWalkEndNotify();
	void WalkAndDrawEndNotify();

	// Charging
	void DrawedWeaponToChargingEnd();
	void DrawedToChargingStartEnd();
	void ChargingStartIdleFirstEnd();
	void ChargedShotEnd();
	void FullChargedShotEnd();
	void DrawnWalkToChargingStartEnd();
	void ChargingWalkEnd();

	// Quick
	void QuickShotEnd();
	void PowerShotEnd();

	// Dragon
	void DragonShotStartEnd();
	void DragonShotEnd();

	// EvadeShot
	void EvadeShotEnd();
	void EvadeRealShotEnd();

	// Coating
	void CoatingEnd();

	// Carving
	void CarvingStartEnd();
	void CarvingEnd();

	// Hit
	void TrippingByFrontEnd();
	void TrippingToIdleEnd();

	void RollByFrontStartEnd();
	void RollByFrontEnd();
	void RollOverToIdleEnd();

	// BossRoaring
	void PlugEarsStartNotify();
	void PlugEarsEndNotify();

	// MernosDown
	void BHDown3EndNotify();

private:
	void SetKeyCallback();
	void SetNotify();

private:
	// Update
	void EvadeUpdate(float DeltaTime);
	void EvadeWalkUpdate(float DeltaTime);

	void DrawToSheatWalkUpdate(float DeltaTime);
	void ChargingUpdate(float DeltaTime);

	void DrawedWalkAndSheatheUpdate(float DeltaTime);

	void ChargingJoomInUpdate(float DeltaTime);
	void ChargingJoomOutUpdate(float DeltaTime);

	void ReturnChargingCountUpdate(float DeltaTime);

	void DragonShotUpdate(float DeltaTime);

	void EvadeShotUpdate(float DeltaTime);

	// Hit
	void HitUpdate(float DeltaTime);
	void HitRollUpdate(float DeltaTime);


	// MoveEnable
	void MoveEnableUpdate(float DeltaTime);


	void CameraRayUpdate(float DeltaTime);

	void BossRoaringUpdate(float DeltaTime);

	// 필드 오브젝 충돌
	void CollisionFieldObjUpdate(float DeltaTime);

	//Func
private:
	void RunFunc(float DeltaTime, float Rot);
	void DrawRunFunc(float DeltaTime, float Rot);
	void RunQuickFunc(float DeltaTime, float Rot);
	void ChangeBowFunc(const std::string& SocketName, const std::string& AnimationName);
	void ChargingWalkFunc(float DeltaTime, float Rot);
	void JoomRotationFunc(float DeltaTime, float Rot);
	void JoomWalkFunc(float DeltaTime, const std::string& Name, float Speed1, float Speed2);
	void ChargingJoomFunc(float DeltaTime, const std::string& Name, float Speed1, float Speed2);
	void ChargingShotDownFunc();
	void ChargingShotUpFunc();
	void EvadeChargingShotUpFunc();
	void BowEffectVfxStartFunc();
	void BowEffectVfxEndFunc();
	bool CheckAnimationFunc(bool Enable, const std::string& Name);
	void HealFlowerInteractionFunc();
	void MonsterCarvingFunc();
	void StaminaFunc(float DeltaTime);
	void CameraShakeFunc(float Strength, float Time);
	void DestroyArrowFunc();
	void CollisionToTrippingFunc(float Damage);
	void CollisionToRollFunc(float Damage);

	// 게시판
	void SignInteractionFunc();

private:
	void CubeCollisionFunc(CGameObject* FieldObj, CColliderBox3D* Box);
	void CuboidCollisionFunc(CGameObject* FieldObj, CColliderBox3D* Box, float DeltaTime);

private:
	void DeleteObjName(const std::string& ObjName);
	void DeleteBoxName(const char* BoxName);

private:
	void CollisionBegin(const CollisionResult& Result);
	void CollisionEnd(const CollisionResult& Result);


	void SlidingCollisionBegin(const CollisionResult& Result);
	void SlidingCollisionEnd(const CollisionResult& Result);

	// EventManager 콜백
	void QuestAcept();

private:
	static bool SortPos(const CollisionBoxInfo& Begin, const CollisionBoxInfo& End);

private:

private:
	//fsm
	//ChangeState 했을 때
	//Start는 첫 프레임에만 호출
	//Stay는 다른 상태로 ChangeState 할 때까지 매 프레임마다 호출
	//End는 다른 상태로 ChangeState 할 때 마지막 프레임에만 한 번 호출
	/*void IDLEStart();
	void IDLEStay();
	void IDLEEnd();*/

	// 자유카메라 진입 및 생성 콜백함수.
	// F11 키로 자유카메라 진입 및 해제할 수 있음.
	void FlightCallback(float DeltaTime);

	void MovePoint(float DeltaTime);
};

