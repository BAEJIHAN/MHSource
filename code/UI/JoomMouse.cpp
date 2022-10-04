
#include "JoomMouse.h"
#include "Component/WidgetComponent.h"

CJoomMouse::CJoomMouse()
{
}

CJoomMouse::CJoomMouse(const CJoomMouse& window) :
    CWidgetWindow(window)
{
    m_MouseImage = FindWidget<CImage>("MouseImage");
}

CJoomMouse::~CJoomMouse()
{
}

void CJoomMouse::Start()
{
}

bool CJoomMouse::Init()
{
    if (!CWidgetWindow::Init())
        return false;

    SetSize(64.f, 64.f);

    m_MouseImage = CreateWidget<CImage>("MouseImage");

    m_MouseImage->SetTexture("MouseJoom", TEXT("Mouse/JoomIcon.png"));
    m_MouseImage->SetSize(32.f, 32.f);

    Vector2 TextureSize;

    TextureSize.x = (float)m_MouseImage->GetInfo().Texture->GetWidth();
    TextureSize.y = (float)m_MouseImage->GetInfo().Texture->GetHeight();


    Vector2 ConvertPos = TextureSize - m_MouseImage->GetSize();

    m_MouseImage->SetPos(m_MouseImage->GetPos().x - 16.f, m_MouseImage->GetPos().y + TextureSize.y);

    return true;
}

void CJoomMouse::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);

    if (m_Visibility)
    {
        m_MouseImage->SetOpacity(1.f);
    }

    else
    {
        m_MouseImage->SetOpacity(0.f);
    }
}

void CJoomMouse::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);
}

void CJoomMouse::Render()
{
    CWidgetWindow::Render();
}
