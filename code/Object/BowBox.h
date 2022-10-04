#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"

class CBowBox :
    public CGameObject
{
    friend class CScene;

protected:
    CBowBox();
    CBowBox(const CBowBox& obj);
    virtual ~CBowBox();

private:
    CSharedPtr<CStaticMeshComponent>    m_Mesh;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBowBox* Clone();
};

