#pragma once
#include "Widget/WidgetWindow.h"
class CCarvingRightWindow :
	public CWidgetWindow
{
    friend class CViewport;

protected:
    CCarvingRightWindow();
    CCarvingRightWindow(const CCarvingRightWindow& Window);
    virtual ~CCarvingRightWindow();

private:
    CSharedPtr<class CImage>        m_CarvingRight;
    CSharedPtr<class CImage>        m_BackImage;
    CSharedPtr<class CImage>        m_Icon;
    CSharedPtr<class CText>         m_MonsterName;
    class CPlayer* m_Player;
    Monster_Name    m_Monster;

    float       m_DestroyTime;
    bool        m_BoolNewUIEnable;      // 새로운 RightUI가 생길경우를 알려주기 위한 변수

public:
    void SetMonsterName(Monster_Name Name)
    {
        m_Monster = Name;
    }

    void SetNewUIEnable(bool Enable)
    {
        m_BoolNewUIEnable = Enable;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
};

