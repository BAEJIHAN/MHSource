#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CArrowSmokeEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CArrowSmokeEffect();
    CArrowSmokeEffect(const CArrowSmokeEffect& obj);
    virtual ~CArrowSmokeEffect();

private:
    CSharedPtr<CBillboardComponent>    m_Billboard;

    bool    m_CollisionEnable;
    float   m_Time;

public:
    void SetCollisionEnalbe(bool Enable)
    {
        m_CollisionEnable = Enable;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CArrowSmokeEffect* Clone();

private:
    void SetEndNotify();
};

