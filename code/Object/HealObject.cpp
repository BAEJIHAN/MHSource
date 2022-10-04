
#include "HealObject.h"
#include "PlayerAnimation.h"
#include "Input.h"
#include "ParticleAnimation.h"
#include "HealEffect.h"
#include "Scene/Scene.h"
#include "Arrow.h"

CHealObject::CHealObject() :
	m_DestroyEnable(false),
	m_Opacity(1.f)
{
	SetTypeID<CHealObject>();
}

CHealObject::CHealObject(const CHealObject& obj)
{
	m_Billboard = (CBillboardComponent*)FindComponent("HealObjectBillboard");
	m_ColliderBox = (CColliderBox3D*)FindComponent("HealObjectBox");
}

CHealObject::~CHealObject()
{
}

bool CHealObject::Init()
{
	m_Billboard = CreateComponent<CBillboardComponent>("HealObjectBillboard");
	m_ColliderBox = CreateComponent<CColliderBox3D>("HealObjectBox");

	SetRootComponent(m_Billboard);

	m_Billboard->AddChild(m_ColliderBox);

	m_ColliderBox->Set3DExtent(3.f, 3.f, 3.f);
	m_ColliderBox->SetOffset(0.f, 0.f, 0.f);
	m_ColliderBox->SetCollisionProfile("Monster");
	m_ColliderBox->AddCollisionCallback<CHealObject>(Collision_State::Begin, this, &CHealObject::CollisionBegin);

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("EtcBillboard1");
	m_Billboard->SetWorldScale(10.f, 10.f, 1.f);
	m_Billboard->SetBaseColor(0.3f, 0.9f, 0.4f, 1.f);
	m_Billboard->SetTransformState(Transform_State::None);


	return true;
}

void CHealObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CHealObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CHealObject* CHealObject::Clone()
{
	return new CHealObject(*this);
}

void CHealObject::CollisionBegin(const CollisionResult& Result)
{
	if (Result.Dest->GetGameObject()->CheckType<CArrow>())
	{
		CHealEffect* HealEffect = m_Scene->CreateGameObject<CHealEffect>("HealEffect");
		HealEffect->SetObjectEnable(true);
		HealEffect->SetWorldPos(m_Billboard->GetWorldPos());

		Destroy();
	}
	//char ObjName[32] = {};

	//strcpy_s(ObjName, Result.Dest->GetGameObject()->GetName().c_str());

	//int NameLength = (int)strlen(ObjName);

	//if (NameLength >= 6)
	//{
	//	for (int i = NameLength - 1; i > 0; --i)
	//	{
	//		if (ObjName[i] == 'w')
	//		{
	//			memset(&ObjName[i + 1], 0, sizeof(char) * (NameLength - i - 1));
	//			break;
	//		}
	//	}
	//}

	//// 문자열 비교
	//int Ret = strcmp(ObjName, "Arrow");

	//if (Ret == 0)
	//{
	//	CHealEffect* HealEffect = m_Scene->CreateGameObject<CHealEffect>("HealEffect");
	//	HealEffect->SetObjectEnable(true);
	//	HealEffect->SetWorldPos(m_Billboard->GetWorldPos());

	//	Destroy();
	//}
}
