#include "Stonej24.h"


CStonej24::CStonej24()
{
	SetTypeID<CStonej24>();
}

CStonej24::CStonej24(const CStonej24& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej24Box");
}

CStonej24::~CStonej24()
{
}

bool CStonej24::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej24Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(34.f, 10.f, 8.f);
	m_ColliderBox->SetWorldPos(0.f,  0.f,m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej24");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(40.f, 0.f, 20.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej24::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej24::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej24* CStonej24::Clone()
{
	return DBG_NEW CStonej24(*this);
}
