
#include "HealEffect.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Player.h"

CHealEffect::CHealEffect() :
	m_CollisionEnable(false),
	m_CollisionObject(false),
	m_Time(1.f)
{
}

CHealEffect::CHealEffect(const CHealEffect& obj)
{
}

CHealEffect::~CHealEffect()
{
}

bool CHealEffect::Init()
{
	m_Billboard = CreateComponent<CBillboardComponent>("HealEffect");
	m_Billboard1 = CreateComponent<CBillboardComponent>("HealEffect1");

	SetRootComponent(m_Billboard);

	m_Billboard->AddChild(m_Billboard1);

	m_Billboard->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard->GetAnimationInstance()->ChangeAnimation("SmokeBillboard1");

	m_Billboard->GetAnimationInstance()->SetEndFunction<CHealEffect>("SmokeBillboard1", this, &CHealEffect::SetEndNotify);
	m_Billboard->SetBaseColor(0.3f, 0.9f, 0.2f, 1.f);

	m_Billboard->SetWorldScale(15.f, 15.f, 1.f);


	m_Billboard1->CreateAnimationInstance<CParticleAnimation>();
	m_Billboard1->GetAnimationInstance()->ChangeAnimation("SmokeBillboard2");

	m_Billboard1->GetAnimationInstance()->SetEndFunction<CHealEffect>("SmokeBillboard2", this, &CHealEffect::SetEndNotify);
	m_Billboard1->SetBaseColor(0.3f, 0.8f, 0.2f, 1.f);

	m_Billboard1->SetWorldScale(15.f, 15.f, 1.f);

	m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetPlayerObject());

	return true;
}

void CHealEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_CollisionEnable)
	{
		m_Time -= DeltaTime;
		m_Billboard->SetOpacity(m_Time);
		m_Billboard1->SetOpacity(m_Time);

		if (m_Time <= 0.f)
			Destroy();
	}


	if (m_CollisionObject)
	{
		if (m_Player)
		{
			Vector3 PlayerPos = m_Player->GetWorldPos();
			PlayerPos.y += 5.f;
			Vector3 Dir = PlayerPos - GetWorldPos();

			Dir.Normalize();

			m_Billboard->AddWorldPos(Dir * 20.f * DeltaTime);
			//m_Billboard1->AddWorldPos(Dir * 10.f * DeltaTime);

			int Dist = (int)PlayerPos.Distance(GetWorldPos());

			if (Dist == 0)
			{
				m_CollisionObject = false;
				float PlayerHP = m_Player->GetPlayerHP();
				float PlayerMaxHP = m_Player->GetPlayerMaxHP();

				PlayerHP += 30.f;

				if (PlayerHP > PlayerMaxHP)
					PlayerHP = PlayerMaxHP;

				m_Player->SetPlayerHP(PlayerHP);

				m_CollisionEnable = true;
			}
		}
	}
}

CHealEffect* CHealEffect::Clone()
{
	return new CHealEffect(*this);
}

void CHealEffect::SetEndNotify()
{
	if (!m_CollisionObject)
		m_CollisionEnable = true;
}
