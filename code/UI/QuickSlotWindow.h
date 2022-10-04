#pragma once

#include "Widget/WidgetWindow.h"

class CQuickSlotWindow :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CQuickSlotWindow();
    CQuickSlotWindow(const CQuickSlotWindow& Window);
    virtual ~CQuickSlotWindow();

private:
    CSharedPtr<class CImage>          m_WindowFrame;
    CSharedPtr<class CImage>          m_SelectedBackImage;
    CSharedPtr<class CImage>          m_UsedBotttleImage;
    CSharedPtr<class CImage>          m_UsedBotttleFrameImage;
    CSharedPtr<class CImage>          m_UsedBotttleFlashImage;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void CreateWidgets(Vector2 WindowSize);
};

