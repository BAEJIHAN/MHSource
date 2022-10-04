#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CFireEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CFireEffect();
    CFireEffect(const CFireEffect& obj);
    virtual ~CFireEffect();

private:
    CSharedPtr<CBillboardComponent> m_Billboard;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
};

