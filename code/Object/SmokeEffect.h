#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CSmokeEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CSmokeEffect();
    CSmokeEffect(const CSmokeEffect& obj);
    virtual ~CSmokeEffect();

private:
    CSharedPtr<CBillboardComponent> m_Billboard;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
};

