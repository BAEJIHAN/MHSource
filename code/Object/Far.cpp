
#include "Far.h"

CFar::CFar()
{
	SetTypeID<CFar>();
}

CFar::CFar(const CFar& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("FarBox");
}

CFar::~CFar()
{
}

bool CFar::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("FarBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(500.f, 200.f, 200.f);
	m_ColliderBox->SetRelativePos(0.f, -120.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("Far");

	m_Mesh->SetTransformState(Transform_State::None);
	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CFar::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CFar::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFar* CFar::Clone()
{
	return DBG_NEW CFar(*this);
}
