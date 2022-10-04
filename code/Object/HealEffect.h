#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CHealEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CHealEffect();
    CHealEffect(const CHealEffect& obj);
    virtual ~CHealEffect();

private:
    CSharedPtr<CBillboardComponent>    m_Billboard;
    CSharedPtr<CBillboardComponent>    m_Billboard1;
    class CPlayer* m_Player;

    bool    m_CollisionEnable;
    float   m_Time;

    bool    m_CollisionObject;

public:
    void SetObjectEnable(bool Enable)
    {
        m_CollisionObject = Enable;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CHealEffect* Clone();

private:
    void SetEndNotify();
};

