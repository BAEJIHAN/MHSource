
#include "Engine.h"
#include "LoadingWindow.h"
#include "Scene/SceneManager.h"
#include "Widget/Image.h"
#include "Widget/ProgressBar.h"
#include "../Scene/MainSceneMode.h"

CLoadingWindow::CLoadingWindow() :
    m_Count(0),
    m_SwitchingTime(2.0f),
    m_SwitchingTimeAcc(0.f),
    m_Angle(0.f)
{
    m_vecLoadIcon.resize(3);
}

CLoadingWindow::~CLoadingWindow()
{
}

void CLoadingWindow::SetLoadingPercent(float Percent)
{
    m_LoadingBar->SetPercent(Percent);
}

bool CLoadingWindow::IsFadeOutCompleted()
{
    int Idx = m_Count - 1;

    if (Idx < 0)
    {
        Idx = 0;
    }

    float Opacity = m_vecLoadIcon[m_Count]->GetOpacity();

    if (Opacity > 0.1f)
    {
        return false;
    }

    else
    {
        return true;
    }
}

void CLoadingWindow::Start()
{
}

bool CLoadingWindow::Init()
{
    if (!CWidgetWindow::Init())
        return false;

    SetSize(1280.f, 720.f);

    m_BackImage = CreateWidget<CImage>("Back");
    m_LoadingBar = CreateWidget<CProgressBar>("LoadingBar");

    m_BackImage->SetSize(1280.f, 720.f);
    m_BackImage->SetZOrder(1);
    m_BackImage->SetTexture("LoadingBack", TEXT("LoadingBack.jpg"));
    m_BackImage->SetTextureTint(Vector4().Black);

    size_t Size = m_vecLoadIcon.size();

    for (size_t i = 0; i < Size; i++)
    {
        char Number[4] = "";
        sprintf_s(Number, "%d", (int)i);

        char Name[32] = "LoadingImage_";
        strcat_s(Name, Number);

        m_vecLoadIcon[i] = CreateWidget<CImage>(Name);

        m_vecLoadIcon[i]->SetSize(200.f, 200.f);
        m_vecLoadIcon[i]->SetPos(1280.f / 2.f, 720.f / 2.f);
        m_vecLoadIcon[i]->SetZOrder(4);
        m_vecLoadIcon[i]->SetFadeInTime(0.5f);
        m_vecLoadIcon[i]->SetFadeOutTime(0.5f);
        m_vecLoadIcon[i]->SetCenterPivot(true);
        m_vecLoadIcon[i]->SetFadeState(Widget_Fade_State::FadeIn);
        m_vecLoadIcon[i]->AddFadeCallback(Widget_Fade_State::FadeOut, this, &CLoadingWindow::Callbk);
        m_vecLoadIcon[i]->Enable(false);

        switch (i)
        {
        case 0:
            m_vecLoadIcon[i]->SetTexture("LoadImage1", TEXT("UI/Loading/LoadImage1.png"));
            break;
        case 1:
            m_vecLoadIcon[i]->SetTexture("LoadImage2", TEXT("UI/Loading/LoadImage2.png"));
            break;
        case 2:
            m_vecLoadIcon[i]->SetTexture("LoadImage3", TEXT("UI/Loading/LoadImage3.png"));
            break;
        }
    }

    m_LoadingBar->SetPos(0.f, -45.f);
    m_LoadingBar->SetSize(1280.f, 50.f);
    m_LoadingBar->SetTexture("LoadingBar", TEXT("HPBar.png"));
    m_LoadingBar->SetTextureTint(Vector4(0.48f, 0.78f, 0.98f, 1.0f));
    m_LoadingBar->SetZOrder(2);
    m_LoadingBar->SetPercent(0.f);

    m_vecLoadIcon[m_Count]->Enable(true);

    return true;
}

void CLoadingWindow::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);

    m_Angle += DeltaTime;

    m_SwitchingTimeAcc += DeltaTime;

    int Size = (int)m_vecLoadIcon.size();

    m_vecLoadIcon[1]->SetAngle(m_Angle * 75.f);

    if (m_SwitchingTimeAcc > m_SwitchingTime)
    {
        m_vecLoadIcon[m_Count]->SetFadeState(Widget_Fade_State::FadeOut);

        m_SwitchingTimeAcc = 0.f;
    }
}

void CLoadingWindow::PostUpdate(float DeltaTime)
{
    CWidgetWindow::PostUpdate(DeltaTime);
}

void CLoadingWindow::Render()
{
    CWidgetWindow::Render();
}

CLoadingWindow* CLoadingWindow::Clone()
{
    return new CLoadingWindow(*this);
}

void CLoadingWindow::Callbk()
{
    int Size = (int)m_vecLoadIcon.size();

    if (m_Count + 1 < Size)
    {
        m_Count++;
    }

    else
    {
        m_Count = 0;
    }


    int PrevIdx = -1;

    if (m_Count - 1 < 0)
    {
        PrevIdx = Size - 1;
    }

    else
    {
        PrevIdx = m_Count - 1;
    }

    m_vecLoadIcon[PrevIdx]->Enable(false);
    m_vecLoadIcon[m_Count]->Enable(true);
    m_vecLoadIcon[m_Count]->SetFadeState(Widget_Fade_State::FadeIn);
}
