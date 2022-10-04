#include "Stonej28.h"


CStonej28::CStonej28()
{
	SetTypeID<CStonej28>();
}

CStonej28::CStonej28(const CStonej28& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej28Box");
}

CStonej28::~CStonej28()
{
}

bool CStonej28::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej28Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(29.f, 18.f, 10.f);
	m_ColliderBox->SetWorldPos(0.f, 0., 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej28");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(30.f, 11.f, 30.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	return true;
}

void CStonej28::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej28::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej28* CStonej28::Clone()
{
	return DBG_NEW CStonej28(*this);
}
