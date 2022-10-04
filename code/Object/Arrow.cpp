
#include "Arrow.h"
#include "PlayerAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/Animation/Skeleton.h"
#include "Player.h"
#include "ArrowHitEffect.h"
#include "ArrowLightEffect.h"
#include "ArrowSmokeEffect.h"
#include "ArrowStrongEffect.h"
#include "ArrowExplosionEffect.h"
#include "../UI/DamageFont.h"
#include "NormalArrowParticle.h"
#include "StrongArrowParticle.h"
#include "Barnos.h"
#include "Jagras.h"
#include "Kestodon.h"
#include "Vespoid.h"
#include "Anjanath.h"
#include "Rathalos.h"
#include "HealObject.h"

CArrow::CArrow() :
	m_ArrowSpeed(150.f),
	m_ArrowDist(120.f),
	m_Angle(0.f),
	m_Player(nullptr),
	m_Arm(nullptr),
	m_DestroyEnable(false),
	m_ProduceEnable(false),
	m_CoatingState(Coating_State::None),
	m_NormalParticle(nullptr),
	m_StrongParticle(nullptr)
{
	SetTypeID<CArrow>();

	m_ArrowState = Arrow_State::None;
}

CArrow::CArrow(const CArrow& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("ArrowComponent");
	m_ColliderBox = (CColliderBox3D*)FindComponent("ArrowBox");
}

CArrow::~CArrow()
{
}

bool CArrow::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("ArrowComponent");
	m_ColliderBox = CreateComponent<CColliderBox3D>("ArrowBox");
	m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetPlayerObject());

	SetRootComponent(m_Mesh);

	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(1.f, 1.f, 5.f);
	//m_ColliderBox->SetOffset(0.f, 0.f, 5.f);
	m_ColliderBox->SetWorldPos(m_Mesh->GetWorldPos());
	m_ColliderBox->SetWorldRotation(m_Mesh->GetWorldRot());
	m_ColliderBox->SetCollisionProfile("PlayerAttack");

	m_Mesh->SetMesh("ArrowMesh");
	m_Mesh->GetTransform()->SetTransformState(Transform_State::None);
	//m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(10.f, -20.f, 10.f);
	//m_Mesh->SetPivot(0.5f, 0.f, 0.5f);

	//m_Arm = m_Player->GetArm();


	m_ColliderBox->AddCollisionCallback<CArrow>(Collision_State::Begin, this, &CArrow::CollisionBegin);

	srand((unsigned int)time(NULL));

	rand();

	return true;
}

void CArrow::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	CreateParticleFunc(m_CoatingState);

	CSkeletonSocket* Socket = m_Mesh->GetTransform()->GetSocket();

	if (Socket == nullptr)
	{
		m_Mesh->SetWorldScale(0.05f, 0.05f, 0.05f);
		m_Mesh->SetWorldRotationX(m_Angle);
		m_Mesh->AddWorldPos(GetWorldAxis(AXIS::AXIS_Z) * -m_ArrowSpeed * DeltaTime);

		Vector3 PlayerPos = m_Player->GetWorldPos();

		float Dist = (m_Mesh->GetWorldPos() - PlayerPos).Length();

		if (m_ArrowDist <= Dist)
		{
			DestroyParticleFunc();

			Destroy();
		}
	}

	if (m_DestroyEnable)
	{
		DestroyParticleFunc();

		Destroy();
	}
}

void CArrow::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CArrow* CArrow::Clone()
{
	return new CArrow(*this);
}

void CArrow::CollisionBegin(const CollisionResult& Result)
{
	if (m_ArrowState == Arrow_State::Flying)
	{
		if (m_CoatingState == Coating_State::None)
		{
			CSharedPtr<CArrowLightEffect> HitEffect = m_Scene->CreateGameObject<CArrowLightEffect>("NoneHitEffect");
			CSharedPtr<CArrowSmokeEffect> SmokeEffect = m_Scene->CreateGameObject<CArrowSmokeEffect>("SmokeNormalEffect");
			SmokeEffect->SetCollisionEnalbe(true);

			HitEffect->SetWorldPos(m_Mesh->GetWorldPos());
			SmokeEffect->SetWorldPos(m_Mesh->GetWorldPos());

			SetDamageFunc(Result);
			
			Destroy();
		}

		else if (m_CoatingState == Coating_State::Normal)
		{
			CArrowHitEffect* HitEffect = m_Scene->CreateGameObject<CArrowHitEffect>("NormalHitEffect");
			CArrowSmokeEffect* SmokeEffect = m_Scene->CreateGameObject<CArrowSmokeEffect>("SmokeNormalEffect");

			HitEffect->SetWorldPos(m_Mesh->GetWorldPos());
			SmokeEffect->SetWorldPos(m_Mesh->GetWorldPos());

			SetDamageFunc(Result);

			if (m_NormalParticle && m_CoatingState != Coating_State::None)
			{
				m_Mesh->DeleteChild(m_NormalParticle);
				m_NormalParticle->Enable(false);
				m_NormalParticle->SetHaveEnable(false);
				m_NormalParticle->SetWorldPos(-1000.f, -1000.f, -1000.f);
			}

			Destroy();
		}

		else if (m_CoatingState == Coating_State::Strong)
		{
			CArrowHitEffect* HitEffect = m_Scene->CreateGameObject<CArrowHitEffect>("NormalHitEffect");
			CArrowStrongEffect* SmokeEffect = m_Scene->CreateGameObject<CArrowStrongEffect>("SmokeStrongEffect");

			HitEffect->SetWorldPos(m_Mesh->GetWorldPos());
			SmokeEffect->SetWorldPos(m_Mesh->GetWorldPos());

			SetDamageFunc(Result);

			if (m_StrongParticle && m_CoatingState != Coating_State::None)
			{
				m_Mesh->DeleteChild(m_StrongParticle);
				m_StrongParticle->Enable(false);
				m_StrongParticle->SetHaveEnable(false);
				m_StrongParticle->SetWorldPos(-1000.f, -1000.f, -1000.f);
			}

			Destroy();
		}

		else if (m_CoatingState == Coating_State::Explosion)
		{
			CArrowHitEffect* HitEffect = m_Scene->CreateGameObject<CArrowHitEffect>("HitEffect");
			CArrowExplosionEffect* SmokeEffect = m_Scene->CreateGameObject<CArrowExplosionEffect>("SmokeExplosionHitEffect");

			HitEffect->SetWorldPos(m_Mesh->GetWorldPos());
			SmokeEffect->SetWorldPos(m_Mesh->GetWorldPos());



			SetDamageFunc(Result);

			Destroy();
		}
	}
}

void CArrow::CreateParticleFunc(const Coating_State& State)
{
	if ((m_ArrowState == Arrow_State::Flying) && (m_CoatingState != Coating_State::None))
	{
		if (!m_ProduceEnable)
		{
			switch (State)
			{
			case Coating_State::Normal:
			{
				for (int i = 0; i < 18;)
				{
					char ParticleName[32] = {};

					sprintf_s(ParticleName, "NormalParticle%d", i);
					m_NormalParticle = (CNormalArrowParticle*)m_Scene->FindObject(ParticleName);

					if (!m_NormalParticle->GetHaveEnable())
					{
						m_Mesh->AddChild(m_NormalParticle);
						m_NormalParticle->SetWorldPos(m_Mesh->GetWorldPos());
						m_NormalParticle->Enable(true);
						m_NormalParticle->SetHaveEnable(true);

						m_ProduceEnable = true;

						break;
					}

					else
					{
						++i;
					}
				}
				m_ArrowDist = 70.f;
			}
			break;
			case Coating_State::Strong:
			{
				for (int i = 0; i < 18;)
				{
					char ParticleName[32] = {};

					sprintf_s(ParticleName, "StrongParticle%d", i);
					m_StrongParticle = (CStrongArrowParticle*)m_Scene->FindObject(ParticleName);

					if (!m_StrongParticle->GetHaveEnable())
					{
						m_Mesh->AddChild(m_StrongParticle);
						m_StrongParticle->SetWorldPos(m_Mesh->GetWorldPos());
						m_StrongParticle->Enable(true);
						m_StrongParticle->SetHaveEnable(true);

						m_ProduceEnable = true;

						break;
					}

					else
					{
						++i;
					}
				}
				m_ArrowDist = 120.f;
			}
			break;
			}


		}
	}
}

void CArrow::DestroyParticleFunc()
{
	if (m_CoatingState != Coating_State::None)
	{
		switch (m_CoatingState)
		{
		case Coating_State::Normal:
			m_Mesh->DeleteChild(m_NormalParticle);
			m_NormalParticle->Enable(false);
			m_NormalParticle->SetHaveEnable(false);
			m_NormalParticle->SetWorldPos(-1000.f, -1000.f, -1000.f);
			break;
		case Coating_State::Strong:
			m_Mesh->DeleteChild(m_StrongParticle);
			m_StrongParticle->Enable(false);
			m_StrongParticle->SetHaveEnable(false);
			m_StrongParticle->SetWorldPos(-1000.f, -1000.f, -1000.f);
			break;
		}
	}
}

void CArrow::SetDamageFunc(const CollisionResult& Result)
{
	if (Result.Dest->GetCollisionProfile()->Name == "FieldObj")
		return;

	if (Result.Dest->GetGameObject()->CheckType<CHealObject>())
		return;

	CSharedPtr<CDamageFont> DamageWidget = m_Scene->GetViewport()->CreateWidgetWindow<CDamageFont>("Damage");

	int DamageMin = 0;// (int)m_Player->GetPlayerMinAttack() * 2.f;
	int DamageMax = 0;// (int)m_Player->GetPlayerMaxAttack() * 2.f;

	switch (m_CoatingState)
	{
	case Coating_State::None:
		DamageMin = (int)m_Player->GetPlayerMinAttack();
		DamageMax = (int)m_Player->GetPlayerMaxAttack();
		break;
	case Coating_State::Normal:
		DamageMin = (int)(m_Player->GetPlayerMinAttack() * 2.f);
		DamageMax = (int)(m_Player->GetPlayerMaxAttack() * 2.f);
		break;
	case Coating_State::Strong:
		DamageMin = (int)(m_Player->GetPlayerMinAttack() * 1.3f);
		DamageMax = (int)(m_Player->GetPlayerMaxAttack() * 1.3f);
		break;
	case Coating_State::Explosion:
		DamageMin = (int)(m_Player->GetPlayerMinAttack() * 1.5f);
		DamageMax = (int)(m_Player->GetPlayerMaxAttack() * 1.5f);
		break;
	}

	int RandDamage = rand() % (DamageMax - DamageMin + 1) + DamageMin;

	int HitPosMinX = (int)m_Mesh->GetWorldPos().x - 1;
	int HitPosMaxX = (int)m_Mesh->GetWorldPos().x + 1;

	int HitPosMinY = (int)m_Mesh->GetWorldPos().y - 1;
	int HitPosMaxY = (int)m_Mesh->GetWorldPos().y + 1;

	int HitPosMinZ = (int)m_Mesh->GetWorldPos().z - 1;
	int HitPosMaxZ = (int)m_Mesh->GetWorldPos().z + 1;

	int RandHitPosX = rand() % (HitPosMaxX - HitPosMinX + 1) + HitPosMinX;
	int RandHitPosY = rand() % (HitPosMaxY - HitPosMinY + 1) + HitPosMinY;
	int RandHitPosZ = rand() % (HitPosMaxZ - HitPosMinZ + 1) + HitPosMinZ;

	DamageWidget->SetDamageNumber(RandDamage);
	DamageWidget->SetHitPos(Vector3((float)RandHitPosX, (float)RandHitPosY, (float)RandHitPosZ));
	DamageWidget->SetArrowMat(m_Mesh->GetWorldMatrix());
	DamageWidget->SetRotation(m_Mesh->GetWorldRot());
	DamageWidget->SetArrowState(m_CoatingState);

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
