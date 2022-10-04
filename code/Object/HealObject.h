#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/BillboardComponent.h"
#include "Component/ColliderBox3D.h"

class CHealObject :
    public CGameObject
{
    friend class CScene;

protected:
    CHealObject();
    CHealObject(const CHealObject& obj);
    virtual ~CHealObject();

private:
    CSharedPtr<CBillboardComponent>    m_Billboard;
    CSharedPtr<CColliderBox3D>		m_ColliderBox;

    bool    m_DestroyEnable;
    float   m_Opacity;

public:
    void SetDestroyEnable(bool Enable)
    {
        m_DestroyEnable = Enable;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CHealObject* Clone();

private:
    void CollisionBegin(const CollisionResult& Result);
};

