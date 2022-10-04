
#include "AnjanathTail.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"

CAnjanathTail::CAnjanathTail()
{
	SetTypeID<CAnjanathTail>();
}

CAnjanathTail::CAnjanathTail(const CAnjanathTail& obj)
{
}

CAnjanathTail::~CAnjanathTail()
{
}

bool CAnjanathTail::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Mesh = CreateComponent<CStaticMeshComponent>("StaticMesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("ColliderBox");
	
	m_Mesh->SetMesh("AnjanathTailMesh");
	m_Mesh->SetRelativeScale(0.04f, 0.04f, 0.04f);
	m_Mesh->SetRelativeRotation(Vector3(-90.f, 0.f, 180.f));

	m_ColliderBox->Set3DExtent(3.f, 3.f, 3.f);
	m_ColliderBox->SetCollisionProfile("Carving");

	m_Mesh->AddChild(m_ColliderBox);

	return true;
}

void CAnjanathTail::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CAnjanathTail::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CAnjanathTail* CAnjanathTail::Clone()
{
	return nullptr;
}

void CAnjanathTail::OnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{

	}
}
