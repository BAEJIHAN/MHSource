#include "HitBreathEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Player.h"

CHitBreathEffect::CHitBreathEffect()	:
	m_Player(nullptr),
	m_Time(8.5f)
{
	SetTypeID<CHitBreathEffect>();
}

CHitBreathEffect::CHitBreathEffect(const CHitBreathEffect& obj) :
	CGameObject(obj)
{
}

CHitBreathEffect::~CHitBreathEffect()
{
}

void CHitBreathEffect::Start()
{
	CGameObject::Start();

	m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetScene()->GetPlayerObject());
}

bool CHitBreathEffect::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Billboard = CreateComponent<CBillboardComponent>("HitBreathBillboard");

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("HitBreath");
	m_Billboard->SetWorldScale(7.f, 7.f, 1.f);
	m_Billboard->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	//m_Billboard->SetBaseColor(0.5f, 0.5f, 0.5f, 1.f);
	m_Billboard->SetOpacity(1.0f);
	m_Billboard->SetDuration(5.f);
	m_Billboard->SetFadeOutTime(0.6f);

	return true;
}

void CHitBreathEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Player)
	{
		Vector3 ConvertPos = m_Player->GetWorldPos();
		
		ConvertPos.y += 6.f;
		
		m_Billboard->SetWorldPos(ConvertPos);

		//m_Time -= DeltaTime;
		//
		//if (m_Time <= 0.f)
		//{
		//	((CAnimationMeshComponent*)m_Player->GetRootComponent())->DeleteChild(m_Billboard);
		//
		//	m_Time = 1000.f;
		//}
	}
}

void CHitBreathEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}
