
#include "Stonej1.h"

CStonej1::CStonej1()
{
	SetTypeID<CStonej1>();
}

CStonej1::CStonej1(const CStonej1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej1Box");
}

CStonej1::~CStonej1()
{
}

bool CStonej1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej1Box");


	
	
	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);


	m_Mesh->SetTransformState(Transform_State::None);
	m_ColliderBox->Set3DExtent(20.f, 15.f, 7.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej1");

	
	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(0.f, 10.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CStonej1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);	
}

CStonej1* CStonej1::Clone()
{
	return DBG_NEW CStonej1(*this);
}
