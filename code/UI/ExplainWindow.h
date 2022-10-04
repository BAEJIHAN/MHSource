#pragma once

#include "Widget/WidgetWindow.h"

class CExplainWindow :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CExplainWindow();
    CExplainWindow(const CExplainWindow& Window);
    virtual ~CExplainWindow();

private:
    CSharedPtr<class CImage>    m_BackImage;
    CSharedPtr<class CImage>    m_UnderImage;
    CSharedPtr<class CText>     m_Text;

public:
    void SetText(const TCHAR* Text);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void QuestClearPopUp();
    void PopUpEnd();

};

