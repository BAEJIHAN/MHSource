
#include "Rathalos.h"
#include "RathalosTail.h"
#include "RathalosAnimation.h"
#include "Player.h"
#include "FlameEffect.h"
#include "BurnedDecal.h"
#include "Scene/Scene.h"
#include "TargetingCamera.h"
#include "EventManager.h"
#include "ObjectManager.h"
#include "HDR.h"
#include "Scene/SceneManager.h"
#include "Mernos.h"
#include "../ClientManager3D.h"
#include "../Scene/MainSceneMode.h"

CRathalos::CRathalos() :
	m_PatrolPosArrived(false),
	m_MoveSpeed(10.f),
	m_Rotate(0),
	m_Move(false),
	m_RotateSpeed(90.f),
	m_PatrolDist(0.f),
	m_WayPointNumber(0),
	m_PlayerDetected(false),
	m_PlayerDetectTime(5.f),
	m_PlayerDetectTimeAcc(0.f),
	m_PlayerDist(40.f),
	m_Dir(0.f, 0.f, 1.f),
	m_FlyStack(0),
	m_Ascend(false),
	m_SetRotate(false), // 임의 회전속도를 올리기위한 bool
	m_TailDamagedCount(0),
	m_IsTailDestroyed(false),
	m_DamagedCount(0),
	m_TotalDamaged(0.f),
	m_DamageTime(1.f),
	m_DamageTimeAcc(1.f),
	m_DeadTimeAcc(0.f),
	m_FadeOpacity(1.f),
	m_Breath(false),
	m_BreathSpawnTime(0.1f),
	m_BreathSpawnTimeAcc(0.f),
	m_BreathTrackingAngle(30.f),
	m_IsAttacking(false),
	m_IsRoaring(false),
	m_HP(1000),
	m_HPMax(1000),
	m_AttackDamage(30),
	m_Dead(false),
	m_DeadComplete(false),
	m_IsCarvingEnd(false),
	m_IsFieldCollision(false),
	m_FieldObj(nullptr),
	m_ReadyToMove(false),
	m_WaitTime(10.f),
	m_WaitTimeAcc(0.f)
{
	SetTypeID<CRathalos>();
}

CRathalos::CRathalos(const CRathalos& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("RathalosMesh");
}

CRathalos::~CRathalos()
{
	SAFE_DELETE(m_FSMRathalos);
}

bool CRathalos::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_FSMRathalos = new FSM<CRathalos>;
	m_FSMRathalos->CreateState("Idle", this, &CRathalos::IdleStay, &CRathalos::IdleStart, &CRathalos::IdleEnd);
	m_FSMRathalos->CreateState("Patrol", this, &CRathalos::NormaPatrolStay, &CRathalos::NormaPatrolStart, &CRathalos::NormaPatrolEnd);
	m_FSMRathalos->CreateState("PlayerDetected", this, &CRathalos::DetectStay, &CRathalos::DetectStart, &CRathalos::DetectEnd);
	m_FSMRathalos->CreateState("PlayerTracking", this, &CRathalos::TrackingStay, &CRathalos::TrackingStart, &CRathalos::TrackingEnd);
	m_FSMRathalos->CreateState("Attack", this, &CRathalos::AttackStay, &CRathalos::AttackStart, &CRathalos::AttackEnd);
	m_FSMRathalos->CreateState("Dead", this, &CRathalos::DeadStay, &CRathalos::DeadStart, &CRathalos::DeadEnd);

	m_Mesh = CreateComponent<CAnimationMeshComponent>("RathalosMesh");
	m_Mesh->SetMesh("RathalosMesh");
	m_Mesh->CreateAnimationInstance<CRathalosAnimation>();

	m_HeadLight = CreateComponent<CLightComponent>("AnjanathPointLight");
	m_HeadLight->SetInheritRotY(true);
	m_HeadLight->SetLightType(Light_Type::Point);
	m_HeadLight->SetDistance(50.f);
	m_HeadLight->SetAtt3(0.01f);
	m_HeadLight->SetColor(Vector4(1.f, 0.5f, 0.f, 1.f));
	m_HeadLight->Enable(false);

	m_RightLegCollider = CreateComponent<CColliderBox3D>("RightLegCollider");
	m_LeftLegCollider = CreateComponent<CColliderBox3D>("LeftLegCollider");
	m_RightFootCollider = CreateComponent<CColliderBox3D>("RightFootCollider");
	m_LeftFootCollider = CreateComponent<CColliderBox3D>("LeftFootCollider");
	m_Head1Collider = CreateComponent<CColliderBox3D>("Head1Collider");
	m_Head2Collider = CreateComponent<CColliderBox3D>("Head2Collider");
	m_BodyCollider = CreateComponent<CColliderBox3D>("BodyCollider");
	m_LeftWingCollider = CreateComponent<CColliderBox3D>("LeftWingCollider");
	m_RightWingCollider = CreateComponent<CColliderBox3D>("RightWingCollider");
	m_TailWithBodyCollider = CreateComponent<CColliderBox3D>("TailWithBodyCollider");
	m_TailConnectionCollider = CreateComponent<CColliderBox3D>("TailConnectionCollider");
	m_TailCollider = CreateComponent<CColliderBox3D>("TailCollider");
	m_SpotCollider = CreateComponent<CColliderBox3D>("SpotCollider");
	m_CarvingCollider = CreateComponent<CColliderBox3D>("ColliderCarving");
	m_BiteCollider = CreateComponent<CColliderBox3D>("BiteCollider");
	m_TailAttackCollider = CreateComponent<CColliderBox3D>("TailAttackCollider");
	m_ChargeCollider = CreateComponent<CColliderBox3D>("ChargeCollider");
	m_SlidingCollider = CreateComponent<CColliderBox3D>("SlidingCollider");


	m_RightLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_RightFootCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftFootCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_Head1Collider->Set3DExtent(2.f, 2.f, 2.f);
	m_Head2Collider->Set3DExtent(2.f, 2.f, 2.f);
	m_BodyCollider->Set3DExtent(4.f, 4.f, 10.f);
	m_LeftWingCollider->Set3DExtent(5.f, 2.f, 7.f);
	m_RightWingCollider->Set3DExtent(5.f, 2.f, 7.f);
	m_TailWithBodyCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_TailConnectionCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_TailCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_SpotCollider->Set3DExtent(80.f, 30.f, 80.f);
	m_SlidingCollider->Set3DExtent(10.f, 5.f, 4.f);

	m_CarvingCollider->Set3DExtent(10.f, 10.f, 10.f);
	m_BiteCollider->Set3DExtent(6.f, 6.f, 6.f);
	m_TailAttackCollider->Set3DExtent(8.f, 8.f, 8.f);
	m_ChargeCollider->Set3DExtent(10.f, 10.f, 10.f);

	m_SpotCollider->SetOffset(0.f, 5.f, 0.f);
	m_CarvingCollider->SetOffset(0.f, 10.f, 0.f);
	m_ChargeCollider->SetOffset(0.f, 7.f, 4.f);
	m_SlidingCollider->SetOffset(0.f, 5.f, 0.f);

	m_RightLegCollider->SetCollisionProfile("Monster");
	m_LeftLegCollider->SetCollisionProfile("Monster");
	m_RightFootCollider->SetCollisionProfile("Monster");
	m_LeftFootCollider->SetCollisionProfile("Monster");
	m_Head1Collider->SetCollisionProfile("Monster");
	m_Head2Collider->SetCollisionProfile("Monster");
	m_BodyCollider->SetCollisionProfile("Monster");
	m_LeftWingCollider->SetCollisionProfile("Monster");
	m_RightWingCollider->SetCollisionProfile("Monster");
	m_TailWithBodyCollider->SetCollisionProfile("Monster");
	m_TailConnectionCollider->SetCollisionProfile("Monster");
	m_TailCollider->SetCollisionProfile("Monster");
	m_SpotCollider->SetCollisionProfile("MonsterSpot");
	m_CarvingCollider->SetCollisionProfile("Carving");
	m_BiteCollider->SetCollisionProfile("MonsterAttack");
	m_TailAttackCollider->SetCollisionProfile("MonsterAttack");
	m_ChargeCollider->SetCollisionProfile("MonsterAttack");
	m_SlidingCollider->SetCollisionProfile("MonsterSliding");

	m_RightLegCollider->SetInheritRotY(true);
	m_LeftLegCollider->SetInheritRotY(true);
	m_RightFootCollider->SetInheritRotY(true);
	m_LeftFootCollider->SetInheritRotY(true);
	m_Head1Collider->SetInheritRotY(true);
	m_Head2Collider->SetInheritRotY(true);
	m_BodyCollider->SetInheritRotY(true);
	m_LeftWingCollider->SetInheritRotY(true);
	m_RightWingCollider->SetInheritRotY(true);
	m_TailWithBodyCollider->SetInheritRotY(true);
	m_TailConnectionCollider->SetInheritRotY(true);
	m_TailCollider->SetInheritRotY(true);
	m_SpotCollider->SetInheritRotY(true);
	m_CarvingCollider->SetInheritRotY(true);
	m_BiteCollider->SetInheritRotY(true);
	m_TailAttackCollider->SetInheritRotY(true);
	m_ChargeCollider->SetInheritRotY(true);

	m_RightLegCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_LeftLegCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_RightFootCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_LeftFootCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_Head1Collider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_Head2Collider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_BodyCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_LeftWingCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_RightWingCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_TailWithBodyCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_TailConnectionCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_TailConnectionCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::TailOnCollisionBegin);
	m_TailCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::WeaponOnCollisionBegin);
	m_TailCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::TailOnCollisionBegin);

	m_SpotCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::SpotOnCollisionBegin);
	m_SpotCollider->AddCollisionCallback(Collision_State::End, this, &CRathalos::SpotOnCollisionEnd);
	m_SlidingCollider->AddCollisionCallback(Collision_State::Begin, this, &CRathalos::SlidingOnCollisionBegin);
	m_SlidingCollider->AddCollisionCallback(Collision_State::End, this, &CRathalos::SlidingOnCollisionEnd);

	m_CarvingCollider->Enable(false);

	m_Mesh->AddChild(m_HeadLight);
	m_Mesh->AddChild(m_CarvingCollider);
	m_Mesh->AddChild(m_ChargeCollider);
	m_Mesh->AddChild(m_SlidingCollider);
	m_Mesh->AddChild(m_SpotCollider);

	m_Mesh->AddChild(m_BiteCollider, "Head1");
	m_Mesh->AddChild(m_TailAttackCollider, "Tail");
	m_Mesh->AddChild(m_RightLegCollider, "RightLeg");
	m_Mesh->AddChild(m_LeftLegCollider, "LeftLeg");
	m_Mesh->AddChild(m_RightFootCollider, "RightFoot");
	m_Mesh->AddChild(m_LeftFootCollider, "LeftFoot");
	m_Mesh->AddChild(m_Head1Collider, "Head1");
	m_Mesh->AddChild(m_Head2Collider, "Head2");
	m_Mesh->AddChild(m_BodyCollider, "Body");
	m_Mesh->AddChild(m_LeftWingCollider, "LeftWing");
	m_Mesh->AddChild(m_RightWingCollider, "RightWing");
	m_Mesh->AddChild(m_TailWithBodyCollider, "TailWithBody");
	m_Mesh->AddChild(m_TailConnectionCollider, "TailConnection");
	m_Mesh->AddChild(m_TailCollider, "Tail");

	m_Mesh->SetRelativeScale(0.03f, 0.03f, 0.03f);
	m_Mesh->SetRelativeRotationY(180.f);

	CEventManager::GetInst()->AddEventCallback<CRathalos>("BossDead", this, &CRathalos::SetTargetCam);
	CEventManager::GetInst()->AddEventCallback<CRathalos>("QuestAcept", this, &CRathalos::SetMernos);

	SetAnimNotify();

	return true;
}

void CRathalos::SetDamage(float Damage)
{
	m_HP -= Damage;

	m_TotalDamaged += Damage;

	m_DamageTimeAcc = m_DamageTime;

	if (m_HP <= 0.f)
	{
		if (!m_Dead)
		{
			m_Dead = true;
		}
	}
}

void CRathalos::Start()
{
	CGameObject::Start();

	Vector3 CurrentPos = GetWorldPos();

	m_PatrolPos[0] = Vector3(CurrentPos.x - 20.f, 0.f, CurrentPos.z + 20.f);
	m_PatrolPos[1] = Vector3(CurrentPos.x + 20.f, 0.f, CurrentPos.z + 20.f);
	m_PatrolPos[2] = Vector3(CurrentPos.x + 20.f, 0.f, CurrentPos.z - 20.f);
	m_PatrolPos[3] = Vector3(CurrentPos.x - 20.f, 0.f, CurrentPos.z - 20.f);

	m_FSMRathalos->ChangeState("Patrol");
}

void CRathalos::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_DeltaTime = DeltaTime;

	// 순간 데미지 누적 초기화하기 위한 타임 계산
	if (m_DamageTimeAcc > 0.f)
	{
		m_DamageTimeAcc -= DeltaTime;

		if (m_DamageTimeAcc <= 0.f)
		{
			m_TotalDamaged = 0.f;
		}
	}

	m_FSMRathalos->Update();

	Move(DeltaTime);

	Rotate(DeltaTime);

	FootStepCheck();

	Ascend(DeltaTime);

	if (m_IsFieldCollision)
	{
		FieldCollision(DeltaTime);
	}
}

void CRathalos::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRathalos* CRathalos::Clone()
{
	return new CRathalos(*this);
}


void CRathalos::IdleStart()
{
}


// 아무것도 안하는 Idle
void CRathalos::IdleStay()
{
	DeadCheck();

	if (m_PlayerDetected)
	{
		m_PlayerDetectTimeAcc += m_DeltaTime;

		if (m_PlayerDetectTimeAcc > m_PlayerDetectTime)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("Roaring");
		}
	}
}

void CRathalos::IdleEnd()
{
}

void CRathalos::NormaPatrolStart()
{
	m_MoveSpeed = 10.f;

	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveStart");

	Vector3 CurrentPos = GetWorldPos();	
	Vector3 WayPointPos = m_PatrolPos[m_WayPointNumber];

	CurrentPos.y = 0.f;
	WayPointPos.y = 0.f;

	Vector3 MovePointDir = WayPointPos - CurrentPos;
	MovePointDir.Normalize();

	// 몬스터 전방벡터와 Up 벡터 외적으로 우향벡터 생성
	Vector3 CurrentRightDir = m_Dir.Cross(Vector3().Axis[AXIS::AXIS_Y]);

	bool	Left = false;

	//우향벡터와 플레이어 벡터의 내적.
	if (CurrentRightDir.Dot(MovePointDir) > 0)
	{
		Left = true;
	}

	float	Angle = m_Dir.Dot(MovePointDir);

	Angle = RadianToDegree(acosf(Angle));

	// 좌측일경우, 음각으로 회전.
	if (Left)
	{
		Angle *= -1.f;
	}

	AddRelativeRotationY(Angle);

	m_Dir = MovePointDir;

	MoveStart();
}

void CRathalos::NormaPatrolStay()
{
	DeadCheck();

	if (m_DamagedCount <= 0)
	{
		Vector3 CurrentPos = GetWorldPos();

		m_PatrolDist = CurrentPos.Distance(m_PatrolPos[m_WayPointNumber]);

		// 5m 이내일 경우
		if (m_PatrolDist < 5.f && !m_PatrolPosArrived)
		{
			// 도착표시.
			m_PatrolPosArrived = true;

			// WayPoint Index변경
			m_WayPointNumber++;

			if (m_WayPointNumber > 3)
			{
				m_WayPointNumber = 0;
			}

			Vector3 CurrentPos = GetWorldPos();
			Vector3 WayPointPos = m_PatrolPos[m_WayPointNumber];

			CurrentPos.y = 0.f;
			WayPointPos.y = 0.f;

			Vector3 MovePointDir = WayPointPos - CurrentPos;
			MovePointDir.Normalize();

			// 몬스터 전방벡터와 Up 벡터 외적으로 우향벡터 생성
			Vector3 CurrentRightDir = m_Dir.Cross(Vector3().Axis[AXIS::AXIS_Y]);

			bool	Left = false;

			//우향벡터와 플레이어 벡터의 내적.
			if (CurrentRightDir.Dot(MovePointDir) > 0)
			{
				Left = true;
			}

			float	Angle = m_Dir.Dot(MovePointDir);

			Angle = RadianToDegree(acosf(Angle));

			// 좌측일경우, 음각으로 회전.
			if (Left)
			{
				Angle *= -1.f;
			}

			AddRelativeRotationY(Angle);

			m_Dir = MovePointDir;
		}

		else
		{
			m_Move = true;

			m_PatrolPosArrived = false;
		}
	}

	if (m_PlayerDetected)
	{
		m_PlayerDetectTimeAcc += m_DeltaTime;

		if (m_PlayerDetectTimeAcc > m_PlayerDetectTime)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("Roaring");

			m_FSMRathalos->ChangeState("PlayerDetected");
		}
	}
}

void CRathalos::NormaPatrolEnd()
{
	m_Move = false;
}

void CRathalos::DetectStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("Roaring");
}

void CRathalos::DetectStay()
{
	CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::FinalBossBattle);

	DeadCheck();

	if (m_PlayerDetected && m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("NormalIdle"))
	{
		m_FSMRathalos->ChangeState("PlayerTracking");
	}
}

void CRathalos::DetectEnd()
{
}

void CRathalos::TrackingStart()
{
	CalcAngle();
}

void CRathalos::TrackingStay()
{
	DeadCheck();

	if (m_Rotate == 0)
	{
		if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("NormalIdle"))
		{
			m_FSMRathalos->ChangeState("Attack");
		}
	}

	else if (m_Rotate == 1)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveTurnRight");
	}

	else if (m_Rotate == -1)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveTurnLeft");
	}
}

void CRathalos::TrackingEnd()
{
}

void CRathalos::AttackStart()
{
	m_MoveSpeed = 45.f;

	m_FlyStack++;

	// Ready to fly for BreathAttack.
	if (m_FlyStack >= 5 && m_PlayerDist >= 50.f && m_HP > (m_HPMax / 2.f))
	{
		m_Mesh->SetTransformState(Transform_State::Falling);

		m_Mesh->GetAnimationInstance()->ChangeAnimation("FlyStart");
	}

	else
	{
		if (m_PlayerDist < 50.f)
		{
			int RandVal = rand() % 3;

			switch (RandVal)
			{
				case 0:
				{
					m_Dir = m_PlayerPrevDir;

					m_Mesh->GetAnimationInstance()->ChangeAnimation("TailAttack");
					break;
				}

				case 1:
				{
					m_Mesh->GetAnimationInstance()->ChangeAnimation("BiteStart");
					break;
				}

				case 2:
				{
					m_Mesh->GetAnimationInstance()->ChangeAnimation("ChargeStart");
					break;
				}
			}
		}

		else if (m_PlayerDist >= 50.f && m_PlayerDist < 65.f)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("GroundBreathStart");
		}

		else
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("ChargeStart");
		}
	}
}

void CRathalos::AttackStay()
{
	DeadCheck();

	CreateFlame();
}

void CRathalos::AttackEnd()
{
	if (m_FlyStack >= 5)
	{
		m_FlyStack = 0;
	}
}

void CRathalos::DeadStart()
{
	MoveEnd();
	RotateEnd();
	BreathEnd();
	DisableBiteAttack();
	DisableChargeAttack();
	DisableTailAttack();

	const std::list<CSceneComponent*> List = GetSceneComponents();

	auto	iter = List.begin();
	auto	iterEnd = List.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->CheckType<CColliderBox3D>())
		{
			(*iter)->Enable(false);
		}
	}

	m_CarvingCollider->Enable(true);

	m_Mesh->GetAnimationInstance()->ChangeAnimation("Dead");

	CEventManager::GetInst()->CallEvent("PlayerMonsterRelease");
}

void CRathalos::DeadStay()
{
	if (m_DeadTimeAcc < 2.f)
	{
		m_DeadTimeAcc += m_DeltaTime;

		if (m_DeadTimeAcc > 2.f && !m_DeadComplete)
		{
			m_DeadComplete = true;

			CEventManager::GetInst()->CallEvent("BossDead");
		}
	}

	if (!m_CarvingCollider->IsEnable())
	{
		float DeltaTime = CEngine::GetInst()->GetDeltaTime();

		m_FadeOpacity -= (float)(DeltaTime * 0.1f);

		int Count = m_Mesh->GetMaterialSlotCount();

		for (int i = 0; i < Count; ++i)
		{
			m_Mesh->SetOpacity(m_FadeOpacity, i);
		}

		if (m_FadeOpacity <= 0.f && !m_IsCarvingEnd)
		{
			m_IsCarvingEnd = true;

			CEventManager::GetInst()->CallEvent("QuestAcept");
		}
	}
}

void CRathalos::DeadEnd()
{
}

void CRathalos::SetAnimNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("NormalMoveStart", this, &CRathalos::NormalMoveStartEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("NormalMoveEnd", this, &CRathalos::NormalMoveEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("NormalTurnLeft", this, &CRathalos::NormalTurnLeftEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("NormalTurnRight", this, &CRathalos::NormalTurnRightEndFunction);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("AgressiveTurnLeft", this, &CRathalos::AgressiveTurnLeftEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("AgressiveTurnRight", this, &CRathalos::AgressiveTurnRightEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("AgressiveTurnEnd", this, &CRathalos::AgressiveTurnEndFunction);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("BiteStart", this, &CRathalos::SingleBiteStart);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("BiteEnd", this, &CRathalos::SingleBiteEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("Roaring", this, &CRathalos::RoarEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("ChargeStart", this, &CRathalos::ChargeAttackStartEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("ChargeEnd", this, &CRathalos::ChargeAttackEndEndFunction);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("TailAttack", this, &CRathalos::TailAttackEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("FlyStart", this, &CRathalos::FlyStartEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("FlyToIdle", this, &CRathalos::FlyToIdleEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("FlyIdle", this, &CRathalos::FlyIdleEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("FlyBreathStart", this, &CRathalos::FlyBreathStartEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("FlyBreath", this, &CRathalos::FlyBreathEndFunction);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("LandStart", this, &CRathalos::LandStartEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("LandEnd", this, &CRathalos::LandEndEndFunction);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("Damaged", this, &CRathalos::CriticalDamagedEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("FlyDamaged", this, &CRathalos::CriticalDamagedEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("GroundBreathStart", this, &CRathalos::BreathReadyEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("GroundBreathAttack", this, &CRathalos::BreathAttackEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CRathalos>("Dead", this, &CRathalos::DeadEndNotify);


	// AddNotify
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("NormalIdle", "NormalIdleVoice", 1, this, &CRathalos::IdleVoiceNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("BiteStart", "TailAttackStartVoice", 1, this, &CRathalos::TailAttackStartVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("BiteEnd", "EnableBiteAttack", 2, this, &CRathalos::EnableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("BiteEnd", "BiteAttackVoice", 2, this, &CRathalos::BiteAttackVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("BiteEnd", "DisableBiteAttack", 15, this, &CRathalos::DisableBiteAttack);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("ChargeStart", "ChargeAttackVoice", 1, this, &CRathalos::RoaringShortVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("ChargeStart", "MoveStart", 22, this, &CRathalos::MoveStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("ChargeStart", "EnableChargeAttack", 22, this, &CRathalos::EnableChargeAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("ChargeEnd", "BiteAttackVoice", 45, this, &CRathalos::BiteAttackVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("ChargeEnd", "MoveEnd", 65, this, &CRathalos::MoveEnd);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("ChargeEnd", "DisableChargeAttack", 70, this, &CRathalos::DisableChargeAttack);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("TailAttack", "TailAttackStartVoice", 1, this, &CRathalos::TailAttackStartVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("TailAttack", "RotateStart", 103, this, &CRathalos::TailRotateStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("TailAttack", "EnableTailAttack", 103, this, &CRathalos::EnableTailAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("TailAttack", "DisableTailAttack", 132, this, &CRathalos::DisableTailAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("TailAttack", "RotateEnd", 132, this, &CRathalos::TailRotateEnd);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("TailAttack", "RoaringShort", 135, this, &CRathalos::TailAttackEndVoiceNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("Roaring", "RoarStart", 0, this, &CRathalos::RoarStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("Roaring", "RoarReady", 1, this, &CRathalos::RoarReadyVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("Roaring", "RoarMeet", 100, this, &CRathalos::RoaringMeetVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("Roaring", "PlayerRoarCheckEnd", 104, this, &CRathalos::RoaringCheckEndNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("Roaring", "RoarBlurEnd", 164, this, &CRathalos::RoarBlurEnd);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyStart", "FlySE", 53, this, &CRathalos::FlySENotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyToIdle", "FlySE", 36, this, &CRathalos::FlySENotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyIdle", "FlySE", 54, this, &CRathalos::FlySENotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyBreathStart", "FlySE", 37, this, &CRathalos::FlySENotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyBreath", "FlySE", 16, this, &CRathalos::FlySENotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyBreath", "FlySE", 54, this, &CRathalos::FlySENotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyBreath", "FlySE", 112, this, &CRathalos::FlySENotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("LandStart", "FlySE", 2, this, &CRathalos::FlySENotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyToIdle", "AscendStart", 0, this, &CRathalos::AscendStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyToIdle", "AscendEnd", 10, this, &CRathalos::AscendEnd);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("LandStart", "DescentStart", 37, this, &CRathalos::DescentStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("LandEnd", "DescentEnd", 3, this, &CRathalos::DescentEnd);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("Damaged", "CriticalState", 0, this, &CRathalos::CriticalDamagedStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("Damaged", "CriticalDamagedVoice", 1, this, &CRathalos::CriticalVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyDamaged", "CriticalState", 0, this, &CRathalos::CriticalDamagedStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyDamaged", "CriticalDamagedVoice", 1, this, &CRathalos::CriticalVoiceNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("GroundBreathStart", "BreathReadyVoice", 9, this, &CRathalos::BreathReadyVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("GroundBreathAttack", "BreathStart", 23, this, &CRathalos::BreathStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("GroundBreathAttack", "BreathAttackVoice", 24, this, &CRathalos::BreathVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("GroundBreathAttack", "BreathAttackSE", 28, this, &CRathalos::BreathSENotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("GroundBreathAttack", "BreathEnd", 78, this, &CRathalos::BreathEnd);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("Dead", "DeadVoice", 1, this, &CRathalos::DeadVoiceNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyBreath", "FlyBreathVoice", 9, this, &CRathalos::FlyBreathVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyBreath", "Fireball", 20, this, &CRathalos::CreateFireball);
	m_Mesh->GetAnimationInstance()->AddNotify<CRathalos>("FlyBreath", "FireballSE", 16, this, &CRathalos::FlyBreathSENotify);
}

void CRathalos::NormalIdleEnd()
{
}

void CRathalos::NormalMoveEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
}

void CRathalos::NormalMoveStartEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CRathalos::NormalTurnLeftStartEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CRathalos::NormalTurnLeftEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CRathalos::NormalTurnRightStartEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CRathalos::NormalTurnRightEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CRathalos::AgressiveTurnLeftEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");

	RotateEnd();
}

void CRathalos::AgressiveTurnRightEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");

	RotateEnd();
}

void CRathalos::AgressiveTurnEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
}

void CRathalos::ChargeAttackStartEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("ChargeEnd");
}

void CRathalos::ChargeAttackEndEndFunction()
{
	m_FSMRathalos->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
}

void CRathalos::FlyStartEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("FlyToIdle");
}

void CRathalos::FlyToIdleEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("FlyIdle");
}

void CRathalos::FlyIdleEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("FlyBreathStart");
}

void CRathalos::FlyBreathStartEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("FlyBreath");
}

void CRathalos::FlyBreathEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("LandStart");
}

void CRathalos::LandStartEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("LandEnd");
}

void CRathalos::LandEndEndFunction()
{
	m_Mesh->SetTransformState(Transform_State::Ground);

	m_FSMRathalos->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
}

void CRathalos::RoarStart()
{
	m_Move = false;
}

void CRathalos::RoarEnd()
{
	m_FSMRathalos->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
}

void CRathalos::RoarBlurEnd()
{
	CHDR::GetInst()->SetBlurEnable(false);
}

void CRathalos::MoveSetNotify()
{
	// 
}

void CRathalos::MoveLoopRotationCheck()
{
}

void CRathalos::SingleBiteStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BiteEnd");
}

void CRathalos::SingleBiteEnd()
{
	m_FSMRathalos->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
}

void CRathalos::TailRotateStart()
{
	RotateRight();

	m_TargetRotateY = 180.f;

	m_SetRotate = true;

	// 회전하는 Frame수만큼의 FrameTime으로 계산.
	// 0.3828f는 바뀌면 안됨!
	m_RotateSpeed = m_TargetRotateY / 0.3828f;
}

void CRathalos::TailRotateEnd()
{
	RotateEnd();
	
	m_Dir = m_Mesh->GetRelativeAxis(AXIS::AXIS_Z);
	m_Dir *= -1.f;
	
	m_SetRotate = false;
}

void CRathalos::TailAttackEnd()
{
	m_FSMRathalos->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
}

void CRathalos::CriticalDamagedStart()
{
	MoveEnd();
	RotateEnd();
	BreathEnd();
	DisableBiteAttack();
	DisableChargeAttack();

	m_Dir = m_Mesh->GetRelativeAxis(AXIS::AXIS_Z);
	m_Dir *= -1.f;
}

void CRathalos::CriticalDamagedEnd()
{
	if (m_Mesh->GetTransformState() == Transform_State::Falling)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("FlyIdle");
	}

	else
	{
		m_FSMRathalos->ChangeState("PlayerTracking");

		m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
	}
}

void CRathalos::BreathReadyEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("GroundBreathAttack");
}

void CRathalos::BreathAttackEnd()
{
	m_FSMRathalos->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
}

void CRathalos::EnableBiteAttack()
{
	m_BiteCollider->Enable(true);

	m_IsAttacking = true;
}

void CRathalos::DisableBiteAttack()
{
	m_BiteCollider->Enable(false);

	m_IsAttacking = false;
}

void CRathalos::EnableTailAttack()
{
	m_TailAttackCollider->Enable(true);

	m_IsAttacking = true;
}

void CRathalos::DisableTailAttack()
{
	m_TailAttackCollider->Enable(false);

	m_IsAttacking = false;
}

void CRathalos::EnableChargeAttack()
{
	m_ChargeCollider->Enable(true);

	m_IsAttacking = true;
}

void CRathalos::DisableChargeAttack()
{
	m_ChargeCollider->Enable(false);

	m_IsAttacking = false;
}

void CRathalos::BreathReadyVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosBreathReady");
}

void CRathalos::BreathVoiceNotify()
{
	int RandVal = rand() % 2;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("RathalosBreathAttack1");
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("RathalosBreathAttack2");
		break;
	}
}

void CRathalos::FlyBreathVoiceNotify()
{
	int RandVal = rand() % 2;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("RathalosFlyBreathAttack1");
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("RathalosFlyBreathAttack2");
		break;
	}
}

void CRathalos::IdleVoiceNotify()
{
	int RandVal = rand() % 10;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("RathalosIdle1", this);
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("RathalosIdle2", this);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		break;
	}
}

void CRathalos::RoarReadyVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosRoarReady");
}

void CRathalos::RoaringMeetVoiceNotify()
{
	Vector3 PlayerPos = m_Scene->GetPlayerObject()->GetWorldPos();
	Vector3 CurPos = GetWorldPos();

	if (PlayerPos.Distance(CurPos) < 100.f)
	{
		CHDR::GetInst()->SetBlurEnable(true);
		m_IsRoaring = true;
	}

	m_Scene->GetResource()->SoundPlay("RathalosRoaringMeet");

	CEventManager::GetInst()->CallEvent("PlayerMonsterContant");
}

void CRathalos::RoaringCheckEndNotify()
{
	m_IsRoaring = false;
}

void CRathalos::RoaringShortVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosShortRoar1");
}

void CRathalos::RoaringVoiceNotify()
{
	int RandVal = rand() % 2;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("RathalosNormalRoar1");
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("RathalosNormalRoar2");
		break;
	}
}

void CRathalos::BiteAttackVoiceNotify()
{
	int RandVal = rand() % 2;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("RathalosBiteAttack1", this);
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("RathalosBiteAttack2", this);
		break;
	}
}

void CRathalos::TailAttackStartVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosTailAttack1");
}

void CRathalos::TailAttackEndVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosTailAttack2");
}

void CRathalos::ChargeAttackVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosChargeAttack1");
}

void CRathalos::ChargeAttackEndVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosChargeEnd");
}

void CRathalos::CriticalVoiceNotify()
{
	int RandVal = rand() % 2;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("RathalosCriticalDamaged1");
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("RathalosCriticalDamaged2");
		break;
	}
}

void CRathalos::DeadVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosDead");
}

void CRathalos::BreathSENotify()
{
	int RandVal = rand() % 2;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("RathalosShortBreath1SE");
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("RathalosShortBreath2SE");
		break;
	}
}

void CRathalos::FlySENotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosFlyAir1SE", this);
}

void CRathalos::FlyBreathSENotify()
{
	m_Scene->GetResource()->SoundPlay("RathalosFlyBreathSE");
}

void CRathalos::DeadEndNotify()
{
	CEventManager::GetInst()->CallEvent("BossDeadEnd");
}

void CRathalos::MoveStart()
{
	m_Move = true;
}

void CRathalos::MoveEnd()
{
	m_Move = false;
}

void CRathalos::RotateLeft()
{
	m_Rotate = -1;
}

void CRathalos::RotateRight()
{
	m_Rotate = 1;
}

void CRathalos::RotateEnd()
{
	m_Rotate = 0;
}

void CRathalos::AscendStart()
{
	m_MoveSpeed *= 3.5f;

	m_Ascend = true;
}

void CRathalos::AscendEnd()
{
	m_MoveSpeed /= 2.5f;

	m_Ascend = false;
}

void CRathalos::DescentStart()
{
	m_MoveSpeed *= -2.f;

	m_Ascend = true;
}

void CRathalos::DescentEnd()
{
	m_MoveSpeed /= -2.f;

	m_Ascend = false;
}

void CRathalos::BreathStart()
{
	m_Breath = true;

	m_HeadLight->Enable(true);

	Vector3 Pos = m_Mesh->GetSocketPos("Head1");
	Pos.y -= 3.f;

	Vector3 CurDir = GetRelativeAxis(AXIS::AXIS_Z) * -1.f;
	Pos += (CurDir * 5.f);

	m_HeadLight->SetWorldPos(Pos);
}

void CRathalos::BreathEnd()
{
	m_Breath = false;

	m_HeadLight->Enable(false);
}

void CRathalos::Rotate(float DeltaTime)
{
	// 0일 경우, 증감자체를 하지않음.
	if (m_Rotate == 0)
	{
		return;
	}

	else
	{
		// 임의 설정을 하지 않았으면
		// TargetDegree와 PlayTime을 나눠 회전속도를 구함.
		if (!m_SetRotate)
		{
			float AnimPlayTime = m_Mesh->GetAnimationInstance()->GetCurrentAnimation()->GetPlayTime();

			m_RotateSpeed = m_TargetRotateY / AnimPlayTime;
		}

		AddRelativeRotationY(m_RotateSpeed * DeltaTime);
	}
}

void CRathalos::Move(float DeltaTime)
{
	if (!m_Move)
	{
		return;
	}

	else
	{
		AddRelativePos(m_Dir * m_MoveSpeed * DeltaTime);
	}
}

void CRathalos::Ascend(float DeltaTime)
{
	if (!m_Ascend)
	{
		return;
	}

	else
	{
		// 하강중일때
		if (m_MoveSpeed <= -1.f)
		{
			Vector3 CurrPos = GetWorldPos();

			float YPos = GetScene()->GetNavigation3DManager()->GetY(GetWorldPos());

			if (CurrPos.y < YPos)
			{
				m_Ascend = false;

				return;
			}
		}
		
		AddRelativePos(Vector3().Axis[AXIS::AXIS_Y] * m_MoveSpeed * DeltaTime);
	}
}

void CRathalos::FootStepCheck()
{
	// 죽었거나, 나는 중이라면 무시.
	if (m_Dead || m_Mesh->GetTransformState() == Transform_State::Falling)
		return;

	float LeftFootY = m_Mesh->GetSocketPos("LeftFoot").y;
	float RightFootY = m_Mesh->GetSocketPos("RightFoot").y;

	// Normal Idle 상태일때,
	if (m_FSMRathalos->CheckCurrentState("Idle") || m_FSMRathalos->CheckCurrentState("Patrol"))
	{
		// Check left foot
		if (LeftFootY - 2.5f <= GetWorldPos().y)
		{
			if (!m_LeftFoot)
			{
				int RandVal = rand() % 2;

				switch (RandVal)
				{
				case 0:
					m_Scene->GetResource()->SoundPlay("RathalosSlowFootStep1SE", this);
					break;
				case 1:
					m_Scene->GetResource()->SoundPlay("RathalosSlowFootStep2SE", this);
					break;
				}
			}

			m_LeftFoot = true;
		}

		else
		{
			m_LeftFoot = false;
		}

		// Check right foot
		if (RightFootY - 2.5f <= GetWorldPos().y)
		{
			if (!m_RightFoot)
			{
				int RandVal = rand() % 2;

				switch (RandVal)
				{
				case 0:
					m_Scene->GetResource()->SoundPlay("RathalosSlowFootStep1SE", this);
					break;
				case 1:
					m_Scene->GetResource()->SoundPlay("RathalosSlowFootStep2SE", this);
					break;
				}
			}

			m_RightFoot = true;
		}

		else
		{
			m_RightFoot = false;
		}
	}

	// Agressive, Tracking 상태일때,
	else
	{
		if (LeftFootY - 2.5f <= GetWorldPos().y)
		{
			if (!m_LeftFoot)
			{
				int RandVal = rand() % 2;

				switch (RandVal)
				{
				case 0:
					m_Scene->GetResource()->SoundPlay("RathalosFastFootStep1SE", this);
					break;
				case 1:
					m_Scene->GetResource()->SoundPlay("RathalosFastFootStep2SE", this);
					break;
				}
			}

			m_LeftFoot = true;
		}

		else
		{
			m_LeftFoot = false;
		}

		// Check right foot
		if (RightFootY - 2.5f <= GetWorldPos().y)
		{
			if (!m_RightFoot)
			{
				int RandVal = rand() % 2;

				switch (RandVal)
				{
				case 0:
					m_Scene->GetResource()->SoundPlay("RathalosFastFootStep1SE", this);
					break;
				case 1:
					m_Scene->GetResource()->SoundPlay("RathalosFastFootStep2SE", this);
					break;
				}
			}

			m_RightFoot = true;
		}

		else
		{
			m_RightFoot = false;
		}

	}
}

void CRathalos::DeadCheck()
{
	if (m_Dead)
	{
		m_FSMRathalos->ChangeState("Dead");
	}
}

void CRathalos::CriticalCheck()
{
	if (m_TotalDamaged > 100.f)
	{
		m_TotalDamaged = 0.f;

		if (m_Mesh->GetTransformState() == Transform_State::Falling)
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("FlyDamaged");
		}

		else if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("Damaged"))
		{
			CriticalDamagedStart();

			m_Mesh->GetAnimationInstance()->ChangeAnimation("Damaged");
		}
	}
}

void CRathalos::FieldCollision(float DeltaTime)
{
	Vector3 Dir = Vector3(m_FieldObj->GetWorldPos() - GetWorldPos());
	Dir.Normalize();
	Dir *= -1;

	AddWorldPos(Dir * m_MoveSpeed * DeltaTime);
}

void CRathalos::AttackPattern(bool AngleIn, bool RangeIn)
{
}

bool CRathalos::CalcAngle()
{
	// 플레이어간의 위치.
	Vector3 PlayerPos = m_Scene->GetPlayerObject()->GetWorldPos();
	Vector3 WorldPos = GetWorldPos();

	m_PlayerDist = PlayerPos.Distance(WorldPos);

	// (몬스터 --> Player) Vector 생성
	Vector3 PlayerDir = PlayerPos - WorldPos;
	PlayerDir.y = 0.f;

	// 현재 몬스터의 전방Vector 생성
	Vector3 CurrentDir = m_Dir;
	CurrentDir.y = 0.f;

	// 몬스터 전방Vector, 플레이어 벡터의 Normalize.
	CurrentDir.Normalize();
	PlayerDir.Normalize();

	// 몬스터 전방벡터와 Up 벡터 외적으로 우향벡터 생성
	Vector3 CurrentRightDir = CurrentDir.Cross(Vector3().Axis[AXIS::AXIS_Y]);

	bool	Left = false;

	//우향벡터와 플레이어 벡터의 내적.
	if (CurrentRightDir.Dot(PlayerDir) > 0)
	{
		Left = true;
	}

	float	Angle = CurrentDir.Dot(PlayerDir);

	Angle = RadianToDegree(acosf(Angle));

	// 좌측일경우, 음각으로 회전.
	if (Left)
	{
		Angle *= -1.f;
	}

	m_TargetRotateY = Angle;


	// 이전 플레이어 위치의 방향을 저장.(꼬리공격의 회전으로 인한 몬스터 전방벡터 손실방지)
	m_PlayerPrevDir = m_Dir;

	// 플레이어 벡터를 몬스터 전방벡터로 갱신.
	m_Dir = PlayerDir;

	if (Angle >= 0.f)
	{
		RotateRight();
	}

	else if (Angle < 0.f)
	{
		RotateLeft();
	}


	return true;
}

void CRathalos::CreateFlame()
{
	if (!m_Breath)
	{
		m_BreathSpawnTimeAcc = 0.f;

		m_PrevBreathDir = m_Dir;

		return;
	}

	// Player <--> 리오레우스 각도 계산 시작
	Vector3 PlayerDir = CSceneManager::GetInst()->GetPlayerObject()->GetWorldPos();
	Vector3 MyPos = GetWorldPos();

	PlayerDir -= MyPos;
	PlayerDir.Normalize();

	// 몬스터 전방벡터와 Up 벡터 외적으로 우향벡터 생성
	Vector3 CurrentRightDir = m_Dir.Cross(Vector3().Axis[AXIS::AXIS_Y]);

	bool	Left = false;

	//우향벡터와 플레이어 벡터의 내적.
	if (CurrentRightDir.Dot(PlayerDir) > 0)
	{
		Left = true;
	}

	float	Angle = m_Dir.Dot(PlayerDir);

	Angle = RadianToDegree(acosf(Angle));

	// 좌측일경우, 음각으로 회전.
	if (Left)
	{
		Angle *= -1.f;
	}


	m_BreathSpawnTimeAcc += m_DeltaTime;

	if (m_BreathSpawnTimeAcc > m_BreathSpawnTime)
	{
		m_BreathSpawnTimeAcc = 0.f;

		Vector3 Pos = m_Mesh->GetSocketPos("Head2");

		CFlameEffect* Effect = m_Scene->CreateGameObject<CFlameEffect>("Flame"); // Scale늘려도 브레스가 어색하다면 추가로 활성, 비활성 Billboard를 추가하는것도 고려해봐야 할듯
		Effect->SetWorldPos(Pos);

		// 만약 Angle이 m_BreathTrackingAngle값을 벗어났다면 최대각도인 
		// m_BreathTrackingAngle값으로 브레스발사 방향을 고정. 

		// 현재 Angle이 m_BreathTrackingAngle보다 크면 이전브레스 각도로 발사.
		if (Angle >= m_BreathTrackingAngle || Angle <= -m_BreathTrackingAngle)
		{
			// 이전 Dir을 갱신하지않고 이전 Dir로 발사한다.
			Effect->Move(m_PrevBreathDir);
		}

		// 플레이어 방향으로 브레스 발사.
		else
		{
			Effect->Move(PlayerDir);

			m_PrevBreathDir = PlayerDir;
		}
	}
}

void CRathalos::CreateFireball()
{
	Vector3 Pos = m_Mesh->GetSocketPos("Head2");
	Vector3 PlayerPos = m_Scene->GetPlayerObject()->GetWorldPos();

	PlayerPos -= Pos;

	PlayerPos.Normalize();

	Vector3 Dir = PlayerPos;


	CFlameEffect* Effect = m_Scene->CreateGameObject<CFlameEffect>("Flame"); // Scale늘려도 브레스가 어색하다면 추가로 활성, 비활성 Billboard를 추가하는것도 고려해봐야 할듯
	Effect->SetWorldPos(Pos);
	Effect->Move(Dir, 50.f, 100.f);
	Effect->SetExplosive(true);
}

void CRathalos::WeaponOnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "PlayerAttack")
	{
		// 충돌체의 확률에 따라 Critical 모션으로 변경
		// 임의로 공격횟수에 따라 Critical여부를 체크.
		m_DamagedCount++;

		CriticalCheck();

		// 상태전환할 것 인지
		if (m_FSMRathalos->CheckCurrentState("Idle") || m_FSMRathalos->CheckCurrentState("Patrol"))
		{
			CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::FinalBossBattle);

			m_Mesh->GetAnimationInstance()->ChangeAnimation("Roaring");
		}
	}
}

void CRathalos::TailOnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "PlayerAttack")
	{
		m_TailDamagedCount++;

		if (m_TailDamagedCount >= 5)
		{
			if (!m_IsTailDestroyed)
			{
				m_IsTailDestroyed = true;

				// 일정량 데미지를 받았을경우 꼬리생성 및 제거.
				// 현재는 횟수만큼 받을경우 제거.
				m_Mesh->GetMaterial(4)->SetOpacity(0.f);

				CGameObject* Tail = m_Scene->CreateGameObject<CRathalosTail>("RathalosTail");
				Tail->GetRootComponent()->SetTransformState(Transform_State::Ground);

				Vector3 Pos = m_Mesh->GetSocketPos("Tail");
				Tail->SetWorldPos(Pos);
			}
		}
	}
}
void CRathalos::SpotOnCollisionBegin(const CollisionResult& result)
{
	CGameObject* Player = m_Scene->GetPlayerObject();

	if (result.Dest->GetGameObject() == m_Scene->GetPlayerObject())
	{
		m_PlayerDetected = true;
	}
}

void CRathalos::SpotOnCollisionEnd(const CollisionResult& result)
{
	CGameObject* Player = m_Scene->GetPlayerObject();

	if (result.Dest->GetGameObject() == m_Scene->GetPlayerObject())
	{
		m_PlayerDetectTimeAcc = 0.f;

		m_PlayerDetected = false;
	}
}

void CRathalos::SlidingOnCollisionBegin(const CollisionResult& result)
{ 
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		m_FieldObj = result.Dest->GetGameObject();
		m_IsFieldCollision = true;
		m_FieldBoxInfo = ((CColliderBox3D*)result.Dest)->GetInfo();

		++m_WayPointNumber;

		if (m_WayPointNumber >= 4)
		{
			m_WayPointNumber = 0;
		}

		Vector3 CurrentPos = GetWorldPos();
		Vector3 WayPointPos = m_PatrolPos[m_WayPointNumber];

		CurrentPos.y = 0.f;
		WayPointPos.y = 0.f;

		Vector3 MovePointDir = WayPointPos - CurrentPos;
		MovePointDir.Normalize();

		// 몬스터 전방벡터와 Up 벡터 외적으로 우향벡터 생성
		Vector3 CurrentRightDir = m_Dir.Cross(Vector3().Axis[AXIS::AXIS_Y]);

		bool	Left = false;

		//우향벡터와 플레이어 벡터의 내적.
		if (CurrentRightDir.Dot(MovePointDir) > 0)
		{
			Left = true;
		}

		float	Angle = m_Dir.Dot(MovePointDir);

		Angle = RadianToDegree(acosf(Angle));

		// 좌측일경우, 음각으로 회전.
		if (Left)
		{
			Angle *= -1.f;
		}

		AddRelativeRotationY(Angle);

		m_Dir = MovePointDir;
	}
}

void CRathalos::SlidingOnCollisionEnd(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		m_FieldObj = nullptr;
		m_IsFieldCollision = false;
	}
}

void CRathalos::SetTargetCam()
{
	CTargetingCamera* RotCam = m_Scene->CreateGameObject<CTargetingCamera>("RotCam");

	Vector3 CurDir = GetRelativeAxis(AXIS::AXIS_Z) * -1.f;

	Vector3 Pos = GetWorldPos() + (CurDir * 40.f);
	RotCam->SetCameraFixedPos(Pos);
	RotCam->SetCameraDistance(25.f);
	RotCam->SetLookAtTarget(this, "Head1");
}

void CRathalos::SetMernos()
{
	Vector3 PlayerPos = CSceneManager::GetInst()->GetPlayerObject()->GetWorldPos();
	PlayerPos.y += 15.f;

	Vector3 PlayerDir = CSceneManager::GetInst()->GetPlayerObject()->GetWorldAxis(AXIS::AXIS_Z);

	CMernos* Mernos = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMernos>("Mernos");
	Mernos->SetWorldPos(PlayerPos + PlayerDir * 30.f);

	CObjectManager::GetInst()->SaveCheckToPointFunc(Check_Type::LoadingToStage);
}

void CRathalos::SetDestroyCarvingCollider()
{
	m_Mesh->DeleteChild(m_CarvingCollider);

	m_CarvingCollider->Enable(false);

	m_Mesh->SetLayerName("Effect");

	CEventManager::GetInst()->SetStageType(Stage_Type::Town);
}
