#pragma once

#include "GameObject/GameObject.h"
#include "Component/ParticleComponent.h"

class CChargingParticle :
    public CGameObject
{
    friend class CScene;

protected:
    CChargingParticle();
    CChargingParticle(const CChargingParticle& obj);
    virtual ~CChargingParticle();

private:
    CSharedPtr<CParticleComponent>    m_Particle;
    class CGameObject*   m_Player;

    float m_SpawnCount;

public:
    void SetParticleAlive(int Alive);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CChargingParticle* Clone();
};

