#pragma once

#include "GameObject/GameObject.h"
#include "Component/ParticleComponent.h"

class CNormalArrowParticle :
    public CGameObject
{
    friend class CScene;

protected:
    CNormalArrowParticle();
    CNormalArrowParticle(const CNormalArrowParticle& obj);
    virtual ~CNormalArrowParticle();

private:
    CSharedPtr<CParticleComponent>    m_Particle;
    class CGameObject* m_Player;

    float m_SpawnCount;

    bool    m_HaveEnable;

public:
    void SetHaveEnable(bool Enable)
    {
        m_HaveEnable = Enable;
    }

    bool GetHaveEnable()    const
    {
        return m_HaveEnable;
    }

public:
    void SetParticleAlive(int Alive);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CNormalArrowParticle* Clone();
};

