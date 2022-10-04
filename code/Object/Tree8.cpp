
#include "Tree8.h"

CTree8::CTree8()
{
	SetTypeID<CTree8>();
}

CTree8::CTree8(const CTree8& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Tree8");
}

CTree8::~CTree8()
{
}

bool CTree8::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Tree8Collider");

	m_Mesh->SetMesh("Tree8");
	m_Mesh->SetRelativeScale(0.005f, 0.005f, 0.005f);
	m_Mesh->SetRelativePos(0.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-180.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(2.f, 2.f, 2.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->AddChild(m_ColliderBox);

	int Size = (int)m_Mesh->GetMaterialSlotCount();

	for (int i = 0; i < Size; ++i)
	{
		m_Mesh->GetMaterial(i)->SetRenderState("NoneCull");
	}

	return true;
}

void CTree8::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTree8::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTree8* CTree8::Clone()
{
	return DBG_NEW CTree8(*this);
}
