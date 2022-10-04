
#include "SmallStone1.h"

CSmallStone1::CSmallStone1()
{
	SetTypeID<CSmallStone1>();
}

CSmallStone1::CSmallStone1(const CSmallStone1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("SmallStone1Box");
}

CSmallStone1::~CSmallStone1()
{
}

bool CSmallStone1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("SmallStone1Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(5.f, 4.f, 1.f);
	m_ColliderBox->SetWorldPos(-1.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("SmallStone1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CSmallStone1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CSmallStone1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSmallStone1* CSmallStone1::Clone()
{
	return DBG_NEW CSmallStone1(*this);
}
