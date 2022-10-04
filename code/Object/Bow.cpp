
#include "Bow.h"
#include "WeaponAnimation.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Resource/Shader/RimLightConstantBuffer.h"
#include "Component/CameraComponent.h"
#include "Scene/CameraManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Player.h"

CBow::CBow()	:
	m_Time(0.5f),
	m_ColorR(0.59f),
	m_ColorG(0.f),
	m_ColorB(0.f),
	m_Count(0),
	m_Inverse(false),
	m_LoopEnable(false),
	m_Charging1To2(true),
	m_FirstCharging(true)
{
	SetTypeID<CBow>();
	m_EmissiveColor = Vector3(0.5f, 0.5f, 0.5f);
}

CBow::CBow(const CBow& obj) :
	CGameObject(obj)
{
	m_Mesh = (CAnimationMeshComponent*)FindComponent("BowComponent");
}

CBow::~CBow()
{
	SAFE_DELETE(m_CBuffer);
}

void CBow::SetRimLightEnable(bool Enable)
{
	m_CBuffer->SetRimLightEnable(Enable);

	m_CBuffer->UpdateCBuffer();
}

void CBow::Start()
{
	CGameObject::Start();

	m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetPlayerObject());
}

bool CBow::Init()
{
	m_Mesh = CreateComponent<CAnimationMeshComponent>("BowComponent");

	SetRootComponent(m_Mesh);

	m_Mesh->CreateAnimationInstance<CWeaponAnimation>();
	
	m_Mesh->SetMesh("BowMesh");
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BowBack");
	m_Mesh->SetWorldScale(0.7f, 1.f, 0.7f);
	m_Mesh->GetTransform()->SetTransformState(Transform_State::None);
	//m_Mesh->SetLayerName("RimLight");

	int Size = m_Mesh->GetMaterialSlotCount();

	for (int i = 0; i < Size; ++i)
	{
		m_Mesh->GetMaterial(i)->SetShader("RimLightShader");
	}

	SetEndNotify();

	m_CBuffer = new CRimLightConstantBuffer;

	m_CBuffer->Init();

	m_CBuffer->SetRimLightEnable(false);


	return true;
}

void CBow::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Vector3 CameraPos = m_Player->GetArm()->GetWorldPos();

	m_CBuffer->SetRimLightCameraPos(CameraPos);

	if (m_CBuffer->GetRimLightEnable())
	{
		if (!m_Player->GetDragonShotEnable())
		{
			int ChargingCount = m_Player->GetChargingCount();

			if (ChargingCount == 1)
			{
				if (m_FirstCharging)
				{
					m_FirstCharging = false;

					m_ColorR = 0.59f;
					m_ColorG = 0.f;
					m_ColorB = 0.f;
					m_EmissiveColor = Vector3(0.5f, 0.5f, 0.5f);
					m_Time = 0.5f;

					m_Inverse = false;
				}

				if (!m_Inverse)
					m_Time += DeltaTime * 3.f;

				else
					m_Time -= DeltaTime * 3.f;

				if (m_Time >= 3.5f)
					m_Inverse = true;

				else if (m_Time <= 0.5f)
					m_Inverse = false;
			}

			if (ChargingCount >= 2)
			{
				if (m_Charging1To2)
				{
					m_Charging1To2 = false;

					m_ColorR = 0.59f;
					m_ColorG = 0.f;
					m_ColorB = 0.f;

					m_EmissiveColor = Vector3(0.5f, 0.5f, 0.5f);
					m_Time = 0.5f;

					m_Inverse = false;
				}

				if (!m_Inverse)
					m_Time += DeltaTime * 3.f;

				if (m_Time >= 3.5f)
					m_LoopEnable = true;

				else if (m_Time <= 0.f)
					m_LoopEnable = true;
			}

			if (m_LoopEnable)
			{
				if (!m_Inverse)
					m_Time += DeltaTime * 3.f;

				else
					m_Time -= DeltaTime * 3.f;

				if (m_Time >= 3.5f)
					m_Inverse = true;

				else if (m_Time <= 0.5f)
					m_Inverse = false;
			}
		}

		if (m_Player->GetDragonShotEnable())
		{
			if (m_LoopEnable)
			{
				if (!m_Inverse)
					m_Time += DeltaTime * 3.f;

				else
					m_Time -= DeltaTime * 3.f;

				if (m_Time >= 3.5f)
					m_Inverse = true;

				else if (m_Time <= 0.5f)
					m_Inverse = false;
			}
		}

		m_EmissiveColor -= DeltaTime;

		if (m_EmissiveColor.x <= 0.f || m_EmissiveColor.y <= 0.f || m_EmissiveColor.z <= 0.f)
		{
			m_EmissiveColor = Vector3(0.f, 0.f, 0.f);
		}

		m_CBuffer->SetRimEmissiveColor(m_EmissiveColor);

		m_CBuffer->SetRimPower(m_Time);

		m_CBuffer->SetRimColor(Vector3(m_ColorR, m_ColorG, m_ColorB));

		m_CBuffer->UpdateCBuffer();
	}
	
}

void CBow::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBow* CBow::Clone()
{
	return new CBow(*this);
}

void CBow::SetEndNotify()
{
	m_Mesh->GetAnimationInstance()->SetEndFunction<CBow>("BowChargingStart", this, &CBow::BowChargingStartEndNotify);
}

void CBow::BowChargingStartEndNotify()
{
	m_Mesh->GetAnimationInstance()->ChangeAnimation("BowChargingLoop");
}
