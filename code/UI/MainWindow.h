#pragma once

#include "Widget/WidgetWindow.h"

class CMainWindow :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CMainWindow();
    CMainWindow(const CMainWindow& Window);
    virtual ~CMainWindow();

private:
    CSharedPtr<class CImage>                m_FadeImage;
    CSharedPtr<class CTargetingCamera>      m_RotCam;

private:
    Stage_Type      m_LoadType;
    bool            m_FadeSetStart;
    float           m_FadeSetTime;
    float           m_FadeSetTimeAcc;

public:
    void SetStageType(Stage_Type Type)
    {
        m_LoadType = Type;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void CameraDeploy();
    void LeavingMernosDeploy();

private:
    void FadeInStart();
    void FadeOutStart();

private:
    void FadeInCallback();
    void FadeOutCallback();

};

