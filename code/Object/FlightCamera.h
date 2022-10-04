
#pragma once

#include "GameObject/GameObject.h"
#include "Component/CameraComponent.h"
#include "Component/Arm.h"

class CFlightCamera :
    public CGameObject
{
    friend class CScene;

protected:
    CFlightCamera();
    CFlightCamera(const CFlightCamera& obj);
    virtual ~CFlightCamera();

private:
    CSharedPtr<CCameraComponent>        m_Camera;
    CSharedPtr<CArm>                    m_Arm;

private:
    Vector2     m_MouseMove;
    POINT       m_CenterPoint;
    float       m_FlightSpeed;
    bool        m_ESCButton;

public:
    void SetCameraSpeed(float Speed)
    {
        m_FlightSpeed = Speed;
    }
    
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CFlightCamera* Clone();
    virtual void Render();

private:
    void MoveFront(float DeltaTime);
    void MoveBack(float DeltaTime);
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);
    void RotationX(float DeltaTime);

private:
    void ESC(float DeltaTime);

};

