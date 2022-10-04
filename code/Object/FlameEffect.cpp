
#include "FlameEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"
#include "../Object/Player.h"
#include "../Object/SmokeEffect.h"
#include "../Object/FireEffect.h"
#include "../Object/BurnedDecal.h"
#include "../Object/SparkEffect.h"
#include "../Object/ExplosionEffect.h"

CFlameEffect::CFlameEffect() :
	m_Dir(0.f, 0.f, 0.f),
	m_Dist(50.f),
	m_Speed(130.f),
	m_Moving(false),
	m_Explosive(false)
{
	SetTypeID<CFlameEffect>();
}

CFlameEffect::CFlameEffect(const CFlameEffect& obj) :
	CGameObject(obj)
{
}

CFlameEffect::~CFlameEffect()
{
}

void CFlameEffect::Move(Vector3 Dir, float Dist, float Speed)
{
	m_Moving = true;

	m_Dir = Dir;
	m_Dir.Normalize();

	m_Dist = Dist;
	m_Speed = Speed;
}

bool CFlameEffect::Init()
{
	m_Billboard = CreateComponent<CBillboardComponent>("FlameEffectBillboard");
	m_Light = CreateComponent<CLightComponent>("Light");
	m_ColliderBox = CreateComponent<CColliderBox3D>("FlameCollider");
	
	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("FlameBillboard1");
	m_Billboard->SetWorldScale(30.f, 30.f, 10.f);
	m_Billboard->SetBaseColor(3.f, 3.f, 3.f, 3.f);
	m_Billboard->SetOpacity(1.0f);
	m_Billboard->SetDuration(0.7f);
	m_Billboard->SetFadeOutTime(0.3f);

	m_Light->SetLightType(Light_Type::Point);
	m_Light->SetDistance(100.f);
	m_Light->SetAtt3(0.02f);
	m_Light->SetColor(Vector4(1.f, 0.5f, 0.f, 1.f));

	m_ColliderBox->Set3DExtent(5.f, 5.f, 5.f);
	m_ColliderBox->SetCollisionProfile("MonsterAttack");
	m_ColliderBox->AddCollisionCallback(Collision_State::Begin, this, &CFlameEffect::OnCollisionBegin);

	m_Billboard->AddChild(m_Light);
	m_Billboard->AddChild(m_ColliderBox);

	return true;	
}

void CFlameEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Moving)
	{
		AddRelativePos(m_Dir * m_Speed * DeltaTime);
	}

	if (m_Explosive)
	{
		Vector3 Pos = GetWorldPos();

		float Y = m_Scene->GetNavigation3DManager()->GetY(Pos);

		if (Y > Pos.y)
		{
			// Æø¹ß
			CreateEffects();

			Destroy();
		}
	}
}

void CFlameEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CFlameEffect* CFlameEffect::Clone()
{
	return nullptr;
}

void CFlameEffect::CreateEffects()
{
	Vector3 Pos = GetWorldPos();
	Pos.y += 5.f;

	m_Scene->CreateGameObject<CSmokeEffect>("ExplosiveSmoke")->SetWorldPos(Pos);
	m_Scene->CreateGameObject<CExplosionEffect>("ExplosionEffect")->SetWorldPos(Pos);
	m_Scene->CreateGameObject<CSparkEffect>("SparkEffect")->SetWorldPos(Pos);

	CBurnedDecal* Decal = m_Scene->CreateGameObject<CBurnedDecal>("BurnedDecal");
	Decal->SetWorldPos(Pos);
	Decal->PresetToExplosive();

	m_Scene->GetCameraManager()->GetCurrentCamera()->ShakeOn(0.2f, 0.4f);
	m_Scene->GetResource()->SoundPlay("RathalosShortBreath2SE", this);
}

void CFlameEffect::OnCollisionBegin(const CollisionResult& result)
{
	if (result.Dest->GetGameObject()->CheckType<CLandScape>())
	{
	}
}
