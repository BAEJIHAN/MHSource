
#include "ClickMouse.h"
#include "Widget/Image.h"

CClickMouse::CClickMouse()
{
}

CClickMouse::CClickMouse(const CClickMouse& window) :
    CWidgetWindow(window)
{
    m_MouseImage = FindWidget<CImage>("MouseImage");
}

CClickMouse::~CClickMouse()
{
}

void CClickMouse::Start()
{
}

bool CClickMouse::Init()
{
    if (!CWidgetWindow::Init())
        return false;

    SetSize(64.f, 64.f);

    m_MouseImage = CreateWidget<CImage>("MouseImage");

    m_MouseImage->SetTexture("MouseClick", TEXT("Mouse/ClickCursor.png"));
    m_MouseImage->SetSize(64.f, 64.f);

    return true;
}

void CClickMouse::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);

    if (m_Visibility)
        m_MouseImage->SetOpacity(1.f);

    else
        m_MouseImage->SetOpacity(0.f);
}

void CClickMouse::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);
}

void CClickMouse::Render()
{
    CWidgetWindow::Render();
}
