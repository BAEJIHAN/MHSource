
#include "Tree9.h"

CTree9::CTree9()
{
	SetTypeID<CTree9>();

	m_XLength = 0.f;
	m_YLength = 0.f;
	m_ZLength = 0.f;
}

CTree9::CTree9(const CTree9& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Tree9");
}

CTree9::~CTree9()
{
}

bool CTree9::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Tree9Collider");

	m_Mesh->SetMesh("Tree9");
	m_Mesh->SetRelativeScale(0.02f, 0.02f, 0.02f);
	m_Mesh->SetRelativePos(0.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(7.f, 7.f, 7.f);
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

void CTree9::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTree9::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTree9* CTree9::Clone()
{
	return DBG_NEW CTree9(*this);
}
