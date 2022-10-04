
#pragma once

#include "../Object/Monster.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"
#include "FSM.h"

class CKestodon :
    public CMonster
{
    friend class CScene;

protected:
    CKestodon();
    CKestodon(const CKestodon& obj);
    virtual ~CKestodon();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;
  
    CSharedPtr<CColliderBox3D>          ColliderHead;
    CSharedPtr<CColliderBox3D>          ColliderUpperBody;
    CSharedPtr<CColliderBox3D>          ColliderLowerBody;
    CSharedPtr<CColliderBox3D>          ColliderLowerLowerBody;
    CSharedPtr<CColliderBox3D>          ColliderTail;
    CSharedPtr<CColliderBox3D>          ColliderLeftLeg;
    CSharedPtr<CColliderBox3D>          ColliderRightLeg;
    CSharedPtr<CColliderBox3D>          ColliderHeadAttack;
  
    CSharedPtr<CColliderBox3D>          ColliderCarving;

    CSharedPtr<CColliderBox3D>          ColliderSliding;

    CSharedPtr<class CSound> AttackSound;

    float IdleTime;
    float MoveTime;
    float AttackTime;
    float DodgeTime;
    
    class CPlayer* pPlayer;
    
    bool IsDodged;
    bool IsCharging;
    
    FSM<CKestodon> FSM;

public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CKestodon* Clone();

private:
    Vector3 FindNextMovePoint();
    Vector3 FindPlayerAroundPos();
    void TakeNestAction();
    void TakeAttack();
    void FieldCollision(float DeltaTime);
    void CheckStuck();

private:
    
    void SetNotify();

    //notify
    void Attack1EndNotify();
    void Attack2EndNotify();
    void Attack3EndNotify();
    
    void ToIdleNotify();
    void ScreamEndNotify();
    void GetHitEndNotify();
    
    
    

    //fsm
    //ChangeState 했을 때
    //Start는 첫 프레임에만 호출
    //Stay는 다른 상태로 ChangeState 할 때까지 매 프레임마다 호출
    //End는 다른 상태로 ChangeState 할 때 마지막 프레임에만 한 번 호출
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void MOVEStart();
    void MOVEStay();
    void MOVEEnd();

    void ATTACK1Start();
    void ATTACK1Stay();
    void ATTACK1End();

    void ATTACK2Start();
    void ATTACK2Stay();
    void ATTACK2End();

    void GETHITStart();
    void GETHITStay();
    void GETHITEnd();

    void SCREAMStart();
    void SCREAMStay();
    void SCREAMEnd();

    void DODGEStart();
    void DODGEStay();
    void DODGEEnd();



    void DEATHStart();
    void DEATHStay();
    void DEATHEnd();

    void FADEOUTStart();
    void FADEOUTStay();
    void FADEOUTEnd();

private:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

    void AttackOnCollisionBegin(const CollisionResult& result);
    void AttackOnCollisionEnd(const CollisionResult& result);

    void SlidingOnCollisionBegin(const CollisionResult& result);
    void SlidingOnCollisionEnd(const CollisionResult& result);


};

