#pragma once

#include "GameObject/GameObject.h"
#include "Component/ParticleComponent.h"

class CStrongArrowParticle :
    public CGameObject
{
    friend class CScene;

protected:
    CStrongArrowParticle();
    CStrongArrowParticle(const CStrongArrowParticle& obj);
    virtual ~CStrongArrowParticle();

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
    virtual CStrongArrowParticle* Clone();
};

