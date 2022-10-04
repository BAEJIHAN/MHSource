#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"

class CHitBreathEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CHitBreathEffect();
    CHitBreathEffect(const CHitBreathEffect& obj);
    virtual ~CHitBreathEffect();

private:
    CSharedPtr<CBillboardComponent> m_Billboard;

    class CPlayer* m_Player;

    float   m_Time;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
};

