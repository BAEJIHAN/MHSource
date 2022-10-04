
#pragma once

#include "../Object/Monster.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"
#include "FSM.h"



class CBarnos :
    public CMonster
{
    friend class CScene;

protected:
    CBarnos();
    CBarnos(const CBarnos& obj);
    virtual ~CBarnos();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;
   
    CSharedPtr<CColliderBox3D>		ColliderHead;
    CSharedPtr<CColliderBox3D>		ColliderBody1;
    CSharedPtr<CColliderBox3D>		ColliderBody2;
    CSharedPtr<CColliderBox3D>		ColliderBody3;
    CSharedPtr<CColliderBox3D>		ColliderBody4;
    
    CSharedPtr<CColliderBox3D>	    ColliderRightWing1;
    CSharedPtr<CColliderBox3D>	    ColliderRightWing2;
    CSharedPtr<CColliderBox3D>	    ColliderRightWing3;
    CSharedPtr<CColliderBox3D>	    ColliderRightWing4;
    CSharedPtr<CColliderBox3D>	    ColliderRightWing5;

    CSharedPtr<CColliderBox3D>		ColliderLeftWing1;
    CSharedPtr<CColliderBox3D>		ColliderLeftWing2;
    CSharedPtr<CColliderBox3D>		ColliderLeftWing3;
    CSharedPtr<CColliderBox3D>		ColliderLeftWing4;
    CSharedPtr<CColliderBox3D>		ColliderLeftWing5;
        
    CSharedPtr<CColliderBox3D>		ColliderLeftFoot; 
    CSharedPtr<CColliderBox3D>		ColliderRightFoot;

    CSharedPtr<CColliderBox3D>		ColliderHeadAttack;
    CSharedPtr<CColliderBox3D>		ColliderLeftFootAttack;
    CSharedPtr<CColliderBox3D>		ColliderRightFootAttack;  

    CSharedPtr<CColliderBox3D>          ColliderCarving;

    CSharedPtr<CColliderBox3D>          ColliderSliding;

    CSharedPtr<class CSound> WingSound1;
    CSharedPtr<class CSound> WingSound2;

    float IdleTime;
    float MoveTime;
    float AttackTime;
      
    float ChaseIdleTime;
     
    bool IsAscending;
 
    class CPlayer* pPlayer;

    FSM<CBarnos> FSM;

public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBarnos* Clone();

private:


private: 
    
    Vector3 FindNextMovePoint();
    Vector3 FindPlayerAroundPos();
    void YPosCorrection();
    void FieldCollision(float DeltaTime);
    void CheckStuck();
    
private:

    void SetNotify();
    
    //notify
    void FlyNotify();
    void DeadNotify1();
    void DeadNotify2();
    void ToIdleNotify();
    void ScreamEndNotify();
    void AttackEndNotify();
    void GetHitEndNotify();
   
    //fsm
    //ChangeState 했을 때
    //Start는 첫 프레임에만 호출
    //Stay는 다른 상태로 ChangeState 할 때까지 매 프레임마다 호출
    //End는 다른 상태로 ChangeState 할 때 마지막 프레임에만 한 번 호출
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    



    void IDLEMOVEStart();
    void IDLEMOVEStay();
    void IDLEMOVEEnd();



    void CHASEStart();
    void CHASEStay();
    void CHASEEnd();

   


    void GETHITStart();
    void GETHITStay();
    void GETHITEnd();

    void SCREAMStart();
    void SCREAMStay();
    void SCREAMEnd();

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

private:       
	void OnCollisionBegin(const CollisionResult& result);
	void OnCollisionEnd(const CollisionResult& result);

    void AttackOnCollisionBegin(const CollisionResult& result);
    void AttackOnCollisionEnd(const CollisionResult& result);

    void SlidingOnCollisionBegin(const CollisionResult& result);
    void SlidingOnCollisionEnd(const CollisionResult& result);

//public:
//   int ColCount = 0;
//   Box3DInfo	FieldColInfo;
//   std::list<ColObj*> m_listCol;
};

