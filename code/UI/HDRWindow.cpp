#include "HDRWindow.h"
#include "Scene/Viewport.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Input.h"
#include "HDR.h"
CHDRWindow::CHDRWindow()
{
	SetTypeID<CHDRWindow>();
}

CHDRWindow::CHDRWindow(const CHDRWindow& Window) :
	CWidgetWindow(Window)
{
}

CHDRWindow::~CHDRWindow()
{
}

void CHDRWindow::Start()
{
	CWidgetWindow::Start();
}

bool CHDRWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	Resolution r = CEngine::GetInst()->GetRS();
	Vector2 rs((float)r.Width, (float)r.Height);
	SetPos(rs.x / 2 + 100.f, rs.y / 2 - 200.f);

	SetSize(450.f, 500.f);

	SetZOrder(10);

	BackFrame = CreateWidget<CImage>("BackFrame");
	BackFrame->SetTexture("Back", TEXT("UI/WindowBack.png"));
	BackFrame->SetSize(450.f, 500.f);
	BackFrame->SetPos(0.f, 0.f);
	BackFrame->SetZOrder(0);


	CheckBox = CreateWidget<CCheckBox>("CheckBox");
	CheckBox->SetPos(200.f, 420.f);
	CheckBox->SetSize(120.f, 32.f);
	CheckBox->SetTexture(false, "CheckBoxOff", TEXT("UI/CheckBoxOff.png"));
	CheckBox->SetTexture(true, "CheckBoxOn", TEXT("UI/CheckBoxOn.png"));

	CheckBox->SetClickCallback<CHDRWindow>(this, &CHDRWindow::CheckBoxCallBack);
	CheckBox->SetZOrder(10);

	HDRButtonText = CreateWidget<CText>("HDRButtonText");
	HDRButtonText->SetSize(120.f, 20.f);
	HDRButtonText->SetPos(20.f, 420.f);
	HDRButtonText->SetText(TEXT("HDR Enable"));
	HDRButtonText->SetColor(255.f, 255.f, 255.f);
	HDRButtonText->SetZOrder(1);

	GreyText = CreateWidget<CText>("GreyText");
	GreyText->SetZOrder(1);
	GreyText->SetSize(60.f, 20.f);
	GreyText->SetPos(20.f, 360.f);
	GreyText->SetText(TEXT("Grey"));
	GreyText->SetColor(255.f, 255.f, 255.f);
	GreyText->SetZOrder(1);

	WhiteText = CreateWidget<CText>("WhiteText");
	WhiteText->SetZOrder(1);
	WhiteText->SetSize(60.f, 20.f);
	WhiteText->SetPos(20.f, 300.f);
	WhiteText->SetText(TEXT("White"));
	WhiteText->SetColor(255.f, 255.f, 255.f);
	WhiteText->SetZOrder(1);

	BloomScaleText = CreateWidget<CText>("BloomScaleText");
	BloomScaleText->SetZOrder(1);
	BloomScaleText->SetSize(110, 20.f);
	BloomScaleText->SetPos(20.f, 240.f);
	BloomScaleText->SetText(TEXT("BloomScale"));
	BloomScaleText->SetColor(255.f, 255.f, 255.f);
	BloomScaleText->SetZOrder(1);

	BloomThresholdText = CreateWidget<CText>("BloomThresholdText");
	BloomThresholdText->SetZOrder(1);
	BloomThresholdText->SetSize(150, 20.f);
	BloomThresholdText->SetPos(20.f, 180.f);
	BloomThresholdText->SetText(TEXT("BloomThreshold"));
	BloomThresholdText->SetColor(255.f, 255.f, 255.f);
	BloomThresholdText->SetZOrder(1);

	NearStartText = CreateWidget<CText>("NearStartText");
	NearStartText->SetZOrder(1);
	NearStartText->SetSize(90.f, 20.f);
	NearStartText->SetPos(20.f, 120.f);
	NearStartText->SetText(TEXT("NearStart"));
	NearStartText->SetColor(255.f, 255.f, 255.f);
	NearStartText->SetZOrder(1);

	FarStartText = CreateWidget<CText>("FarStartText");
	FarStartText->SetZOrder(1);
	FarStartText->SetSize(80.f, 20.f);
	FarStartText->SetPos(20.f, 60.f);
	FarStartText->SetText(TEXT("FarStart"));
	FarStartText->SetColor(255.f, 255.f, 255.f);
	FarStartText->SetZOrder(1);



	GreyBar = CreateWidget<CImage>("MiddleGreyBar");
	GreyBar->SetTexture("GreyBar", TEXT("UI/SliderBack.png"));
	GreyBar->SetSize(167.f, 8.f);
	GreyBar->SetPos(200.f, 365.f);
	GreyBar->SetZOrder(1);


	GreySlider = CreateWidget<CGreySlider>("GreySlider");
	GreySlider->SetTexture("Slider", TEXT("UI/Slider.png"));
	GreySlider->SetSize(30.f, 30.f);
	//GreySlider->SetPos(200.f, 353.f);
	GreySlider->SetZOrder(11);
	GreySlider->SetMinMax(185.f, 352.f);
	GreySlider->SetInitPos(CHDR::GetInst()->GetGrey());


	WhiteBar = CreateWidget<CImage>("WhiteBar");
	WhiteBar->SetTexture("WhiteBar", TEXT("UI/SliderBack.png"));
	WhiteBar->SetSize(167.f, 8.f);
	WhiteBar->SetPos(200.f, 305.f);
	WhiteBar->SetZOrder(1);

	WhiteSlider = CreateWidget<CWhiteSlider>("WhiteSlider");
	WhiteSlider->SetTexture("Slider", TEXT("UI/Slider.png"));
	WhiteSlider->SetSize(30.f, 30.f);
	//WhiteSlider->SetPos(200.f, 293.f);
	WhiteSlider->SetZOrder(11);
	WhiteSlider->SetMinMax(185.f, 352.f);
	WhiteSlider->SetInitPos(CHDR::GetInst()->GetWhite());

	BloomScaleBar = CreateWidget<CImage>("Bloom");
	BloomScaleBar->SetTexture("BloomScaleBar", TEXT("UI/SliderBack.png"));
	BloomScaleBar->SetSize(167.f, 8.f);
	BloomScaleBar->SetPos(200.f, 245.f);
	BloomScaleBar->SetZOrder(1);

	BloomScaleSlider = CreateWidget<CBloomScaleSlider>("BloomScaleSlider");
	BloomScaleSlider->SetTexture("Slider", TEXT("UI/Slider.png"));
	BloomScaleSlider->SetSize(30.f, 30.f);
	//BloomScaleSlider->SetPos(200.f, 233.f);
	BloomScaleSlider->SetZOrder(11);
	BloomScaleSlider->SetMinMax(185.f, 352.f);
	BloomScaleSlider->SetInitPos(CHDR::GetInst()->GetBloomScale());

	BloomThresholdBar = CreateWidget<CImage>("WhiteBar");
	BloomThresholdBar->SetTexture("BloonThresholdBar", TEXT("UI/SliderBack.png"));
	BloomThresholdBar->SetSize(167.f, 8.f);
	BloomThresholdBar->SetPos(200.f, 185.f);
	BloomThresholdBar->SetZOrder(1);

	BloomThresholdSlider = CreateWidget<CBloomThresholdSlider>("BloomThresholdSlider");
	BloomThresholdSlider->SetTexture("Slider", TEXT("UI/Slider.png"));
	BloomThresholdSlider->SetSize(30.f, 30.f);
	//BloomThresholdSlider->SetPos(200.f, 173.f);
	BloomThresholdSlider->SetZOrder(11);
	BloomThresholdSlider->SetMinMax(185.f, 352.f);
	BloomThresholdSlider->SetInitPos(CHDR::GetInst()->GetBloomThreshold());

	NearStartBar = CreateWidget<CImage>("NearStartBar");
	NearStartBar->SetTexture("NearStartBar", TEXT("UI/SliderBack.png"));
	NearStartBar->SetSize(167.f, 8.f);
	NearStartBar->SetPos(200.f, 125.f);
	NearStartBar->SetZOrder(1);

	NearStartSlider = CreateWidget<CNearStartSlider>("NearStartSlider");
	NearStartSlider->SetTexture("Slider", TEXT("UI/Slider.png"));
	NearStartSlider->SetSize(30.f, 30.f);
	//NearStartSlider->SetPos(200.f, 113.f);
	NearStartSlider->SetZOrder(11);
	NearStartSlider->SetMinMax(185.f, 352.f);
	NearStartSlider->SetInitPos(CHDR::GetInst()->GetNearStart());

	FarStartBar = CreateWidget<CImage>("FarStartBar");
	FarStartBar->SetTexture("FarStartBar", TEXT("UI/SliderBack.png"));
	FarStartBar->SetSize(167.f, 8.f);
	FarStartBar->SetPos(200.f, 65.f);
	FarStartBar->SetZOrder(1);

	FarStartSlider = CreateWidget<CFarStartSlider>("FarStartSlider");
	FarStartSlider->SetTexture("Slider", TEXT("UI/Slider.png"));
	FarStartSlider->SetSize(30.f, 30.f);
	//FarStartSlider->SetPos(200.f, 53.f);
	FarStartSlider->SetZOrder(11);
	FarStartSlider->SetMinMax(185.f, 352.f);
	FarStartSlider->SetInitPos(CHDR::GetInst()->GetFarStart());

	return true;
}

void CHDRWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	
}

void CHDRWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CHDRWindow::Render()
{
	CWidgetWindow::Render();
}

void CHDRWindow::ButtonCallBack()
{
	if (true == CHDR::GetInst()->GetHDREnable())
	{
		CHDR::GetInst()->SetHDREnable(false);
	}
	else
	{
		CHDR::GetInst()->SetHDREnable(true);
	}
}

void CHDRWindow::CheckBoxCallBack()
{
	if (true == CHDR::GetInst()->GetHDREnable())
	{
		CHDR::GetInst()->SetHDREnable(false);
	}
	else
	{
		CHDR::GetInst()->SetHDREnable(true);
	}
}




