#pragma once

#include "GameObject/GameObject.h"
#include "Component/DecalComponent.h"

class CBurnedDecal :
    public CGameObject
{
    friend class CScene;

protected:
    CBurnedDecal();
    CBurnedDecal(const CBurnedDecal& obj);
    virtual ~CBurnedDecal();

private:
    CSharedPtr<CDecalComponent> m_Decal;

public:
    void SetFadeInTime(float Time)
    {
        m_Decal->SetFadeInTime(Time);
    }

    void SetFadeOutTime(float Time)
    {
        m_Decal->SetFadeOutTime(Time);
    }

    void SetDuration(float Time)
    {
        m_Decal->SetDuration(Time);
    }



public:
    void PresetToExplosive();
    void PresetToGroundBurnt();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
};

