#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CArrowStrongEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CArrowStrongEffect();
    CArrowStrongEffect(const CArrowStrongEffect& obj);
    virtual ~CArrowStrongEffect();

private:
    CSharedPtr<CBillboardComponent>    m_Billboard;

    bool    m_CollisionEnable;
    float   m_Time;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CArrowStrongEffect* Clone();

private:
    void SetEndNotify();
};

