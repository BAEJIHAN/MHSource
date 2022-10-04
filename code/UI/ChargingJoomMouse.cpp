
#include "ChargingJoomMouse.h"
#include "Component/WidgetComponent.h"
#include "../Object/Player.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

CChargingJoomMouse::CChargingJoomMouse()    :
    m_Time(200.f),
    m_Count(0),
    m_Player(nullptr)
{
}

CChargingJoomMouse::CChargingJoomMouse(const CChargingJoomMouse& window) :
    CWidgetWindow(window)
{
    m_MouseImage = FindWidget<CImage>("MouseImage");
}

CChargingJoomMouse::~CChargingJoomMouse()
{
}

void CChargingJoomMouse::Start()
{
}

bool CChargingJoomMouse::Init()
{
    if (!CWidgetWindow::Init())
        return false;

    SetSize(200.f, 200.f);

    m_MouseImage = CreateWidget<CImage>("MouseImage");
    m_ChargingImage = CreateWidget<CImage>("ChargingImage");

    m_MouseImage->SetTexture("ChargingMouse", TEXT("Mouse/ChargingJoomIcon.png"));
    m_MouseImage->SetSize(100.f, 50.f);

    m_ChargingImage->SetTexture("Charging", TEXT("Mouse/ChargingIcon.png"));
    m_ChargingImage->SetSize(m_Time, m_Time);

    m_MouseImage->SetPos(m_MouseImage->GetPos().x - 50.f, m_MouseImage->GetPos().y + 180.f);
    m_ChargingImage->SetPos(m_MouseImage->GetPos().x - m_ChargingImage->GetSize().x / 2.f + 50.f, 
        m_MouseImage->GetPos().y - m_ChargingImage->GetSize().y / 2.f + 25.f);

    return true;
}

void CChargingJoomMouse::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);

    // 마우스 위젯을 씬보다 먼저 생성하기때문에 이닛에서 찾을 수 없음
    // 그래서 업데이트쪽에서 탐색을하는데 null일때만 찾도록 설정을 함(1번 찾으면 그 이후로 탐색 안함)
    
    m_Player = dynamic_cast<CPlayer*>(CSceneManager::GetInst()->GetPlayerObject());

    bool ChargingEnable = false;
    int ChargingCount = 0;
    float ChargingTime = 0.f;

    if (m_Player)
    {
        ChargingEnable = m_Player->GetChargingEnable();
        ChargingCount = m_Player->GetChargingCount();
        ChargingTime = m_Player->GetChargingTime();
    }

    if (ChargingEnable)
    {
        if (ChargingCount < 2)
        {
           // m_Time -= DeltaTime * 210.f;
            m_ChargingImage->SetSize(ChargingTime, ChargingTime);
            m_ChargingImage->SetPos(m_MouseImage->GetPos().x - m_ChargingImage->GetSize().x / 2.f + 50.f,
                m_MouseImage->GetPos().y - m_ChargingImage->GetSize().y / 2.f + 25.f);
            m_ChargingImage->SetImageVisibillty(true);
        }
        else
        {
            m_ChargingImage->SetImageVisibillty(false);
        }
    }
    else
    {
        m_ChargingImage->SetImageVisibillty(false);
    }

    if (m_Visibility)
    {
        m_MouseImage->SetOpacity(1.f);
        m_ChargingImage->SetOpacity(1.f);
    }

    else
    {
        m_MouseImage->SetOpacity(0.f);
        m_ChargingImage->SetOpacity(0.f);
    }
}

void CChargingJoomMouse::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);
}

void CChargingJoomMouse::Render()
{
    CWidgetWindow::Render();
}
