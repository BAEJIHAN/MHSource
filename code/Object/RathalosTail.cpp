
#include "RathalosTail.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"

CRathalosTail::CRathalosTail()
{
	SetTypeID<CRathalosTail>();
}

CRathalosTail::CRathalosTail(const CRathalosTail& obj)
{
}

CRathalosTail::~CRathalosTail()
{
}

bool CRathalosTail::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Mesh = CreateComponent<CStaticMeshComponent>("StaticMesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("ColliderBox");

	m_Mesh->SetMesh("RathalosTailMesh");
	m_Mesh->SetRelativeScale(0.04f, 0.04f, 0.04f);
	m_Mesh->SetRelativeRotationY(90.f);

	m_ColliderBox->Set3DExtent(3.f, 3.f, 3.f);
	m_ColliderBox->SetCollisionProfile("Carving");

	m_Mesh->AddChild(m_ColliderBox);

	return true;
}

void CRathalosTail::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRathalosTail::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CRathalosTail* CRathalosTail::Clone()
{
	return nullptr;
}

void CRathalosTail::OnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetGameObject()->GetName() == "Player")
	{

	}
}
