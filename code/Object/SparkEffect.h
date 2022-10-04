#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CSparkEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CSparkEffect();
    CSparkEffect(const CSparkEffect& obj);
    virtual ~CSparkEffect();

private:
    CSharedPtr<CBillboardComponent> m_Billboard;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
};

