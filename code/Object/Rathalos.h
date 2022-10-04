
#pragma once

#include "GameObject/GameObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Component/LightComponent.h"
#include "FSM.h"

class CRathalos :
	public CGameObject
{
	friend class CScene;

protected:
	CRathalos();
	CRathalos(const CRathalos& obj);
	virtual ~CRathalos();

private:
	CSharedPtr<CAnimationMeshComponent>		m_Mesh;
	CSharedPtr<CLightComponent>				m_HeadLight;
	CSharedPtr<CColliderBox3D>				m_SpotCollider;

	CSharedPtr<CColliderBox3D>				m_CarvingCollider;
	CSharedPtr<CColliderBox3D>				m_BiteCollider;
	CSharedPtr<CColliderBox3D>				m_ChargeCollider;
	CSharedPtr<CColliderBox3D>				m_TailAttackCollider;

	CSharedPtr<CColliderBox3D>				m_RightLegCollider;
	CSharedPtr<CColliderBox3D>				m_LeftLegCollider;
	CSharedPtr<CColliderBox3D>				m_RightFootCollider;
	CSharedPtr<CColliderBox3D>				m_LeftFootCollider;
	CSharedPtr<CColliderBox3D>				m_Head1Collider;
	CSharedPtr<CColliderBox3D>				m_Head2Collider;
	CSharedPtr<CColliderBox3D>				m_BodyCollider;
	CSharedPtr<CColliderBox3D>				m_LeftWingCollider;
	CSharedPtr<CColliderBox3D>				m_RightWingCollider;
	CSharedPtr<CColliderBox3D>				m_TailWithBodyCollider;
	CSharedPtr<CColliderBox3D>				m_TailConnectionCollider;
	CSharedPtr<CColliderBox3D>				m_TailCollider;
	CSharedPtr<CColliderBox3D>				m_SlidingCollider;

	//Rathalos FSM
	FSM<CRathalos>* m_FSMRathalos;

private:
	Vector3	m_PatrolPos[4];
	Vector3	m_Dir;
	Vector3	m_PrevBreathDir;
	Vector3	m_PlayerPrevDir;
	int		m_WayPointNumber;
	int		m_FlyStack;
	bool	m_PatrolPosArrived;
	bool	m_PlayerDetected;
	float	m_PlayerDetectTimeAcc;
	float	m_PlayerDetectTime;
	float	m_MoveSpeed;
	float	m_PatrolDist;
	float	m_PatrolRot;
	float	m_FadeOpacity;

private:
	float	m_DeltaTime;
	float	m_RotateSpeed;
	float	m_PlayerDist;
	float	m_TargetRotateY;
	int8_t 	m_Rotate;		// -1, 0, 1만 체크하기 위해 int8_t로 선언함.
	bool	m_Move;
	bool	m_Dead;
	bool	m_DeadComplete;
	bool	m_IsAttacking;	// 실제 공격판정 확인 변수
	bool	m_LeftFoot;
	bool	m_RightFoot;
	bool	m_IsTailDestroyed;
	bool	m_Ascend;
	bool	m_SetRotate;
	bool	m_IsRoaring;
	bool	m_IsCarvingEnd;

private:
	int		m_DamagedCount;
	int		m_TailDamagedCount;
	float	m_TotalDamaged;
	float	m_DamageTimeAcc;
	float	m_DamageTime;
	float	m_DeadTimeAcc;

private:
	bool	m_Breath;
	float	m_BreathSpawnTime;
	float	m_BreathSpawnTimeAcc;
	float	m_BreathTrackingAngle;

private:
	float	m_HP;
	float	m_HPMax;
	float	m_AttackDamage;

private:
	CGameObject*	m_FieldObj;
	Box3DInfo		m_FieldBoxInfo;
	bool			m_IsFieldCollision;

private:
	float		m_WaitTime;
	float		m_WaitTimeAcc;
	bool		m_ReadyToMove;

public:
	bool IsAttacking() const
	{
		return m_IsAttacking;
	}

	bool IsRoaring() const
	{
		return m_IsRoaring;
	}

public:
	void SetDamage(float Damage);

public:
	virtual void Start();
	virtual void Update(float DeltaTime);
	virtual bool Init();
	virtual void PostUpdate(float DeltaTime);
	virtual CRathalos* Clone();

	//ChangeState 했을 때
	//Start는 첫 프레임에만 호출
	//Stay는 다른 상태로 ChangeState 할 때까지 매 프레임마다 호출
	//End는 다른 상태로 ChangeState 할 때 마지막 프레임에만 한 번 호출

	// FSMs
private:
	void IdleStart();
	void IdleStay();
	void IdleEnd();
	void NormaPatrolStart();
	void NormaPatrolStay();
	void NormaPatrolEnd();
	void DetectStart();
	void DetectStay();
	void DetectEnd();
	void TrackingStart();
	void TrackingStay();
	void TrackingEnd();
	void AttackStart();
	void AttackStay();
	void AttackEnd();
	void DeadStart();
	void DeadStay();
	void DeadEnd();

private:
	void SetAnimNotify();

	// Animation Notify
private:
	void NormalIdleEnd();
	void NormalMoveEnd();
	void NormalMoveStartEnd();
	void NormalTurnLeftStartEndFunction();
	void NormalTurnLeftEndFunction();
	void NormalTurnRightStartEndFunction();
	void NormalTurnRightEndFunction();
	void AgressiveTurnLeftEndFunction();
	void AgressiveTurnRightEndFunction();
	void AgressiveTurnEndFunction();
	void ChargeAttackStartEndFunction();
	void ChargeAttackEndEndFunction();
	void FlyStartEndFunction();
	void FlyToIdleEndFunction();
	void FlyIdleEndFunction();
	void FlyBreathStartEndFunction();
	void FlyBreathEndFunction();
	void LandStartEndFunction();
	void LandEndEndFunction();
	void RoarStart();
	void RoarEnd();
	void RoarBlurEnd();
	void MoveSetNotify();
	void MoveLoopRotationCheck();
	void SingleBiteStart();
	void SingleBiteEnd();
	void TailRotateStart();
	void TailRotateEnd();
	void TailAttackEnd();
	void CriticalDamagedStart();
	void CriticalDamagedEnd();
	void BreathReadyEnd();
	void BreathAttackEnd();
	void EnableBiteAttack();
	void DisableBiteAttack();
	void EnableTailAttack();
	void DisableTailAttack();
	void EnableChargeAttack();
	void DisableChargeAttack();
	void BreathReadyVoiceNotify();
	void BreathVoiceNotify();
	void FlyBreathVoiceNotify();
	void IdleVoiceNotify();
	void RoarReadyVoiceNotify();
	void RoaringMeetVoiceNotify();
	void RoaringCheckEndNotify();
	void RoaringShortVoiceNotify();
	void RoaringVoiceNotify();
	void BiteAttackVoiceNotify();
	void TailAttackStartVoiceNotify();
	void TailAttackEndVoiceNotify();
	void ChargeAttackVoiceNotify();
	void ChargeAttackEndVoiceNotify();
	void CriticalVoiceNotify();
	void DeadVoiceNotify();
	void BreathSENotify();
	void FlySENotify();
	void FlyBreathSENotify();
	void DeadEndNotify();

	// Transform Notify
private:
	void MoveStart();
	void MoveEnd();
	void RotateLeft();
	void RotateRight();
	void RotateEnd();
	void AscendStart();
	void AscendEnd();
	void DescentStart();
	void DescentEnd();
	void BreathStart();
	void BreathEnd();

private:
	void Rotate(float DeltaTime);
	void Move(float DeltaTime);
	void Ascend(float DeltaTime);
	void FootStepCheck();
	void DeadCheck();
	void CriticalCheck();
	void FieldCollision(float DeltaTime);

private:
	void AttackPattern(bool AngleIn, bool RangeIn);
	bool CalcAngle();
	void CreateFlame();
	void CreateFireball();

	// Collision Callback Function
public:
	void WeaponOnCollisionBegin(const CollisionResult& result);
	void TailOnCollisionBegin(const CollisionResult& result);
	void SpotOnCollisionBegin(const CollisionResult& result);
	void SpotOnCollisionEnd(const CollisionResult& result);
	void SlidingOnCollisionBegin(const CollisionResult& result);
	void SlidingOnCollisionEnd(const CollisionResult& result);

private:
	void SetTargetCam();
	void SetMernos();

public:
	void SetDestroyCarvingCollider();

};

