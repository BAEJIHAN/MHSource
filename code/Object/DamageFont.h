#pragma once
#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"
class CDamageFont :
	public CGameObject
{
    friend class CScene;

protected:
    CDamageFont();
    CDamageFont(const CDamageFont& obj);
    virtual ~CDamageFont();

private:
    CSharedPtr<CBillboardComponent>    m_Billboard;

public:
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CDamageFont* Clone();
};

