#pragma once

#include "GameObject/GameObject.h"
#include "Component/StaticMeshComponent.h"
#include "Component/ColliderBox3D.h"

enum class DragonArrow_State
{
    None,
    Charging,
    Flying,
    Max
};


class CDragonArrow :
    public CGameObject
{
    friend class CScene;

protected:
    CDragonArrow();
    CDragonArrow(const CDragonArrow& obj);
    virtual ~CDragonArrow();

private:
    CSharedPtr<CStaticMeshComponent>    m_Mesh;
    CSharedPtr<CColliderBox3D>		m_ColliderBox;
    float       m_DragonArrowSpeed;
    float		m_DragonArrowDist;			// 화살이 날아갈 거리
    DragonArrow_State  m_DragonArrowState;
    class CPlayer* m_Player;
    float       m_Time;
    bool        m_Collision;
    float       m_AttackTime;
    CollisionResult m_CollisionResult;
    int         m_DamageCount;

public:
    DragonArrow_State GetDragonArrowState() const
    {
        return m_DragonArrowState;
    }

    void SetArrowState(DragonArrow_State State)
    {
        m_DragonArrowState = State;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CDragonArrow* Clone();

private:
    void CollisionBegin(const CollisionResult& Result);

private:
    void SetDamageFunc(const CollisionResult& Result);
};

