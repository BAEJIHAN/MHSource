
#include "NormalMouse.h"
#include "Widget/Image.h"

CNormalMouse::CNormalMouse()
{
}

CNormalMouse::CNormalMouse(const CNormalMouse& window) :
	CWidgetWindow(window)
{
	m_MouseImage = FindWidget<CImage>("MouseImage");
}

CNormalMouse::~CNormalMouse()
{
}

void CNormalMouse::Start()
{
}

bool CNormalMouse::Init()
{
    if (!CWidgetWindow::Init())
        return false;

    SetSize(64.f, 64.f);

    m_MouseImage = CreateWidget<CImage>("MouseImage");

    m_MouseImage->SetTexture("MouseNormal", TEXT("Mouse/NormalCursor.png"));
    m_MouseImage->SetSize(64.f, 64.f);
    m_MouseImage->SetOpacity(0.f);

    


    return true;
}

void CNormalMouse::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);

    if(m_Visibility)
        m_MouseImage->SetOpacity(1.f);

    else
        m_MouseImage->SetOpacity(0.f);

}

void CNormalMouse::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);
}

void CNormalMouse::Render()
{
    CWidgetWindow::Render();
}
