#include "DebugWindow.h"
#include "Engine.h"

#include "Widget/Number.h"
#include "Widget/Text.h"

CDebugWindow::CDebugWindow()
{
	SetTypeID<CDebugWindow>();
}

CDebugWindow::CDebugWindow(const CDebugWindow& Window) :
	CWidgetWindow(Window)
{
}

CDebugWindow::~CDebugWindow()
{
}

void CDebugWindow::SetDebugText(const TCHAR* Text)
{
	m_DebugText1->SetText(Text);
}

void CDebugWindow::SetDebugText2(const TCHAR* Text)
{
	m_DebugText2->SetText(Text);
}

void CDebugWindow::SetDebugText2Result(const TCHAR* Text)
{
	m_DebugText2Result->SetText(Text);
}

void CDebugWindow::SetDebugNumber(int Number)
{
	TCHAR* T_char = new TCHAR[32];
	
	wsprintfW(T_char, TEXT("%d"), Number);

	m_DebugNumber1->SetText(T_char);
	
	SAFE_DELETE_ARRAY(T_char);
}

void CDebugWindow::SetDebugText3(const TCHAR* Text)
{
	m_DebugText3->SetText(Text);
}

void CDebugWindow::SetDebugText3Result(int Number)
{
	TCHAR* T_char = new TCHAR[32];

	wsprintfW(T_char, TEXT("%d"), Number);

	m_DebugText3Result->SetText(T_char);

	SAFE_DELETE_ARRAY(T_char);
}

void CDebugWindow::SetDebugText4(const TCHAR* Text)
{
	m_DebugText4->SetText(Text);
}

void CDebugWindow::SetDebugText4Result(float Number)
{
	float fNum = (float)Number;

	char* fchar = new char[64];

	TCHAR T_Char[64] = {};

	sprintf_s(fchar, 64, "%f", fNum);

	int ConvertLength = MultiByteToWideChar(CP_ACP, 0, fchar, -1, nullptr, 0);
	MultiByteToWideChar(CP_ACP, 0, fchar, -1, T_Char, ConvertLength);

	m_DebugText4Result->SetText(T_Char);
	SAFE_DELETE_ARRAY(fchar);
}

void CDebugWindow::SetDebugText4Result2(float Number)
{
	float fNum = (float)Number;

	char* fchar = new char[64];

	TCHAR T_Char[64] = {};

	sprintf_s(fchar, 64, "%.4f", fNum);

	int ConvertLength = MultiByteToWideChar(CP_ACP, 0, fchar, -1, nullptr, 0);
	MultiByteToWideChar(CP_ACP, 0, fchar, -1, T_Char, ConvertLength);

	m_DebugText4Result2->SetText(T_Char);
	SAFE_DELETE_ARRAY(fchar);
}

void CDebugWindow::SetDebugText5(const TCHAR* Text)
{
	m_DebugText5->SetText(Text);
}

void CDebugWindow::SetDebugText5Result(float Number)
{
	float fNum = (float)Number;

	char* fchar = new char[64];

	TCHAR T_Char[64] = {};

	sprintf_s(fchar, 64, "%f.5", fNum);

	int ConvertLength = MultiByteToWideChar(CP_ACP, 0, fchar, -1, nullptr, 0);
	MultiByteToWideChar(CP_ACP, 0, fchar, -1, T_Char, ConvertLength);

	m_DebugText5Result->SetText(T_Char);
	SAFE_DELETE_ARRAY(fchar);
}

void CDebugWindow::SetDebugText5Result2(float Number)
{
	float fNum = (float)Number;

	char* fchar = new char[64];

	TCHAR T_Char[64] = {};

	sprintf_s(fchar, 64, "%f", fNum);

	int ConvertLength = MultiByteToWideChar(CP_ACP, 0, fchar, -1, nullptr, 0);
	MultiByteToWideChar(CP_ACP, 0, fchar, -1, T_Char, ConvertLength);

	m_DebugText5Result2->SetText(T_Char);
	SAFE_DELETE_ARRAY(fchar);
}

void CDebugWindow::SetDebugText6(const TCHAR* Text)
{
	m_DebugText5->SetText(Text);
}

void CDebugWindow::SetDebugText6Result(float Number)
{
	float fNum = (float)Number;

	char* fchar = new char[64];

	TCHAR T_Char[64] = {};

	sprintf_s(fchar, 64, "%f", fNum);

	int ConvertLength = MultiByteToWideChar(CP_ACP, 0, fchar, -1, nullptr, 0);
	MultiByteToWideChar(CP_ACP, 0, fchar, -1, T_Char, ConvertLength);

	m_DebugText6Result->SetText(T_Char);
	
	SAFE_DELETE_ARRAY(fchar);
}

void CDebugWindow::Start()
{
	CWidgetWindow::Start();
}

bool CDebugWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}

	SetSize(1280.f, 720.f);
	SetZOrder(10);

	Resolution RS = CEngine::GetInst()->GetRS();

	m_DebugNumber1 = CreateWidget<CText>("DebugNumber1");
	m_DebugText1 = CreateWidget<CText>("DebugText1");
	m_DebugText2 = CreateWidget<CText>("DebugText2");
	m_DebugText2Result = CreateWidget<CText>("DebugText2Result");
	m_DebugText3 = CreateWidget<CText>("DebugText3");
	m_DebugText3Result = CreateWidget<CText>("DebugText3Result");
	m_DebugText4 = CreateWidget<CText>("DebugText3");
	m_DebugText4Result = CreateWidget<CText>("DebugText3Result");
	m_DebugText4Result2 = CreateWidget<CText>("DebugText3Result");
	m_DebugText5 = CreateWidget<CText>("DebugText3");
	m_DebugText5Result = CreateWidget<CText>("DebugText3Result");	
	m_DebugText5Result2 = CreateWidget<CText>("DebugText3Result");
	m_DebugText6 = CreateWidget<CText>("DebugText3");
	m_DebugText6Result = CreateWidget<CText>("DebugText3Result");

	m_DebugNumber1->SetZOrder(4);
	m_DebugNumber1->SetSize(200.f, 100.f);
	m_DebugNumber1->SetPos(1050.f, 500.f);
	m_DebugNumber1->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugNumber1->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugNumber1->SetAlphaEnable(true);
	m_DebugNumber1->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugNumber1->SetFontSize(20.f);
	m_DebugNumber1->SetText(TEXT("9999"));

	m_DebugText1->SetZOrder(4);
	m_DebugText1->SetSize(100.f, 100.f);
	m_DebugText1->SetPos(750.f, 500.f);
	m_DebugText1->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText1->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText1->SetAlphaEnable(true);
	m_DebugText1->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText1->SetFontSize(20.f);
	m_DebugText1->SetText(TEXT("m_TargetRotateY : "));
	
	m_DebugText2->SetZOrder(4);
	m_DebugText2->SetSize(200.f, 100.f);
	m_DebugText2->SetPos(750.f, 400.f);
	m_DebugText2->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText2->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText2->SetAlphaEnable(true);
	m_DebugText2->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText2->SetFontSize(20.f);
	m_DebugText2->SetText(TEXT("CurrnetAnimName : "));
	
	m_DebugText2Result->SetZOrder(4);
	m_DebugText2Result->SetSize(100.f, 100.f);
	m_DebugText2Result->SetPos(1050.f, 400.f);
	m_DebugText2Result->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText2Result->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText2Result->SetAlphaEnable(true);
	m_DebugText2Result->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText2Result->SetFontSize(20.f);
	m_DebugText2Result->SetText(TEXT("N/A"));

	m_DebugText3->SetZOrder(4);
	m_DebugText3->SetSize(200.f, 100.f);
	m_DebugText3->SetPos(750.f, 300.f);
	m_DebugText3->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText3->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText3->SetAlphaEnable(true);
	m_DebugText3->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText3->SetFontSize(20.f);
	m_DebugText3->SetText(TEXT("Anjanath Rotation Y : "));
	
	m_DebugText3Result->SetZOrder(4);
	m_DebugText3Result->SetSize(100.f, 100.f);
	m_DebugText3Result->SetPos(1050.f, 300.f);
	m_DebugText3Result->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText3Result->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText3Result->SetAlphaEnable(true);
	m_DebugText3Result->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText3Result->SetFontSize(20.f);
	m_DebugText3Result->SetText(TEXT("N/A"));
	
	m_DebugText4->SetZOrder(4);
	m_DebugText4->SetSize(200.f, 100.f);
	m_DebugText4->SetPos(750.f, 200.f);
	m_DebugText4->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText4->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText4->SetAlphaEnable(true);
	m_DebugText4->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText4->SetFontSize(20.f);
	m_DebugText4->SetText(TEXT("Lookat PlayerDir : "));
	
	m_DebugText4Result->SetZOrder(4);
	m_DebugText4Result->SetSize(200.f, 100.f);
	m_DebugText4Result->SetPos(1050.f, 200.f);
	m_DebugText4Result->SetAlignH(TEXT_ALIGN_H::Left);
	m_DebugText4Result->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText4Result->SetAlphaEnable(true);
	m_DebugText4Result->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText4Result->SetFontSize(20.f);
	m_DebugText4Result->SetText(TEXT("N/A"));
	
	m_DebugText4Result2->SetZOrder(4);
	m_DebugText4Result2->SetSize(200.f, 100.f);
	m_DebugText4Result2->SetPos(1150.f, 200.f);
	m_DebugText4Result2->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText4Result2->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText4Result2->SetAlphaEnable(true);
	m_DebugText4Result2->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText4Result2->SetFontSize(20.f);
	m_DebugText4Result2->SetText(TEXT("N/A"));
	
	m_DebugText5->SetZOrder(4);
	m_DebugText5->SetSize(200.f, 100.f);
	m_DebugText5->SetPos(750.f, 100.f);
	m_DebugText5->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText5->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText5->SetAlphaEnable(true);
	m_DebugText5->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText5->SetFontSize(20.f);
	m_DebugText5->SetText(TEXT("Anjanath Dir : "));
	
	m_DebugText5Result->SetZOrder(4);
	m_DebugText5Result->SetSize(200.f, 100.f);
	m_DebugText5Result->SetPos(1050.f, 100.f);
	m_DebugText5Result->SetAlignH(TEXT_ALIGN_H::Left);
	m_DebugText5Result->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText5Result->SetAlphaEnable(true);
	m_DebugText5Result->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText5Result->SetFontSize(20.f);
	m_DebugText5Result->SetText(TEXT("N/A"));

	m_DebugText5Result2->SetZOrder(4);
	m_DebugText5Result2->SetSize(200.f, 100.f);
	m_DebugText5Result2->SetPos(1150.f, 100.f);
	m_DebugText5Result2->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText5Result2->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText5Result2->SetAlphaEnable(true);
	m_DebugText5Result2->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText5Result2->SetFontSize(20.f);
	m_DebugText5Result2->SetText(TEXT("N/A"));
	
	m_DebugText6->SetZOrder(4);
	m_DebugText6->SetSize(200.f, 100.f);
	m_DebugText6->SetPos(750.f, 0.f);
	m_DebugText6->SetAlignH(TEXT_ALIGN_H::Center);
	m_DebugText6->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText6->SetAlphaEnable(true);
	m_DebugText6->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText6->SetFontSize(20.f);
	m_DebugText6->SetText(TEXT("Radian Value : "));
	
	m_DebugText6Result->SetZOrder(4);
	m_DebugText6Result->SetSize(200.f, 100.f);
	m_DebugText6Result->SetPos(1050.f, 0.f);
	m_DebugText6Result->SetAlignH(TEXT_ALIGN_H::Left);
	m_DebugText6Result->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DebugText6Result->SetAlphaEnable(true);
	m_DebugText6Result->SetColor(Vector4(0.9f, 0.9f, 0.9f, 1.0f));
	m_DebugText6Result->SetFontSize(20.f);
	m_DebugText6Result->SetText(TEXT("N/A"));

	m_DebugNumber1->Enable(false);
	m_DebugText1->Enable(false);
	m_DebugText2->Enable(false);
	m_DebugText2Result->Enable(false);
	m_DebugText3->Enable(false);
	m_DebugText3Result->Enable(false);
	m_DebugText4->Enable(true);
	m_DebugText4Result->Enable(true);
	m_DebugText4Result2->Enable(true);
	m_DebugText5->Enable(false);
	m_DebugText5Result->Enable(false);
	m_DebugText5Result2->Enable(false);
	m_DebugText6->Enable(false);
	m_DebugText6Result->Enable(false);

	return true;
}

void CDebugWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CDebugWindow::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CDebugWindow::Render()
{
	CWidgetWindow::Render();
}
