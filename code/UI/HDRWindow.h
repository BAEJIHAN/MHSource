
#pragma once
#include "Widget/Text.h"
#include "Widget/Button.h"
#include "Widget/WidgetWindow.h"
#include "Widget/CheckBox.h"
#include "Widget/Image.h"
#include "GreySlider.h"
#include "WhiteSlider.h"
#include "BloomScaleSlider.h"
#include "BloomThresholdSlider.h"
#include "NearStartSlider.h"
#include "FarStartSlider.h"
class CHDRWindow :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CHDRWindow();
    CHDRWindow(const CHDRWindow& Window);
    virtual ~CHDRWindow();

    CSharedPtr<CImage> BackFrame;

    CSharedPtr<CText>   HDRButtonText;
    CSharedPtr<CText>	GreyText;
    CSharedPtr<CText>	WhiteText;
    CSharedPtr<CText>	BloomScaleText;
    CSharedPtr<CText>	BloomThresholdText;
    CSharedPtr<CText>	NearStartText;
    CSharedPtr<CText>	FarStartText;


    CSharedPtr<CCheckBox> CheckBox;
    CSharedPtr<CImage> GreyBar;
    CSharedPtr<CImage> WhiteBar;
    CSharedPtr<CImage> BloomScaleBar;
    CSharedPtr<CImage> BloomThresholdBar;
    CSharedPtr<CImage> NearStartBar;
    CSharedPtr<CImage> FarStartBar;
    CSharedPtr<CGreySlider> GreySlider;
    CSharedPtr<CWhiteSlider> WhiteSlider;
    CSharedPtr<CBloomScaleSlider> BloomScaleSlider;
    CSharedPtr<CBloomThresholdSlider> BloomThresholdSlider;
    CSharedPtr<CNearStartSlider> NearStartSlider;
    CSharedPtr<CFarStartSlider> FarStartSlider;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

private:
    void ButtonCallBack();
    void CheckBoxCallBack();



};

