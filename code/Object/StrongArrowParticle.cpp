
#include "StrongArrowParticle.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Resource/Particle/Particle.h"

CStrongArrowParticle::CStrongArrowParticle()	:
	m_HaveEnable(false)
{
}

CStrongArrowParticle::CStrongArrowParticle(const CStrongArrowParticle& obj)
{
	m_Particle = (CParticleComponent*)m_Scene->FindObject("StrongArrowParticle");
}

CStrongArrowParticle::~CStrongArrowParticle()
{
}

void CStrongArrowParticle::SetParticleAlive(int Alive)
{
	m_Particle->SetParticleAlive(Alive);

	m_Particle->GetCBuffer()->UpdateCBuffer();
}

void CStrongArrowParticle::Start()
{
	CGameObject::Start();
}

bool CStrongArrowParticle::Init()
{
	m_Particle = CreateComponent<CParticleComponent>("StrongArrowParticle");

	SetRootComponent(m_Particle);

	m_Particle->SetParticle("StrongArrowParticle");
	//m_Particle->SetRelativePos(10.f, 5.f, 10.f);
	//m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetPlayerObject());
	//
	//Vector3 PlayerPos = m_Player->GetWorldPos();


	return true;
}

void CStrongArrowParticle::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//Vector3 Rot = m_Player->GetWorldAxis(AXIS::AXIS_Z);


	//m_Particle->SetWorldPos(m_Player->GetWorldPos() + m_Player->GetWorldAxis(AXIS::AXIS_Z) * -7.f);
	//m_Particle->SetComponentAngle(m_Player->GetWorldRot());
	//m_Particle->SetMoveDir(Rot);
	//Bm_Particle->GetCBuffer()->UpdateCBuffer();
}

CStrongArrowParticle* CStrongArrowParticle::Clone()
{
	return new CStrongArrowParticle(*this);
}
