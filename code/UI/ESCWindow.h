#pragma once

#include "Widget/WidgetWindow.h"

class CESCWindow :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CESCWindow();
    virtual ~CESCWindow();

public:
    virtual void FadeDestroy();

private:
    std::vector<CSharedPtr<class CButton>> m_vecMenuIconButton; // 아이템/장비, 옵션 등의 버튼
    std::vector<CSharedPtr<class CButton>>  m_vecSystemButton; // 옵션, 뷰모드, 저장, 종료등의 버튼
    std::vector<CSharedPtr<class CText>>   m_vecButtonText;
    CSharedPtr<class CImage>    m_TitleImage;
    CSharedPtr<class CImage>    m_TitleLine;
    CSharedPtr<class CImage>    m_ButtonBackImage;
    CSharedPtr<class CImage>    m_ButtonFocusImage;

private:
    int  m_CurrMenuIndex;
    int  m_FocusingIndex;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void CreateWidgets(Vector2 WindowSize);
    void TrackingButton();
    void SetExplainText(int ButtonIndex);


private:
    void MenuIconClickCallback();
    void ExitCallback();
    void OptionCallback();

private:
    void SetSystemMenu();
};

