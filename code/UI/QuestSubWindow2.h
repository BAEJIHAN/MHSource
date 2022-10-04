#pragma once
#include "Widget/Text.h"
#include "Widget/Button.h"
#include "Widget/WidgetWindow.h"
#include "Widget/CheckBox.h"
#include "Widget/Image.h"

class CQuestSubWindow2 :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CQuestSubWindow2();
    CQuestSubWindow2(const CQuestSubWindow2& Window);
    virtual ~CQuestSubWindow2();

    CSharedPtr<CImage> BackFrame;
    CSharedPtr<CImage> BossImage;

    CSharedPtr<CImage> BackBar1;

    CSharedPtr<CImage> barnosicon;

    CSharedPtr<CText> BossText;
    CSharedPtr<CText> StartText;
    CSharedPtr<CText> MonsterText;

    CSharedPtr<CButton> StartButton;

    class CPlayer* m_Player;


public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void ButtonCallBack();
};

