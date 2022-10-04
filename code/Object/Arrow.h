#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

enum class Arrow_State
{
    None,
    Charging,
    Flying,
    Max
};

class CArrow :
    public CGameObject
{
    friend class CScene;

protected:
    CArrow();
    CArrow(const CArrow& obj);
    virtual ~CArrow();

private:
    CSharedPtr<CStaticMeshComponent>    m_Mesh;
    CSharedPtr<CColliderBox3D>		m_ColliderBox;
    float       m_ArrowSpeed;
    float		m_ArrowDist;			// 화살이 날아갈 거리
    float       m_Angle;
    bool        m_DestroyEnable;
    Arrow_State  m_ArrowState;
    class CPlayer* m_Player;
    class CArm* m_Arm;
    Coating_State   m_CoatingState;

    class CNormalArrowParticle* m_NormalParticle;
    class CStrongArrowParticle* m_StrongParticle;

    bool    m_ProduceEnable;

public:
    Arrow_State GetArrowState() const
    {
        return m_ArrowState;
    }

    void SetArrowState(Arrow_State State)
    {
        m_ArrowState = State;
    }

    void SetArrowAngle(float Angle)
    {
        m_Angle = Angle;
    }

    void SetDestroyEnabel(bool Enable)
    {
        m_DestroyEnable = Enable;
    }

    Coating_State GetArrowCoatingState()  const
    {
        return m_CoatingState;
    }

public:
    void SetArrowCoatingState(const Coating_State& State)
    {
        m_CoatingState = State;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CArrow* Clone();

private:
    void CollisionBegin(const CollisionResult& Result);

private:
    void CreateParticleFunc(const Coating_State& State);
    void DestroyParticleFunc();
    void SetDamageFunc(const CollisionResult& Result);
};

