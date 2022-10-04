
#pragma once

#include "GameObject/GameObject.h"
#include "Component/ParticleComponent.h"

class CRockFractalParticle :
    public CGameObject
{
    friend class CScene;

protected:
    CRockFractalParticle();
    CRockFractalParticle(const CRockFractalParticle& obj);
    virtual ~CRockFractalParticle();

private:
    CSharedPtr<CParticleComponent>    m_Particle;

private:
    float m_SpawnCount;

public:
    void SetParticleAlive(int Alive);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

