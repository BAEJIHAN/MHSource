
#include "DragonArrow.h"
#include "PlayerAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/Animation/Skeleton.h"
#include "Input.h"
#include "../Object/Player.h"
#include "Component/Arm.h"
#include "ArrowHitEffect.h"
#include "ArrowSmokeEffect.h"
#include "../UI/DamageFont.h"
#include "Anjanath.h"
#include "Rathalos.h"
#include "Monster.h"
#include "HealObject.h"

CDragonArrow::CDragonArrow() :
	m_DragonArrowSpeed(200.f),
	m_DragonArrowDist(200.f),
	m_Time(0.f),
	m_AttackTime(0.05f),
	m_DamageCount(0),
	m_Collision(false),
	m_Player(nullptr)
{
	SetTypeID<CDragonArrow>();

	m_DragonArrowState = DragonArrow_State::None;
}

CDragonArrow::CDragonArrow(const CDragonArrow& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("DragonArrowComponent");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DragonArrowBox");

	m_DragonArrowSpeed = obj.m_DragonArrowSpeed;
	m_DragonArrowDist = obj.m_DragonArrowDist;
}

CDragonArrow::~CDragonArrow()
{
}

void CDragonArrow::Start()
{
	CGameObject::Start();
}

bool CDragonArrow::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("DragonArrowComponent");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DragonArrowBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(15.f, 15.f, 15.f);
	m_ColliderBox->SetWorldPos(m_Mesh->GetWorldPos());
	m_ColliderBox->SetWorldRotation(m_Mesh->GetWorldRot());
	m_ColliderBox->SetCollisionProfile("PlayerAttack");

	m_Mesh->SetMesh("ArrowMesh");
	//m_Mesh->SetReceiveDecal(false);
	m_Mesh->GetTransform()->SetTransformState(Transform_State::None);

	m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetPlayerObject());

	m_ColliderBox->AddCollisionCallback<CDragonArrow>(Collision_State::Begin, this, &CDragonArrow::CollisionBegin);

	return true;
}

void CDragonArrow::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	CSkeletonSocket* Socket = m_Mesh->GetTransform()->GetSocket();

	Vector2 MousePos = CInput::GetInst()->GetMousePos();

	if (Socket == nullptr && !m_Collision )
	{
		m_Mesh->SetWorldScale(0.05f, 0.05f, 0.05f);
		m_Mesh->AddWorldPos(GetWorldAxis(AXIS::AXIS_Z) * -m_DragonArrowSpeed * DeltaTime);

		Vector3 PlayerPos = m_Player->GetWorldPos();

		float Dist = (m_Mesh->GetWorldPos() - PlayerPos).Length();

		if (m_DragonArrowDist <= Dist)
			Destroy();
	}

	if (m_Collision)
	{
		m_AttackTime -= DeltaTime;

		if (m_AttackTime <= 0.f)
		{
			m_AttackTime = 0.05f;

			if (m_DamageCount < 10)
			{
				++m_DamageCount;
				SetDamageFunc(m_CollisionResult);
			}

			else
				Destroy();
		}
	}
}

void CDragonArrow::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDragonArrow* CDragonArrow::Clone()
{
	return new CDragonArrow(*this);
}

void CDragonArrow::CollisionBegin(const CollisionResult& Result)
{
	if (m_DragonArrowState == DragonArrow_State::Flying)
	{
		m_CollisionResult = Result;

		m_Collision = true;
	}
}

void CDragonArrow::SetDamageFunc(const CollisionResult& Result)
{
	CResourceManager::GetInst()->SoundPlay("ArrowHit");

	CArrowHitEffect* HitEffect = m_Scene->CreateGameObject<CArrowHitEffect>("HitEffect");
	CArrowSmokeEffect* SmokeEffect = m_Scene->CreateGameObject<CArrowSmokeEffect>("SmokeEffect");

	HitEffect->SetWorldPos(m_Mesh->GetWorldPos());
	SmokeEffect->SetWorldPos(m_Mesh->GetWorldPos());

	if (Result.Dest->GetCollisionProfile()->Name == "FieldObj")
		return;

	if (Result.Dest->GetGameObject()->CheckType<CHealObject>())
		return;

	CSharedPtr<CDamageFont> DamageWidget = m_Scene->GetViewport()->CreateWidgetWindow<CDamageFont>("Damage");

	int DamageMin = (int)m_Player->GetPlayerMinAttack();
	int DamageMax = (int)m_Player->GetPlayerMaxAttack();

	int RandDamage = rand() % (DamageMax - DamageMin + 1) + DamageMin;

	int HitPosMinX = (int)Result.Dest->GetWorldPos().x - 1;
	int HitPosMaxX = (int)Result.Dest->GetWorldPos().x + 1;

	int HitPosMinY = (int)Result.Dest->GetWorldPos().y - 1;
	int HitPosMaxY = (int)Result.Dest->GetWorldPos().y + 1;

	int HitPosMinZ = (int)Result.Dest->GetWorldPos().z - 1;
	int HitPosMaxZ = (int)Result.Dest->GetWorldPos().z + 1;

	int RandHitPosX = rand() % (HitPosMaxX - HitPosMinX + 1) + HitPosMinX;
	int RandHitPosY = rand() % (HitPosMaxY - HitPosMinY + 1) + HitPosMinY;
	int RandHitPosZ = rand() % (HitPosMaxZ - HitPosMinZ + 1) + HitPosMinZ;

	DamageWidget->SetDamageNumber(RandDamage);
	DamageWidget->SetHitPos(Vector3((float)RandHitPosX, (float)RandHitPosY, (float)RandHitPosZ));
	DamageWidget->SetArrowMat(m_Mesh->GetWorldMatrix());
	DamageWidget->SetRotation(m_Mesh->GetWorldRot());

	if (Result.Dest->GetGameObject()->CheckType<CAnjanath>())
	{
		CAnjanath* Anjanath = (CAnjanath*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName().c_str());

		if (Anjanath)
		{
			Anjanath->SetDamage((float)RandDamage);
		}
	}

	else if (Result.Dest->GetGameObject()->CheckType<CRathalos>())
	{
		CRathalos* Rathalos = (CRathalos*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName().c_str());

		if (Rathalos)
		{
			Rathalos->SetDamage((float)RandDamage);
		}
	}

	else
	{
		CMonster* Monster = (CMonster*)m_Scene->FindObject(Result.Dest->GetGameObject()->GetName().c_str());

		if (Monster)
		{
			Monster->SetDamage((float)RandDamage);
		}
	}

}
