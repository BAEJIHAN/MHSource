#pragma once

#include "../Object/Monster.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"
#include "FSM.h"

class CJagras :
    public CMonster
{
    friend class CScene;

protected:
    CJagras();
    CJagras(const CJagras& obj);
    virtual ~CJagras();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;
   
    CSharedPtr<CColliderBox3D>          ColliderHead;
    CSharedPtr<CColliderBox3D>          ColliderBody1;
    CSharedPtr<CColliderBox3D>          ColliderBody2;
    CSharedPtr<CColliderBox3D>          ColliderBody3;
    CSharedPtr<CColliderBox3D>          ColliderBody4;
    CSharedPtr<CColliderBox3D>          ColliderBody5;
    CSharedPtr<CColliderBox3D>          ColliderTail1;
    CSharedPtr<CColliderBox3D>          ColliderTail2;
    CSharedPtr<CColliderBox3D>          ColliderRightFrontLeg;
    CSharedPtr<CColliderBox3D>          ColliderLeftFrontLeg;
    CSharedPtr<CColliderBox3D>          ColliderRightBackLeg;
    CSharedPtr<CColliderBox3D>          ColliderLeftBackLeg;

    CSharedPtr<CColliderBox3D>          ColliderHeadAttack;
    CSharedPtr<CColliderBox3D>          ColliderLeftArmAttack;
    CSharedPtr<CColliderBox3D>          ColliderRightArmAttack;

    CSharedPtr<CColliderBox3D>          ColliderCarving;

    CSharedPtr<CColliderBox3D>          ColliderSliding;

    float IdleTime;   
    
    float MoveTime;
    float AttackTime;   
    float DodgeTime; 
       
    class CPlayer* pPlayer;   

    bool IsDodged;
    bool Attack1Move; 

 
    //플레이어 FSM
    FSM<CJagras> FSM;

public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CJagras* Clone();

private:
    Vector3 FindNextMovePoint();
    Vector3 FindPlayerAroundPos();
    void TakeNestAction();
    void TakeAttack();
    void FieldCollision(float DeltaTime);
    void CheckStuck();
private:
    
private:
    
    void SetNotify();

    //notify
    void Attack1EndNotify();
    void Attack2EndNotify();
    void Attack3EndNotify();   
 
    void RollEndNotify();
   
    void ScreamEndNotify();
    void AttackEndNotify();
    void GetHitEndNotify();


  //FSM
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void MOVEStart();
    void MOVEStay();
    void MOVEEnd();

    void GETHITStart();
    void GETHITStay();
    void GETHITEnd();

    void SCREAMStart();
    void SCREAMStay();
    void SCREAMEnd();

    void DODGEStart();
    void DODGEStay();
    void DODGEEnd();

    void ATTACK1Start();
    void ATTACK1Stay();
    void ATTACK1End();

    void ATTACK2Start();
    void ATTACK2Stay();
    void ATTACK2End();

    void ATTACK3Start();
    void ATTACK3Stay();
    void ATTACK3End();

    void DEATHStart();
    void DEATHStay();
    void DEATHEnd();

    void FADEOUTStart();
    void FADEOUTStay();
    void FADEOUTEnd();

public:
    void OnCollisionBegin(const CollisionResult& result);
    void OnCollisionEnd(const CollisionResult& result);

    void AttackOnCollisionBegin(const CollisionResult& result);
    void AttackOnCollisionEnd(const CollisionResult& result);

    void SlidingOnCollisionBegin(const CollisionResult& result);
    void SlidingOnCollisionEnd(const CollisionResult& result);
};

