
#pragma once
#include "Widget/Text.h"
#include "Widget/Button.h"
#include "Widget/WidgetWindow.h"
#include "Widget/CheckBox.h"
#include "Widget/Image.h"

class CQuestSubWindow1 :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CQuestSubWindow1();
    CQuestSubWindow1(const CQuestSubWindow1& Window);
    virtual ~CQuestSubWindow1();

    CSharedPtr<CImage> BackFrame;
    CSharedPtr<CImage> BossImage;

    CSharedPtr<CImage> BackBar1;
   
    CSharedPtr<CImage> vespoidicon;
    CSharedPtr<CImage> jagrasicon;
    CSharedPtr<CImage> kestodonicon;

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

