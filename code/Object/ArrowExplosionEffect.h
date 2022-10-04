#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CArrowExplosionEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CArrowExplosionEffect();
    CArrowExplosionEffect(const CArrowExplosionEffect& obj);
    virtual ~CArrowExplosionEffect();

private:
    CSharedPtr<CBillboardComponent>    m_Billboard;

    bool    m_CollisionEnable;
    float   m_Time;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CArrowExplosionEffect* Clone();

private:
    void SetEndNotify();
};

