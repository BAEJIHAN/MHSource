#pragma once
#include "Widget/Text.h"
#include "Widget/Button.h"
#include "Widget/WidgetWindow.h"
#include "Widget/CheckBox.h"
#include "Widget/Image.h"

class CQuestWindow :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CQuestWindow();
    CQuestWindow(const CQuestWindow& Window);
    virtual ~CQuestWindow();

    CSharedPtr<CImage> BackFrame;
    CSharedPtr<CText> QuestText1;
    CSharedPtr<CText> QuestText2;
    CSharedPtr<CButton> QuestButton1;
    CSharedPtr<CButton> QuestButton2;
    
    CSharedPtr<class CQuestSubWindow1>  pSubWindow1;
    CSharedPtr<class CQuestSubWindow2>  pSubWindow2;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void ButtonCallBack1();
    void ButtonCallBack2();

    void QuestAcept();
 
};

