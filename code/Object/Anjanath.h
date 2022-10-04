
#pragma once

#include "GameObject/GameObject.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderSphere.h"
#include "Component/ColliderBox3D.h"
#include "Component/LightComponent.h"
#include "FSM.h"

class CAnjanath :
	public CGameObject
{
	friend class CScene;

protected:
	CAnjanath();
	CAnjanath(const CAnjanath& obj);
	virtual ~CAnjanath();

private:
	CSharedPtr<CAnimationMeshComponent>		m_Mesh;
	CSharedPtr<CLightComponent>				m_HeadLight;
	CSharedPtr<CColliderBox3D>				m_SpotCollider;

	CSharedPtr<CColliderBox3D>				m_CarvingCollider;
	CSharedPtr<CColliderBox3D>				m_BiteCollider;
	CSharedPtr<CColliderBox3D>				m_ChargeCollider;

	CSharedPtr<CColliderBox3D>				m_RightBackLegCollider;
	CSharedPtr<CColliderBox3D>				m_LeftBackLegCollider;
	CSharedPtr<CColliderBox3D>				m_RightFrontLegCollider;
	CSharedPtr<CColliderBox3D>				m_LeftFrontLegCollider;
	CSharedPtr<CColliderBox3D>				m_RightFootCollider;
	CSharedPtr<CColliderBox3D>				m_LeftFootCollider;
	CSharedPtr<CColliderBox3D>				m_Head1Collider;
	CSharedPtr<CColliderBox3D>				m_Head2Collider;
	CSharedPtr<CColliderBox3D>				m_BodyCollider;
	CSharedPtr<CColliderBox3D>				m_TailWithBodyCollider;
	CSharedPtr<CColliderBox3D>				m_TailCollider;
	CSharedPtr<CColliderBox3D>				m_SlidingCollider;

	//Anjanath FSM
	FSM<CAnjanath>* m_FSMAnjanath;

private:
	Vector3	m_PatrolPos[4];
	Vector3	m_PrevBreathDir;
	Vector3	m_Dir;

	int		m_WayPointNumber;
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
	bool	m_IsChargeAttacking;
	bool	m_IsBiteAttacking;
	bool	m_IsBreathAttacking;
	bool	m_IsRoaring;
	bool	m_IsTailDestroyed;
	bool	m_LeftFoot;
	bool	m_RightFoot;
	bool	m_IsCarvingEnd;

private:
	int		m_DamagedCount;
	int		m_TailDamagedCount;
	float	m_TotalDamaged;
	float	m_DamageTimeAcc;
	float	m_DamageTime;
	float	m_DeadTimeAcc;

private:
	int		m_BreathStack;
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
	bool IsChargeAttacking() const
	{
		return m_IsChargeAttacking;
	}

	bool IsBiteAttacking()	const
	{
		return m_IsBiteAttacking;
	}

	bool IsBreathAttacking()	const
	{
		return m_IsBreathAttacking;
	}

	bool IsRoaring() const
	{
		return m_IsRoaring;
	}


public:
	void SetDamage(float Damage);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CAnjanath* Clone();

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
	void GroggyStart();
	void GroggyStay();
	void GroggyEnd();
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
	void AttackDashStartEndFunction();
	void AttackDashEndFunction();
	void RoarStart();
	void RoarEnd();
	void RoarBlurEnd();
	void MoveSetNotify();
	void MoveLoopRotationCheck();
	void TripleBiteStart();
	void TripleBiteCombo1();
	void TripleBiteCombo2();
	void TripleBiteEnd();
	void CriticalDamagedStart();
	void CriticalDamagedEnd();
	void BreathReadyEnd();
	void BreathAttackEnd();
	void EnableBiteAttack();
	void DisableBiteAttack();
	void EnableChargeAttack();
	void DisableChargeAttack();
	void BreathReadyStart();
	void BreathSENotify();
	void IdleVoiceNotify();
	void RoaringMeetVoiceNotify();
	void RoaringCheckEndNotify();
	void RoaringVoiceNotify();
	void BiteAttackStartVoiceNotify();
	void BiteAttackVoiceNotify();
	void BiteEndRoarVoiceNotify();
	void ChargeAttackVoiceNotify();
	void CriticalVoiceNotify();
	void DeadVoiceNotify();
	void DeadEndNotify();
	 
	// Transform Notify
private:
	void MoveStart();
	void MoveEnd();
	void RotateLeft();
	void RotateRight();
	void RotateEnd();
	void BreathStart();
	void BreathEnd();

private:
	void Rotate(float DeltaTime);
	void Move(float DeltaTime);
	void FootStepCheck();
	void DeadCheck();
	void CriticalCheck();
	void FieldCollision(float DeltaTime);

private:
	void AttackPattern(bool AngleIn, bool RangeIn);
	bool CalcAngle();
	void CreateFlame();


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
