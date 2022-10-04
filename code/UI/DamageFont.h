#pragma once

#include "Widget/WidgetWindow.h"

class CDamageFont :
	public CWidgetWindow
{
    friend class CViewport;

protected:
    CDamageFont();
    CDamageFont(const CDamageFont& Window);
    virtual ~CDamageFont();

private:
    CSharedPtr<class CNumber>    m_Damage;
    Vector3     m_HitPos;
    Vector3     m_Rotation;
    float       m_Distance;
    float       m_FontSizeX;
    float       m_FontSizeY;
    class CPlayer* m_Player;
    Coating_State  m_ArrowCoatingState;

    float       m_DeltaTime;
    float       m_ColorTimeR;
    float       m_ColorTimeG;
    float       m_ColorTimeB;
    float       m_ColorTimeA;
    Matrix      m_matArrowWorld;

public:
    void SetHitPos(const Vector3& HitPos)
    {
        m_HitPos = HitPos;
    }

    void SetDamageNumber(int Number);

    void SetArrowMat(const Matrix& Mat)
    {
        m_matArrowWorld = Mat;
    }

    void SetRotation(const Vector3& Rot)
    {
        m_Rotation = Rot;
    }

    void SetArrowState(const Coating_State& State)
    {
        m_ArrowCoatingState = State;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
};

