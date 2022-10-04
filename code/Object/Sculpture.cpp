
#include "Sculpture.h"

CSculpture::CSculpture()
{
	SetTypeID<CSculpture>();
}

CSculpture::CSculpture(const CSculpture& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("SculptureBox");
}

CSculpture::~CSculpture()
{
}

bool CSculpture::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("SculptureBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(100.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("Sculpture1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CSculpture::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CSculpture::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSculpture* CSculpture::Clone()
{
	return DBG_NEW CSculpture(*this);
}
