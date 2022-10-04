#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/PaperBurnComponent.h"

class CBowVfx :
    public CGameObject
{
    friend class CScene;

protected:
    CBowVfx();
    CBowVfx(const CBowVfx& obj);
    virtual ~CBowVfx();

private:
    CSharedPtr<CStaticMeshComponent>    m_VFXMesh;
    CSharedPtr<CPaperBurnComponent>   m_PaperBurn1;
    CSharedPtr<CPaperBurnComponent>   m_PaperBurn2;
    CSharedPtr<CPaperBurnComponent>   m_PaperBurn3;

    class CPlayer* m_Player;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBowVfx* Clone();

private:
    void EndNotify();
};

