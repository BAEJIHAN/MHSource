#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Image.h"
#include "Widget/ProgressBar.h"

class CPlayerHUD :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CPlayerHUD();
    CPlayerHUD(const CPlayerHUD& Window);
    virtual ~CPlayerHUD();

private:
    CSharedPtr<class CProgressBar>    m_HPBar;
    CSharedPtr<class CProgressBar>    m_SPBar;
    CSharedPtr<class CImage>          m_HPBarBack;   
    CSharedPtr<class CImage>          m_SPBarBack;
    class CPlayer*   m_Player;

    float m_ColorG;
    float m_ColorB;

    bool m_Inverse;

public:
    void SetHPBar(float HP);
    void SetSPBar(float SP);

    // 캐릭터 무기타입에 따라 UI 표시를 다르게해야함.

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void CreateWidgets(Vector2 WindowSize);

};

