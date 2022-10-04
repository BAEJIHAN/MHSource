#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CArrowHitEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CArrowHitEffect();
    CArrowHitEffect(const CArrowHitEffect& obj);
    virtual ~CArrowHitEffect();

private:
    CSharedPtr<CBillboardComponent>    m_Billboard;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CArrowHitEffect* Clone();

private:
    void SetEndNotify();
};

