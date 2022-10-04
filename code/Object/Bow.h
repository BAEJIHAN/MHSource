#pragma once

#include "GameObject/GameObject.h"
#include "Component/AnimationMeshComponent.h"

class CBow :
    public CGameObject
{
    friend class CScene;

protected:
    CBow();
    CBow(const CBow& obj);
    virtual ~CBow();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;
    class CRimLightConstantBuffer* m_CBuffer;

    class CPlayer* m_Player;

    float m_Time;
    float m_ColorR;
    float m_ColorG;
    float m_ColorB;
    Vector3 m_EmissiveColor;
    
    int m_Count;

    bool m_Inverse;
    bool m_LoopEnable;
    bool m_FirstCharging;
    bool m_Charging1To2;

public:
    void SetRimLightEnable(bool Enable);
    void SetCount(int Count)
    {
        m_Count = Count;
    }

    void SetFirstCharg(bool Enable)
    {
        m_FirstCharging = Enable;
    }

    void SetCharging1To2(bool Enable)
    {
        m_Charging1To2 = Enable;
    }
    void SetLoopEnable(bool Enable)
    {
        m_LoopEnable = Enable;
    }

    void SetTime(float Time)
    {
        m_Time = Time;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBow* Clone();


    void SetEndNotify();

private:
    void BowChargingStartEndNotify();
};

