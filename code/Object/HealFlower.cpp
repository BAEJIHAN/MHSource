
#include "HealFlower.h"

CHealFlower::CHealFlower()	:
	m_DestroyEnable(false),
	m_Opacity(1.f)
{
	SetTypeID<CHealFlower>();
}

CHealFlower::CHealFlower(const CHealFlower& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("HealFlowerComponent");
	m_ColliderBox = (CColliderBox3D*)FindComponent("HealFlowerBox");
}

CHealFlower::~CHealFlower()
{
}

bool CHealFlower::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("HealFlowerComponent");
	m_ColliderBox = CreateComponent<CColliderBox3D>("HealFlowerBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_ColliderBox->Set3DExtent(3.f);
	m_ColliderBox->SetOffset(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("Environment");

	m_Mesh->SetMesh("SmallTree1");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetRelativePos(0.f, 0.f, 5.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CHealFlower::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_DestroyEnable)
	{
		m_Opacity -= DeltaTime * 0.3f;

		m_Mesh->SetOpacity(m_Opacity);
		m_Mesh->SetOpacity(m_Opacity, 1);
		m_Mesh->SetOpacity(m_Opacity, 2);

		if (m_Opacity <= 0.f)
			Destroy();
	}
}

void CHealFlower::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CHealFlower* CHealFlower::Clone()
{
	return DBG_NEW CHealFlower(*this);
}
