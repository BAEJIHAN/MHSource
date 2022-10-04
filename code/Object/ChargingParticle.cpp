
#include "ChargingParticle.h"
#include "ParticleAnimation.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Player.h"
#include "Resource/Particle/Particle.h"

CChargingParticle::CChargingParticle()	:
	m_SpawnCount(50.f)
{
}

CChargingParticle::CChargingParticle(const CChargingParticle& obj)
{
}

CChargingParticle::~CChargingParticle()
{
}

void CChargingParticle::SetParticleAlive(int Alive)
{
	m_Particle->SetParticleAlive(Alive);

	m_Particle->GetCBuffer()->UpdateCBuffer();
}

void CChargingParticle::Start()
{
	CGameObject::Start();
}

bool CChargingParticle::Init()
{
	m_Particle = CreateComponent<CParticleComponent>("ChargingParticle");

	SetRootComponent(m_Particle);
	
	m_Particle->SetParticle("ChargingParticle");
	m_Particle->SetRelativePos(10.f, 5.f, 10.f);
	m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetPlayerObject());

	Vector3 PlayerPos = m_Player->GetWorldPos();


	return true;
}

void CChargingParticle::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//m_SpawnCount += DeltaTime * 20.f;

	float DirY = m_Player->GetWorldRot().y;

	
	Vector3 Rot = m_Player->GetWorldAxis(AXIS::AXIS_Z);

	Vector3 ConvertRot = Vector3(Rot.y, 0.f, Rot.y);



	m_Particle->SetParticleAlive(1);
	m_Particle->SetWorldPos(m_Player->GetWorldPos() + m_Player->GetWorldAxis(AXIS::AXIS_Z) * -7.f);
	m_Particle->SetComponentAngle(m_Player->GetWorldRot());
	m_Particle->SetMoveDir(Rot);
	m_Particle->GetCBuffer()->UpdateCBuffer();
}

CChargingParticle* CChargingParticle::Clone()
{
	return new CChargingParticle(*this);
}
