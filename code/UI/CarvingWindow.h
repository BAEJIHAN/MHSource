#pragma once

#include "Widget/WidgetWindow.h"

class CCarvingWindow :
	public CWidgetWindow
{
    friend class CViewport;

protected:
    CCarvingWindow();
    CCarvingWindow(const CCarvingWindow& Window);
    virtual ~CCarvingWindow();

private:
    CSharedPtr<class CImage>        m_CarvingCenter;
    CSharedPtr<class CImage>        m_CarvingEffect;    // CenterUI ÁÖÀ§ ºû³ª´Â Image
    CSharedPtr<class CImage>        m_FButtonImage;
    CSharedPtr<class CImage>        m_Icon;
    CSharedPtr<class CText>         m_MonsterName;
    class CPlayer* m_Player;
    Monster_Name    m_Monster;

    bool            m_CenterUIFadeOut;
    float           m_FadeOpacity;

public:
    void SetMonsterName(Monster_Name Name)
    {
        m_Monster = Name;
    }

    void SetUIFadeEnable(bool Enable)
    {
        m_CenterUIFadeOut = Enable;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
};

