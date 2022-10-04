#pragma once

#include "Widget/WidgetWindow.h"

class CStartWindow :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CStartWindow();
    virtual ~CStartWindow();

private:
    CSharedPtr<class CImage>    m_BackgroundImage;
    CSharedPtr<class CImage>    m_EmblemImage;
    CSharedPtr<class CImage>    m_LogoImage;
    CSharedPtr<class CImage>    m_LightEffectImage;
    CSharedPtr<class CImage>    m_EyeLightImage;
    CSharedPtr<class CImage>    m_TextBackImage;
    CSharedPtr<class CText>     m_PressText;
    CSharedPtr<class CImage>    m_ButtonFocusImage;

private:
    int  m_FocusingIndex;

private:
    bool    m_TitleStart;
    bool    m_LightStart;
    bool    m_PressStart;
    bool    m_LoadingStart;

private:
    std::vector<CSharedPtr<class CButton>> m_vecMenuButton; // 아이템/장비, 옵션 등의 버튼
    std::vector<CSharedPtr<class CText>>   m_vecButtonText;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void InitWidgets(Vector2 WindowSize);
    void TrackingButton();
    
    // CallbackFunction
private:
    void PressClickCallback();
    void StartButtonCallback();
    void OptionButtonCallback();
    void ExitButtonCallback();



};

