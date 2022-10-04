#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"
#include "Component/LightComponent.h"

class CExplosionEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CExplosionEffect();
    CExplosionEffect(const CExplosionEffect& obj);
    virtual ~CExplosionEffect();

private:
    CSharedPtr<CBillboardComponent> m_Billboard;
    CSharedPtr<CLightComponent> m_Light;

private:
    float   m_LightOffTime;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
};

