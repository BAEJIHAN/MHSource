
#include "Anjanath.h"
#include "AnjanathTail.h"
#include "AnjanathAnimation.h"
#include "FlameEffect.h"
#include "BurnedDecal.h"
#include "Player.h"
#include "TargetingCamera.h"
#include "EventManager.h"
#include "HDR.h"
#include "Mernos.h"
#include "ObjectManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Collision/Collision.h"
#include "../ClientManager3D.h"
#include "../Scene/MainSceneMode.h"

CAnjanath::CAnjanath() :
	m_PatrolPosArrived(false),
	m_MoveSpeed(10.f),
	m_Move(false),
	m_LeftFoot(true),
	m_RightFoot(true),
	m_Rotate(0),
	m_RotateSpeed(90.f),
	m_PatrolDist(0.f),
	m_FadeOpacity(1.f),
	m_WayPointNumber(0),
	m_PlayerDetectTime(5.f),
	m_PlayerDetectTimeAcc(0.f),
	m_PlayerDist(40.f),
	m_Dir(0.f, 0.f, -1.f),
	m_DamagedCount(0),
	m_TailDamagedCount(0),
	m_TotalDamaged(0.f),
	m_DamageTime(1.f),
	m_DamageTimeAcc(1.f),
	m_DeadTimeAcc(0.f),
	m_BreathStack(0),
	m_Breath(false),
	m_BreathSpawnTime(0.1f),
	m_BreathSpawnTimeAcc(0.f),
	m_BreathTrackingAngle(30.f),
	m_IsChargeAttacking(false),
	m_IsBiteAttacking(false),
	m_IsBreathAttacking(false),
	m_IsTailDestroyed(false),
	m_PlayerDetected(false),
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
	SetTypeID<CAnjanath>();
}

CAnjanath::CAnjanath(const CAnjanath& obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("AnjanathMesh");
}

CAnjanath::~CAnjanath()
{
	SAFE_DELETE(m_FSMAnjanath);
}

void CAnjanath::SetDamage(float Damage)
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

void CAnjanath::Start()
{
	CGameObject::Start();

	Vector3 CurrentPos = GetWorldPos();

	m_PatrolPos[0] = Vector3(CurrentPos.x - 10.f, 0.f, CurrentPos.z + 10.f);
	m_PatrolPos[1] = Vector3(CurrentPos.x + 10.f, 0.f, CurrentPos.z + 10.f);
	m_PatrolPos[2] = Vector3(CurrentPos.x + 10.f, 0.f, CurrentPos.z - 10.f);
	m_PatrolPos[3] = Vector3(CurrentPos.x - 10.f, 0.f, CurrentPos.z - 10.f);

	m_FSMAnjanath->ChangeState("Patrol");
}

bool CAnjanath::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_FSMAnjanath = new FSM<CAnjanath>;

	m_FSMAnjanath->CreateState("Idle", this, &CAnjanath::IdleStay, &CAnjanath::IdleStart, &CAnjanath::IdleEnd);
	m_FSMAnjanath->CreateState("Patrol", this, &CAnjanath::NormaPatrolStay, &CAnjanath::NormaPatrolStart, &CAnjanath::NormaPatrolEnd);
	m_FSMAnjanath->CreateState("PlayerDetected", this, &CAnjanath::DetectStay, &CAnjanath::DetectStart, &CAnjanath::DetectEnd);
	m_FSMAnjanath->CreateState("PlayerTracking", this, &CAnjanath::TrackingStay, &CAnjanath::TrackingStart, &CAnjanath::TrackingEnd);
	m_FSMAnjanath->CreateState("Attack", this, &CAnjanath::AttackStay, &CAnjanath::AttackStart, &CAnjanath::AttackEnd);
	m_FSMAnjanath->CreateState("Groggy", this, &CAnjanath::GroggyStay, &CAnjanath::GroggyStart, &CAnjanath::GroggyEnd);
	m_FSMAnjanath->CreateState("Dead", this, &CAnjanath::DeadStay, &CAnjanath::DeadStart, &CAnjanath::DeadEnd);

	m_Mesh = CreateComponent<CAnimationMeshComponent>("AnjanathMesh");
	m_Mesh->SetMesh("AnjanathMesh");
	m_Mesh->CreateAnimationInstance<CAnjanathAnimation>();

	m_HeadLight = CreateComponent<CLightComponent>("AnjanathPointLight");
	m_HeadLight->SetInheritRotY(true);
	m_HeadLight->SetLightType(Light_Type::Point);
	m_HeadLight->SetDistance(50.f);
	m_HeadLight->SetAtt3(0.01f);
	m_HeadLight->SetColor(Vector4(1.f, 0.5f, 0.f, 1.f));
	m_HeadLight->Enable(false);

	m_BiteCollider = CreateComponent<CColliderBox3D>("BiteCollider");
	m_ChargeCollider = CreateComponent<CColliderBox3D>("ChargeCollider");
	m_CarvingCollider = CreateComponent<CColliderBox3D>("ColliderCarving");
	m_SpotCollider = CreateComponent<CColliderBox3D>("ColliderBox");
	m_RightBackLegCollider = CreateComponent<CColliderBox3D>("RightBackLegCollider");
	m_LeftBackLegCollider = CreateComponent<CColliderBox3D>("LeftBackLegCollider");
	m_RightFrontLegCollider = CreateComponent<CColliderBox3D>("RightFrontLegCollider");
	m_LeftFrontLegCollider = CreateComponent<CColliderBox3D>("LeftFrontLegCollider");
	m_RightFootCollider = CreateComponent<CColliderBox3D>("RightFootCollider");
	m_LeftFootCollider = CreateComponent<CColliderBox3D>("LeftFootCollider");
	m_Head1Collider = CreateComponent<CColliderBox3D>("Head1Collider");
	m_Head2Collider = CreateComponent<CColliderBox3D>("Head2Collider");
	m_BodyCollider = CreateComponent<CColliderBox3D>("BodyCollider");
	m_TailWithBodyCollider = CreateComponent<CColliderBox3D>("TailWithBodyCollider");
	m_TailCollider = CreateComponent<CColliderBox3D>("TailCollider");
	m_SlidingCollider = CreateComponent<CColliderBox3D>("ColliderSliding");


	m_RightBackLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftBackLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_RightFrontLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftFrontLegCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_RightFootCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_LeftFootCollider->Set3DExtent(2.f, 2.f, 2.f);
	m_Head1Collider->Set3DExtent(2.f, 2.f, 2.f);
	m_Head2Collider->Set3DExtent(2.f, 2.f, 2.f);
	m_BodyCollider->Set3DExtent(5.f, 8.f, 3.f);
	m_TailWithBodyCollider->Set3DExtent(5.f, 4.f, 4.f);
	m_TailCollider->Set3DExtent(4.f, 5.f, 4.f);
	m_SpotCollider->Set3DExtent(80.f, 80.f, 30.f);
	m_CarvingCollider->Set3DExtent(10.f, 10.f, 10.f);
	m_BiteCollider->Set3DExtent(6.f, 6.f, 6.f);
	m_ChargeCollider->Set3DExtent(8.f, 8.f, 8.f);
	m_SlidingCollider->Set3DExtent(4.f, 10.f, 4.f);

	m_SpotCollider->SetOffset(0.f, 5.f, 0.f);
	m_CarvingCollider->SetOffset(0.f, 5.f, 0.f);
	m_BiteCollider->SetOffset(0.f, 3.f, 5.f);
	m_ChargeCollider->SetOffset(0.f, 8.f, 6.f);
	m_SlidingCollider->SetOffset(0.f, 0.f, 4.f);

	m_RightBackLegCollider->SetCollisionProfile("Monster");
	m_LeftBackLegCollider->SetCollisionProfile("Monster");
	m_RightFrontLegCollider->SetCollisionProfile("Monster");
	m_LeftFrontLegCollider->SetCollisionProfile("Monster");
	m_RightFootCollider->SetCollisionProfile("Monster");
	m_LeftFootCollider->SetCollisionProfile("Monster");
	m_Head1Collider->SetCollisionProfile("Monster");
	m_Head2Collider->SetCollisionProfile("Monster");
	m_BodyCollider->SetCollisionProfile("Monster");
	m_TailWithBodyCollider->SetCollisionProfile("Monster");
	m_TailCollider->SetCollisionProfile("Monster");
	m_BiteCollider->SetCollisionProfile("MonsterAttack");
	m_ChargeCollider->SetCollisionProfile("MonsterAttack");
	m_SlidingCollider->SetCollisionProfile("MonsterSliding");
	m_SpotCollider->SetCollisionProfile("MonsterSpot");
	m_CarvingCollider->SetCollisionProfile("Carving");

	m_RightBackLegCollider->SetInheritRotY(true);
	m_LeftBackLegCollider->SetInheritRotY(true);
	m_RightFrontLegCollider->SetInheritRotY(true);
	m_LeftFrontLegCollider->SetInheritRotY(true);
	m_RightFootCollider->SetInheritRotY(true);
	m_LeftFootCollider->SetInheritRotY(true);
	m_Head1Collider->SetInheritRotY(true);
	m_Head2Collider->SetInheritRotY(true);
	m_BodyCollider->SetInheritRotY(true);
	m_TailWithBodyCollider->SetInheritRotY(true);
	m_TailCollider->SetInheritRotY(true);
	m_SpotCollider->SetInheritRotY(true);
	m_CarvingCollider->SetInheritRotY(true);
	m_BiteCollider->SetInheritRotY(true);
	m_ChargeCollider->SetInheritRotY(true);

	m_RightBackLegCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_LeftBackLegCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_RightFrontLegCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_LeftFrontLegCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_RightFootCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_LeftFootCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_Head1Collider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_Head2Collider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_BodyCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_TailWithBodyCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_TailWithBodyCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::TailOnCollisionBegin);
	m_TailCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::WeaponOnCollisionBegin);
	m_TailCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::TailOnCollisionBegin);

	m_SpotCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::SpotOnCollisionBegin);
	m_SpotCollider->AddCollisionCallback(Collision_State::End, this, &CAnjanath::SpotOnCollisionEnd);
	m_SlidingCollider->AddCollisionCallback(Collision_State::Begin, this, &CAnjanath::SlidingOnCollisionBegin);
	m_SlidingCollider->AddCollisionCallback(Collision_State::End, this, &CAnjanath::SlidingOnCollisionEnd);


	m_CarvingCollider->Enable(false);
	m_BiteCollider->Enable(false);
	m_ChargeCollider->Enable(false);

	m_Mesh->AddChild(m_BiteCollider, "Head1");
	m_Mesh->AddChild(m_CarvingCollider, "Body");
	m_Mesh->AddChild(m_ChargeCollider);
	m_Mesh->AddChild(m_SpotCollider);
	m_Mesh->AddChild(m_SlidingCollider);
	m_Mesh->AddChild(m_HeadLight);

	m_Mesh->AddChild(m_RightBackLegCollider, "RightBackLeg");
	m_Mesh->AddChild(m_LeftBackLegCollider, "LeftBackLeg");
	m_Mesh->AddChild(m_RightFrontLegCollider, "RightFrontLeg");
	m_Mesh->AddChild(m_LeftFrontLegCollider, "LeftFrontLeg");
	m_Mesh->AddChild(m_RightFootCollider, "RightBackFoot");
	m_Mesh->AddChild(m_LeftFootCollider, "LeftBackFoot");
	m_Mesh->AddChild(m_Head1Collider, "Head1");
	m_Mesh->AddChild(m_Head2Collider, "Head2");
	m_Mesh->AddChild(m_BodyCollider, "Body");
	m_Mesh->AddChild(m_TailWithBodyCollider, "TailWithBody");
	m_Mesh->AddChild(m_TailCollider, "Tail");

	m_Mesh->SetRelativeScale(0.03f, 0.03f, 0.03f);
	m_Mesh->SetRelativeRotation(Vector3(-90.f, 0.f, 180.f));

	size_t Size = m_Mesh->GetMaterialSlotCount();


	for (size_t i = 0; i < Size; ++i)
	{
		m_Mesh->GetMaterial((int)i)->SetAmbientColor(Vector4().White);
	}

	CEventManager::GetInst()->AddEventCallback<CAnjanath>("BossDead", this, &CAnjanath::SetTargetCam);
	CEventManager::GetInst()->AddEventCallback<CAnjanath>("QuestAcept", this, &CAnjanath::SetMernos);

	SetAnimNotify();

	return true;
}

void CAnjanath::Update(float DeltaTime)
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

	m_FSMAnjanath->Update();

	Move(DeltaTime);

	Rotate(DeltaTime);

	FootStepCheck();

	if (m_IsFieldCollision)
	{
		FieldCollision(DeltaTime);
	}
}

void CAnjanath::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CAnjanath* CAnjanath::Clone()
{
	return new CAnjanath(*this);
}


void CAnjanath::IdleStart()
{
}


// 아무것도 안하는 Idle
void CAnjanath::IdleStay()
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

void CAnjanath::IdleEnd()
{
}

void CAnjanath::NormaPatrolStart()
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
}

void CAnjanath::NormaPatrolStay()
{
	DeadCheck();
	
	m_WaitTimeAcc += m_DeltaTime;

	if (m_WaitTimeAcc > m_WaitTime)
	{
		m_ReadyToMove = true;
	}

	if (m_ReadyToMove)
	{
		if (m_DamagedCount <= 0)
		{
			Vector3 Pos = GetWorldPos();

			m_PatrolDist = Pos.Distance(m_PatrolPos[m_WayPointNumber]);

			// 5m 이내일 경우
			if (m_PatrolDist < 5.f && !m_PatrolPosArrived)
			{
				// 도착표시.
				m_PatrolPosArrived = true;

				// WayPoint Index변경
				m_WayPointNumber++;

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

			else if (m_PatrolDist >= 5.f)
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

				m_FSMAnjanath->ChangeState("PlayerDetected");
			}
		}
	}
}

void CAnjanath::NormaPatrolEnd()
{
	m_Move = false;
}

void CAnjanath::DetectStart()
{
	if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("Roaring"))
	{
		CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::BossBattle);
		
		m_Mesh->GetAnimationInstance()->ChangeAnimation("Roaring");
	}
}

void CAnjanath::DetectStay()
{
	DeadCheck();

	if (m_PlayerDetected && m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("AgressiveIdle"))
	{
		m_FSMAnjanath->ChangeState("PlayerTracking");
	}
}

void CAnjanath::DetectEnd()
{
}

void CAnjanath::TrackingStart()
{
	CalcAngle();
}

void CAnjanath::TrackingStay()
{
	DeadCheck();

	if (m_Rotate == 0)
	{
		if (m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("AgressiveIdle"))
		{
			m_FSMAnjanath->ChangeState("Attack");
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

void CAnjanath::TrackingEnd()
{
}

void CAnjanath::AttackStart()
{
	m_MoveSpeed = 40.f;

	m_BreathStack++;

	if (m_PlayerDist < 40.f)
	{
		m_Mesh->GetAnimationInstance()->ChangeAnimation("TripleBiteStart");
	}

	else
	{
		if (m_BreathStack >= 5 && m_HP < (m_HPMax / 2.f))
		{
			m_BreathStack = 0;

			m_Mesh->GetAnimationInstance()->ChangeAnimation("BreathReady");
		}

		else
		{
			m_Mesh->GetAnimationInstance()->ChangeAnimation("AttackDashStart");
		}
	}
}

void CAnjanath::AttackStay()
{
	DeadCheck();

	CreateFlame();
}

void CAnjanath::AttackEnd()
{
}

void CAnjanath::GroggyStart()
{
}

void CAnjanath::GroggyStay()
{
}

void CAnjanath::GroggyEnd()
{
}

void CAnjanath::DeadStart()
{
	MoveEnd();
	RotateEnd();
	BreathEnd();
	DisableBiteAttack();
	DisableChargeAttack();

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

void CAnjanath::DeadStay()
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
		m_FadeOpacity -= (float)(m_DeltaTime * 0.1f);

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

void CAnjanath::DeadEnd()
{
}

void CAnjanath::SetAnimNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("NormalMoveStart", this, &CAnjanath::NormalMoveStartEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("NormalMoveEnd", this, &CAnjanath::NormalMoveEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("NormalMoveStartToLeft", this, &CAnjanath::NormalTurnLeftStartEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("NormalTurnLeft", this, &CAnjanath::NormalTurnLeftEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("NormalMoveStartToRight", this, &CAnjanath::NormalTurnRightStartEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("NormalTurnRight", this, &CAnjanath::NormalTurnRightEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("NormalIdle", this, &CAnjanath::IdleVoiceNotify);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("AgressiveTurnLeft", this, &CAnjanath::AgressiveTurnLeftEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("AgressiveTurnRight", this, &CAnjanath::AgressiveTurnRightEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("AgressiveTurnEnd", this, &CAnjanath::AgressiveTurnEndFunction);


	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("TripleBiteStart", this, &CAnjanath::TripleBiteStart);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("TripleBite1", this, &CAnjanath::TripleBiteCombo1);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("TripleBite2", this, &CAnjanath::TripleBiteCombo2);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("TripleBiteEndV2", this, &CAnjanath::TripleBiteEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("Roaring", this, &CAnjanath::RoarEnd);


	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("AttackDashStart", this, &CAnjanath::AttackDashStartEndFunction);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("AttackDashEnd", this, &CAnjanath::AttackDashEndFunction);


	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("CriticalDamaged", this, &CAnjanath::CriticalDamagedEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("BreathReady", this, &CAnjanath::BreathReadyEnd);
	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("BreathAttack", this, &CAnjanath::BreathAttackEnd);

	m_Mesh->GetAnimationInstance()->SetEndFunction<CAnjanath>("Dead", this, &CAnjanath::DeadEndNotify);



	/// Adding Notify
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("AttackDashStart", "ChargeVoice", 1, this, &CAnjanath::ChargeAttackVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("AttackDashStart", "MoveStart", 5, this, &CAnjanath::MoveStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("AttackDashStart", "EnableChargeAttack", 5, this, &CAnjanath::EnableChargeAttack);

	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("AttackDashEnd", "DisableChargeAttack", 1, this, &CAnjanath::DisableChargeAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("AttackDashEnd", "MoveEnd", 1, this, &CAnjanath::MoveEnd);

	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("Roaring", "RoarStart", 1, this, &CAnjanath::RoarStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("Roaring", "MeetRoar", 3, this, &CAnjanath::RoaringMeetVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("Roaring", "RoarCheckEnd", 49, this, &CAnjanath::RoaringCheckEndNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("Roaring", "RoarBlurEnd", 149, this, &CAnjanath::RoarBlurEnd);

	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteStart", "BiteReadyVoice", 15, this, &CAnjanath::BiteAttackStartVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteStart", "MoveStart", 42, this, &CAnjanath::MoveStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteStart", "CreateAttack", 40, this, &CAnjanath::EnableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteStart", "BiteVoice", 40, this, &CAnjanath::BiteAttackVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteStart", "DeleteAttack", 52, this, &CAnjanath::DisableBiteAttack);

	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBite1", "MoveEnd", 10, this, &CAnjanath::MoveEnd);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBite1", "MoveStart", 40, this, &CAnjanath::MoveStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBite1", "CreateAttack", 50, this, &CAnjanath::EnableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBite1", "BiteVoice", 50, this, &CAnjanath::BiteAttackVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBite1", "DeleteAttack", 67, this, &CAnjanath::DisableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBite1", "MoveEnd", 70, this, &CAnjanath::MoveEnd);

	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "MoveStart", 0, this, &CAnjanath::MoveStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "CreateAttack", 15, this, &CAnjanath::EnableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "BiteVoice", 15, this, &CAnjanath::BiteAttackVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "DeleteAttack", 33, this, &CAnjanath::DisableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "MoveEnd", 37, this, &CAnjanath::MoveEnd);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "CreateAttack", 80, this, &CAnjanath::EnableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "MoveStart", 84, this, &CAnjanath::MoveStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "BiteVoice", 80, this, &CAnjanath::BiteAttackVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "MoveEnd", 94, this, &CAnjanath::MoveEnd);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "DeleteAttack", 94, this, &CAnjanath::DisableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "MoveStart", 152, this, &CAnjanath::MoveStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "CreateAttack", 155, this, &CAnjanath::EnableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "BiteVoice", 155, this, &CAnjanath::BiteAttackVoiceNotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "DeleteAttack", 175, this, &CAnjanath::DisableBiteAttack);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "MoveEnd", 175, this, &CAnjanath::MoveEnd);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("TripleBiteEndV2", "BiteEndRoarVoice", 198, this, &CAnjanath::BiteEndRoarVoiceNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("CriticalDamaged", "CriticalState", 1, this, &CAnjanath::CriticalDamagedStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("CriticalDamaged", "CriticalVoice", 2, this, &CAnjanath::CriticalVoiceNotify);

	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("BreathReady", "BreathVoice", 15, this, &CAnjanath::BreathReadyStart);

	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("BreathAttack", "BreathSE", 40, this, &CAnjanath::BreathSENotify);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("BreathAttack", "BreathStart", 40, this, &CAnjanath::BreathStart);
	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("BreathAttack", "BreathEnd", 140, this, &CAnjanath::BreathEnd);

	m_Mesh->GetAnimationInstance()->AddNotify<CAnjanath>("Dead", "DeadVoice", 1, this, &CAnjanath::DeadVoiceNotify);

}

void CAnjanath::NormalIdleEnd()
{
}

void CAnjanath::NormalMoveEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalIdle");
}

void CAnjanath::NormalMoveStartEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CAnjanath::NormalTurnLeftStartEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CAnjanath::NormalTurnLeftEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CAnjanath::NormalTurnRightStartEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CAnjanath::NormalTurnRightEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("NormalMoveLoop");
}

void CAnjanath::AgressiveTurnLeftEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveTurnEnd");

	RotateEnd();
}

void CAnjanath::AgressiveTurnRightEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveTurnEnd");

	RotateEnd();
}

void CAnjanath::AgressiveTurnEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveIdle");
}

void CAnjanath::AttackDashStartEndFunction()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("AttackDashEnd");
}

void CAnjanath::AttackDashEndFunction()
{
	m_FSMAnjanath->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveIdle");

	MoveEnd();
}

void CAnjanath::RoarStart()
{
	m_Move = false;
}

void CAnjanath::RoarEnd()
{
	m_FSMAnjanath->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveIdle");
}

void CAnjanath::RoarBlurEnd()
{
	CHDR::GetInst()->SetBlurEnable(false);
}

void CAnjanath::MoveSetNotify()
{
	// 
}

void CAnjanath::MoveLoopRotationCheck()
{
}

void CAnjanath::TripleBiteStart()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("TripleBite1");
}

void CAnjanath::TripleBiteCombo1()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("TripleBite2");
}

void CAnjanath::TripleBiteCombo2()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("TripleBiteEndV2");
}

void CAnjanath::TripleBiteEnd()
{
	m_FSMAnjanath->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveIdle");
}

void CAnjanath::CriticalDamagedStart()
{
	BreathEnd();
	MoveEnd();
	RotateEnd();
	DisableBiteAttack();
	DisableChargeAttack();

	m_Dir = m_Mesh->GetRelativeAxis(AXIS::AXIS_Z);
	m_Dir *= -1.f;
}

void CAnjanath::CriticalDamagedEnd()
{
	m_FSMAnjanath->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveIdle");
}

void CAnjanath::BreathReadyEnd()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BreathAttack");
}

void CAnjanath::BreathAttackEnd()
{
	m_FSMAnjanath->ChangeState("PlayerTracking");

	m_Mesh->GetAnimationInstance()->ChangeAnimation("AgressiveIdle");
}

void CAnjanath::EnableBiteAttack()
{
	m_BiteCollider->Enable(true);

	m_IsBiteAttacking = true;
}

void CAnjanath::DisableBiteAttack()
{
	m_BiteCollider->Enable(false);

	m_IsBiteAttacking = false;
}

void CAnjanath::EnableChargeAttack()
{
	m_ChargeCollider->Enable(true);

	m_IsChargeAttacking = true;
}

void CAnjanath::DisableChargeAttack()
{
	m_ChargeCollider->Enable(false);

	m_IsChargeAttacking = false;
}

void CAnjanath::BreathReadyStart()
{
	int RandVal = rand() % 2;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("AnjanathBreathReady1");
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("AnjanathBreathReady2");
		break;
	}
}

void CAnjanath::BreathSENotify()
{
	m_Scene->GetResource()->SoundPlay("AnjanathBreathSE");
}

void CAnjanath::IdleVoiceNotify()
{
	int RandVal1 = rand() % 3;
	int RandVal2 = rand() % 10;

	if (RandVal2 < 3)
	{
		switch (RandVal1)
		{
		case 0:
			m_Scene->GetResource()->SoundPlay("AnjanathIdle1", this);
			break;
		case 1:
			m_Scene->GetResource()->SoundPlay("AnjanathIdle2", this);
			break;
		case 2:
			m_Scene->GetResource()->SoundPlay("AnjanathIdle3", this);
			break;
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
}

void CAnjanath::RoaringMeetVoiceNotify()
{
	Vector3 PlayerPos = m_Scene->GetPlayerObject()->GetWorldPos();
	Vector3 CurPos = GetWorldPos();

	if (PlayerPos.Distance(CurPos) < 100.f)
	{
		CHDR::GetInst()->SetBlurEnable(true);
		m_IsRoaring = true;
	}

	m_Scene->GetResource()->SoundPlay("AnjanathMeetRoaring");

	CEventManager::GetInst()->CallEvent("PlayerMonsterContant");
}

void CAnjanath::RoaringCheckEndNotify()
{
	m_IsRoaring = false;
}

void CAnjanath::RoaringVoiceNotify()
{
	int RandVal = rand() % 2;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("AnjanathRoaring1", this);
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("AnjanathRoaring2", this);
		break;
	}
}

void CAnjanath::BiteAttackStartVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("AnjanathBiteReady", this);
}

void CAnjanath::BiteAttackVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("AnjanathBiteAttack1", this);
}

void CAnjanath::BiteEndRoarVoiceNotify()
{
	// EndRoar -> Attack2 -> AnjanathRoaring1으로 수정함.
	m_Scene->GetResource()->SoundPlay("AnjanathRoaring1", this);
}

void CAnjanath::ChargeAttackVoiceNotify()
{
	int RandVal = rand() % 2;

	switch (RandVal)
	{
	case 0:
		m_Scene->GetResource()->SoundPlay("AnjanathChargeAttack1", this);
		break;
	case 1:
		m_Scene->GetResource()->SoundPlay("AnjanathChargeAttack2", this);
		break;
	}
}

void CAnjanath::CriticalVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("AnjanathCriticalDamage", this);
}

void CAnjanath::DeadVoiceNotify()
{
	m_Scene->GetResource()->SoundPlay("AnjanathDead");
}

void CAnjanath::DeadEndNotify()
{
	CEventManager::GetInst()->CallEvent("BossDeadEnd");
}

void CAnjanath::MoveStart()
{
	m_Move = true;
}

void CAnjanath::MoveEnd()
{
	m_Move = false;
}

void CAnjanath::RotateLeft()
{
	m_Rotate = -1;
}

void CAnjanath::RotateRight()
{
	m_Rotate = 1;
}

void CAnjanath::RotateEnd()
{
	m_Rotate = 0;
}

void CAnjanath::BreathStart()
{
	m_Breath = true;

	m_HeadLight->Enable(true);

	Vector3 Pos = m_Mesh->GetSocketPos("Head1");
	Pos.y -= 3.f;

	Vector3 CurDir = GetRelativeAxis(AXIS::AXIS_Z) * -1.f;
	Pos += (CurDir * 5.f);

	m_HeadLight->SetWorldPos(Pos);
}

void CAnjanath::BreathEnd()
{
	m_Breath = false;

	m_HeadLight->Enable(false);
}

void CAnjanath::Rotate(float DeltaTime)
{
	// 0일 경우, 증감자체를 하지않음.
	if (m_Rotate == 0)
	{
		return;
	}

	else
	{
		float AnimPlayTime = m_Mesh->GetAnimationInstance()->GetCurrentAnimation()->GetPlayTime();

		m_RotateSpeed = m_TargetRotateY / AnimPlayTime;

		AddRelativeRotationY(m_RotateSpeed * DeltaTime);
	}
}

void CAnjanath::Move(float DeltaTime)
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

void CAnjanath::FootStepCheck()
{
	// 죽었을경우 무시.
	if (m_Dead)
		return;

	float LeftFootY = m_Mesh->GetSocketPos("LeftBackFoot").y;
	float RightFootY = m_Mesh->GetSocketPos("RightBackFoot").y;

	// Normal Idle 상태일때,
	if (m_FSMAnjanath->CheckCurrentState("Idle") || m_FSMAnjanath->CheckCurrentState("Patrol"))
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
					m_Scene->GetResource()->SoundPlay("AnjanathSlowStep1SE", this);
					break;
				case 1:
					m_Scene->GetResource()->SoundPlay("AnjanathSlowStep2SE", this);
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
					m_Scene->GetResource()->SoundPlay("AnjanathSlowStep1SE", this);
					break;
				case 1:
					m_Scene->GetResource()->SoundPlay("AnjanathSlowStep2SE", this);
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
				int RandVal = rand() % 3;

				switch (RandVal)
				{
				case 0:
					m_Scene->GetResource()->SoundPlay("AnjanathFastStep1SE", this);
					break;
				case 1:
					m_Scene->GetResource()->SoundPlay("AnjanathFastStep2SE", this);
					break;
				case 2:
					m_Scene->GetResource()->SoundPlay("AnjanathFastStep3SE", this);
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
				int RandVal = rand() % 3;

				switch (RandVal)
				{
				case 0:
					m_Scene->GetResource()->SoundPlay("AnjanathFastStep1SE", this);
					break;
				case 1:
					m_Scene->GetResource()->SoundPlay("AnjanathFastStep2SE", this);
					break;
				case 2:
					m_Scene->GetResource()->SoundPlay("AnjanathFastStep3SE", this);
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

void CAnjanath::DeadCheck()
{
	if (m_Dead)
	{
		m_FSMAnjanath->ChangeState("Dead");
	}
}

void CAnjanath::CriticalCheck()
{
	if (m_TotalDamaged > 100.f)
	{
		m_TotalDamaged = 0.f;

		if (!m_Mesh->GetAnimationInstance()->CheckCurrentAnimation("CriticalDamaged"))
		{
			CriticalDamagedStart();

			m_Mesh->GetAnimationInstance()->ChangeAnimation("CriticalDamaged");
		}
	}
}

void CAnjanath::FieldCollision(float DeltaTime)
{
	Vector3 Dir = Vector3(m_FieldObj->GetWorldPos() - GetWorldPos());
	Dir.Normalize();
	Dir *= -1;

	AddWorldPos(Dir * m_MoveSpeed * DeltaTime);
}

void CAnjanath::AttackPattern(bool AngleIn, bool RangeIn)
{
}

bool CAnjanath::CalcAngle()
{
	// 플레이어간의 위치.
	Vector3 PlayerPos = m_Scene->GetPlayerObject()->GetWorldPos();
	Vector3 WorldPos = GetWorldPos();

	m_PlayerDist = PlayerPos.Distance(WorldPos);

	// (안자냐프 --> Player) Dir 생성
	Vector3 PlayerDir = PlayerPos - WorldPos;
	PlayerDir.y = 0.f;

	// 현재 몬스터의 전방Dir 생성
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

void CAnjanath::CreateFlame()
{
	if (!m_Breath)
	{
		m_BreathSpawnTimeAcc = 0.f;

		m_PrevBreathDir = m_Dir;

		return;
	}

	// Player <--> 안자냐프 각도 계산 시작
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

		CFlameEffect* Effect = m_Scene->CreateGameObject<CFlameEffect>("Flame");
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

void CAnjanath::WeaponOnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "PlayerAttack")
	{
		//충돌체의 확률에 따라 Critical 모션으로 변경
		//임의로 공격횟수에 따라 Critical여부를 체크.
		m_DamagedCount++;

		CriticalCheck();

		// 상태전환할 것 인지
		if (m_FSMAnjanath->CheckCurrentState("Idle") || m_FSMAnjanath->CheckCurrentState("Patrol"))
		{
			CClientManager3D::GetInst()->PlayBattleBGM(BGM_Type::BossBattle);

			m_Mesh->GetAnimationInstance()->ChangeAnimation("Roaring");
		}
	}
}

void CAnjanath::TailOnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "PlayerAttack")
	{
		bool TailDestroyed = false;

		m_TailDamagedCount++;

		if (m_TailDamagedCount >= 5)
		{
			if (!m_IsTailDestroyed)
			{
				m_IsTailDestroyed = true;

				m_Mesh->GetAnimationInstance()->ChangeAnimation("CriticalDamaged");

				// 일정량 데미지를 받았을경우 꼬리생성 및 제거.
				// 현재는 횟수만큼 받을경우 제거.
				m_Mesh->GetMaterial(2)->SetOpacity(0.f);	// 꼬리 털
				m_Mesh->GetMaterial(3)->SetOpacity(0.f);	// 꼬리 털
				m_Mesh->GetMaterial(4)->SetOpacity(0.f);	// 꼬리 털 
				m_Mesh->GetMaterial(5)->SetOpacity(0.f);	// 꼬리 털
				m_Mesh->GetMaterial(6)->SetOpacity(0.f);	// 꼬리 털
				m_Mesh->GetMaterial(19)->SetOpacity(0.f);	// 꼬리 털
				m_Mesh->GetMaterial(20)->SetOpacity(0.f);	// 꼬리
				m_Mesh->GetMaterial(21)->SetOpacity(0.f);	// 꼬리

				CGameObject* Tail = m_Scene->CreateGameObject<CAnjanathTail>("AnjanathTail");
				Tail->GetRootComponent()->SetTransformState(Transform_State::Ground);

				Vector3 Pos = m_Mesh->GetSocketPos("Tail");
				Tail->SetWorldPos(Pos);
			}
		}
	}
}

void CAnjanath::SpotOnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetGameObject() == m_Scene->GetPlayerObject())
	{
		m_PlayerDetected = true;
	}
}

void CAnjanath::SpotOnCollisionEnd(const CollisionResult& result)
{
	if (result.Dest->GetGameObject() == m_Scene->GetPlayerObject())
	{
		m_PlayerDetectTimeAcc = 0.f;

		m_PlayerDetected = false;
	}
}

void CAnjanath::SlidingOnCollisionBegin(const CollisionResult& result)
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

void CAnjanath::SlidingOnCollisionEnd(const CollisionResult& result)
{
	if (result.Dest->GetCollisionProfile()->Name == "FieldObj")
	{
		m_FieldObj = nullptr;
		m_IsFieldCollision = false;
	}
}

void CAnjanath::SetTargetCam()
{
	CTargetingCamera* RotCam = m_Scene->CreateGameObject<CTargetingCamera>("RotCam");

	Vector3 CurDir = GetRelativeAxis(AXIS::AXIS_Z) * -1.f;

	Vector3 Pos = GetWorldPos() + (CurDir * 40.f);
	RotCam->SetCameraFixedPos(Pos);
	RotCam->SetCameraDistance(65.f);
	RotCam->SetLookAtTarget(this, "Head1");
}

void CAnjanath::SetMernos()
{
	Vector3 PlayerPos = CSceneManager::GetInst()->GetPlayerObject()->GetWorldPos();
	PlayerPos.y += 15.f;

	Vector3 PlayerDir = CSceneManager::GetInst()->GetPlayerObject()->GetWorldAxis(AXIS::AXIS_Z);

	CMernos* Mernos = CSceneManager::GetInst()->GetScene()->CreateGameObject<CMernos>("Mernos");
	Mernos->SetWorldPos(PlayerPos + PlayerDir * 30.f);

	CObjectManager::GetInst()->SaveCheckToPointFunc(Check_Type::LoadingToStage);
}

void CAnjanath::SetDestroyCarvingCollider()
{
	m_Mesh->DeleteChild(m_CarvingCollider);

	m_CarvingCollider->Enable(false);

	m_Mesh->SetLayerName("Effect");

	CEventManager::GetInst()->SetStageType(Stage_Type::Town);
}
