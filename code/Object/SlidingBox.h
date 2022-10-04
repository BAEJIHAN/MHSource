#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

class CSlidingBox :
    public CGameObject
{
    friend class CScene;

protected:
    CSlidingBox();
    CSlidingBox(const CSlidingBox& obj);
    virtual ~CSlidingBox();

private:
    CSharedPtr<CColliderBox3D>		m_ColliderBox;
    CSharedPtr<CStaticMeshComponent>    m_Mesh;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CSlidingBox* Clone();
};

