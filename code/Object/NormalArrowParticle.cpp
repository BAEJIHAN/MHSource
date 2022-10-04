
#include "NormalArrowParticle.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Resource/Particle/Particle.h"

CNormalArrowParticle::CNormalArrowParticle() :
	m_HaveEnable(false)
{
}

CNormalArrowParticle::CNormalArrowParticle(const CNormalArrowParticle& obj)
{
	m_Particle = (CParticleComponent*)m_Scene->FindObject("NormalArrowParticle");
}

CNormalArrowParticle::~CNormalArrowParticle()
{
}

void CNormalArrowParticle::SetParticleAlive(int Alive)
{
	m_Particle->SetParticleAlive(Alive);

	m_Particle->GetCBuffer()->UpdateCBuffer();
}

void CNormalArrowParticle::Start()
{
	CGameObject::Start();
}

bool CNormalArrowParticle::Init()
{
	m_Particle = CreateComponent<CParticleComponent>("NormalArrowParticle");

	SetRootComponent(m_Particle);

	m_Particle->SetParticle("NormalArrowParticle");
	//m_Particle->SetRelativePos(10.f, 5.f, 10.f);
	//m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetPlayerObject());
	//
	//Vector3 PlayerPos = m_Player->GetWorldPos();


	return true;
}

void CNormalArrowParticle::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//Vector3 Rot = m_Player->GetWorldAxis(AXIS::AXIS_Z);


	//m_Particle->SetWorldPos(m_Player->GetWorldPos() + m_Player->GetWorldAxis(AXIS::AXIS_Z) * -7.f);
	//m_Particle->SetComponentAngle(m_Player->GetWorldRot());
	//m_Particle->SetMoveDir(Rot);
	//Bm_Particle->GetCBuffer()->UpdateCBuffer();
}

CNormalArrowParticle* CNormalArrowParticle::Clone()
{
	return new CNormalArrowParticle(*this);
}
