
#include "BowBox.h"
#include "PlayerAnimation.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence.h"
#include "Scene/Scene.h"

CBowBox::CBowBox()
{
	SetTypeID<CBowBox>();
}

CBowBox::CBowBox(const CBowBox& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("BowBox");
}

CBowBox::~CBowBox()
{
}

bool CBowBox::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("BowBox");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("BowBoxMesh");

	//m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(10.f, -20.f, 10.f);
	m_Mesh->SetPivot(0.5f, 0.f, 0.5f);
	//m_Mesh->GetTransform()->SetTransformState(Transform_State::None);

	return true;
}

void CBowBox::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CBowBox::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBowBox* CBowBox::Clone()
{
	return new CBowBox(*this);
}
