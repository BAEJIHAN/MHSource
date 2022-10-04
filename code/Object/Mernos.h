

#pragma once

#include "../Object/Monster.h"
#include "Component/StaticMeshComponent.h"
#include "Component/AnimationMeshComponent.h"
#include "Component/ColliderBox3D.h"
#include "FSM.h"

class CMernos :
    public CMonster
{
    friend class CScene;

protected:
    CMernos();
    CMernos(const CMernos& obj);
    virtual ~CMernos();

private:
    CSharedPtr<CAnimationMeshComponent>    m_Mesh;


    float ActTime;
    Vector3 DestMovePoint;
    class CPlayer* pPlayer;
    float FadeOpacity;

    //플레이어 FSM
    FSM<CMernos> FSM;
    float PlayerTime;

    Check_Type m_CheckType;
    Vector3     m_MoveStartPoint;

public:
    void SetCheckToPointType(const Check_Type& Type);

public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CMernos* Clone();

private:


private:
  
    void YPosCorrection();

private:

    void SetNotify();

    //notify
    void PickUpNotify();
    void AscendNotify();


    //fsm
    //ChangeState 했을 때
    //Start는 첫 프레임에만 호출
    //Stay는 다른 상태로 ChangeState 할 때까지 매 프레임마다 호출
    //End는 다른 상태로 ChangeState 할 때 마지막 프레임에만 한 번 호출
    void IDLEStart();
    void IDLEStay();
    void IDLEEnd();

    void DESCENDStart();
    void DESCENDStay();
    void DESCENDEnd();

    void PICKUPStart();
    void PICKUPStay();
    void PICKUPEnd();

    void ASCENDStart();
    void ASCENDStay();
    void ASCENDEnd();

    void ARRIVEStart();
    void ARRIVEStay();
    void ARRIVEEnd();

    void LEAVEStart();
    void LEAVEStay();
    void LEAVEEnd();

    void FADEOUTStart();
    void FADEOUTStay();
    void FADEOUTEnd();


private:

};

