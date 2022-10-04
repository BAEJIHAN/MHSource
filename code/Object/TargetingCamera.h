
#pragma once

#include "GameObject/GameObject.h"
#include "Component/CameraComponent.h"
#include "Component/Arm.h"

class CTargetingCamera :
    public CGameObject
{
public:
    CTargetingCamera();
    virtual ~CTargetingCamera();

private:
    CSharedPtr<CCameraComponent>        m_Camera;
    CSharedPtr<CArm>                    m_Arm;
    CSharedPtr<CGameObject>             m_TargetObj;

private:
    std::string m_TargetSocketName;
    Vector3     m_TargetOffset;
    Vector3     m_TargetPos;
    Vector3     m_CamFixedPos;
    Vector3     m_Dir;
    float       m_CamDist;
    float       m_CamRotSpeed;
    float       m_MoveSpeed;
    float       m_CameraAliveTime;
    float       m_CameraAliveTimeAcc;
    bool        m_IsBossDeadCam;
    bool        m_RotateCamStart;

public:
    // 추적할 오브젝트와 추적할 BoneSocket 이름을 입력.
    // 실제 카메라가 LootAt하는 대상은 BoneSocket의 Position.
    void SetLookAtTarget(CGameObject* Obj, const std::string& SocketName)
    {
        m_IsBossDeadCam = true;

        m_TargetObj = Obj;

        m_TargetSocketName = SocketName;
    }

    void SetLookAtTarget(Vector3 Pos, CGameObject* Obj)
    {
        m_TargetPos = Pos;

        m_TargetObj = Obj;

        Vector3 CamPos = GetWorldPos();

        //// 되도록이면 z전방으로 많이 이격되도록 하기위해 일부 Offset조정.
        //CamPos.x -= m_CamDist / 2.f;
        //CamPos.y -= m_CamDist / 2.f;

        Vector3 CamUpVector = GetRelativeAxis(AXIS::AXIS_Y);

        Matrix ViewMat;

        ViewMat.m = XMMatrixLookAtLH(CamPos.Convert(), m_TargetPos.Convert(), CamUpVector.Convert());

        if (m_Camera)
        {
            m_Camera->SetViewMatrix(ViewMat);
        }
    }

    // 기본 생존시간 4초
    void SetAliveTime(float Time)
    {
        m_CameraAliveTime = Time;
    }
    
    // LookAt Target에 Offset조정
    void SetLootAtOffset(Vector3 Offset)
    {
        m_TargetOffset = Offset;
    }
    
    // 배치될 CameraPos로부터 Offset조정
    // 기본 Distance 값 15.f
    void SetCameraDistance(float Dist)
    {
        m_CamDist = Dist;
    }

    // 기본속도 2.f.
    void SetMoveSpeed(float Speed)
    {
        m_MoveSpeed = Speed;
    }

    // Zero 벡터설정시, 움직이지 않음.
    void SetMoveDir(Vector3 Dir)
    {
        m_Dir = Dir;
    }

    void SetCameraFixedPos(Vector3 Pos)
    {
        m_CamFixedPos = Pos;
    }
   
    // 카메라 Rotation 시작하면 FadeOut Event호출.
    void RotationStart();


public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void LookAt(float DeltaTime);
    void Move(float DeltaTime);

};

