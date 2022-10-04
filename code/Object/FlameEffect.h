#pragma once

#include "GameObject/GameObject.h"
#include "Component/BillboardComponent.h"
#include "Component/LightComponent.h"
#include "Component/ColliderBox3D.h"
class CFlameEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CFlameEffect();
    CFlameEffect(const CFlameEffect& obj);
    virtual ~CFlameEffect();

private:
    CSharedPtr<CBillboardComponent> m_Billboard;
    CSharedPtr<CLightComponent>     m_Light;
    CSharedPtr<CColliderBox3D>      m_ColliderBox;

private:
    Vector3 m_Dir;
    float   m_Dist;
    float   m_Speed;
    bool    m_Moving;
    bool    m_Explosive;

public:
    void SetExplosive(bool bEnable)
    {
        m_Explosive = bEnable;
    }

public:
    void Move(Vector3 Dir, float Dist = 50.f, float Speed = 130.f);

    // 둘중 적합한 안으로 구현
    // 1. 몬스터 Y값을 기준으로 Billboard에서 Landscape에 Decal생성여부를 판정.
    // 2. 브레스 타임이 끝나면 Decal생성할지

    // Box3DCollider 생성
    // 충돌체크
    // 1. LandScape의 경우 <<< 바로 밑의 위치에 Decal 생성(충돌해야하나?)
    // 2. Player의 경우 <<< Opacity 값에 따라 화염피해 설정여부를 판단.


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CFlameEffect* Clone();

private:
    void CreateEffects();

private:
    void OnCollisionBegin(const CollisionResult& result);

};

