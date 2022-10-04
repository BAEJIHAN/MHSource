#include "Stonej37.h"


CStonej37::CStonej37()
{
	SetTypeID<CStonej37>();
}

CStonej37::CStonej37(const CStonej37& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej37Box");
}

CStonej37::~CStonej37()
{
}

bool CStonej37::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej37Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(18.f, 11.f, 5.f);
	m_ColliderBox->SetWorldPos(0.f, -1.f, m_ColliderBox->GetInfo().Length.z - 2.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej37");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(30.f, 7.f, 30.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	return true;
}

void CStonej37::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej37::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej37* CStonej37::Clone()
{
	return DBG_NEW CStonej37(*this);
}
