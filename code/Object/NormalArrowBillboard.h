#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CNormalArrowBillboard :
    public CGameObject
{
    friend class CScene;

protected:
    CNormalArrowBillboard();
    CNormalArrowBillboard(const CNormalArrowBillboard& obj);
    virtual ~CNormalArrowBillboard();

private:
    CSharedPtr<CBillboardComponent> m_Billboard;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
};

