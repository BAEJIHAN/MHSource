
#include "RockFractalParticle.h"	

CRockFractalParticle::CRockFractalParticle() :
	m_SpawnCount(50.f)
{
}

CRockFractalParticle::CRockFractalParticle(const CRockFractalParticle& obj)
{
}

CRockFractalParticle::~CRockFractalParticle()
{
}

void CRockFractalParticle::SetParticleAlive(int Alive)
{
	m_Particle->SetParticleAlive(Alive);

	m_Particle->GetCBuffer()->UpdateCBuffer();
}

void CRockFractalParticle::Start()
{
	CGameObject::Start();
}

bool CRockFractalParticle::Init()
{
	if (!CGameObject::Init())
	{
		return false;
	}

	m_Particle = CreateComponent<CParticleComponent>("RockParticle");

	SetRootComponent(m_Particle);

	m_Particle->SetParticle("RockParticle");
	m_Particle->SetRelativePos(10.f, 5.f, 10.f);

	return true;
}

void CRockFractalParticle::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Particle->SetParticleAlive(1);
}
