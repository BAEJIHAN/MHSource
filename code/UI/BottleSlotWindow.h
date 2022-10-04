#pragma once

#include "Widget/WidgetWindow.h"
#include "Widget/Text.h"
#include "Widget/Image.h"

struct BottleSlot
{
	CSharedPtr<CImage>	Image;
	CSharedPtr<CText>	Text;
	Coating_State		CoatingState;

private:
	Vector4 TintValue;
	
public:
	BottleSlot() :
		Image(nullptr),
		Text(nullptr),
		TintValue(0.f, 0.f, 0.f, 0.f),
		CoatingState(Coating_State::Normal)
	{
	}

public:
	void SetText(const TCHAR* tText)
	{
		return Text->SetText(tText);
	}
	
	const TCHAR* GetText()
	{
		return Text->GetText();
	}

	void SetTextureTint(const Vector4 Tint)
	{
		Image->SetTextureTint(Tint);
		
		TintValue = Tint;
	}
	
	Vector4 GetTextureTint() const
	{
		return TintValue;
	}

	Coating_State GetState() const
	{
		return CoatingState;
	}
};

class CBottleSlotWindow :
	public CWidgetWindow
{
	friend class CViewport;

protected:
	CBottleSlotWindow();
	virtual ~CBottleSlotWindow();

private:
	CSharedPtr<CImage>          m_WindowFrame;
	CSharedPtr<CImage>          m_SelectedBackImage;
	CSharedPtr<CImage>          m_UsedBottleImage;
	CSharedPtr<CImage>          m_UsedBottleFrameImage;
	CSharedPtr<CImage>          m_UsedBottleFlashImage;
	BottleSlot*                 m_Slot;      // Critical, Power, Explosion
	class CPlayer*				m_Player;
	Coating_State		m_CurrentState;

public:
	void SetUsingBottle(bool bEnable);

public:
	Coating_State UsingBottle(bool bEnable);


public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();

private:
	void CreateWidgets(Vector2 WindowSize);

private:
	void AscendSlot();
	void DescendSlot();
	void CheckUsedBottle();

};

