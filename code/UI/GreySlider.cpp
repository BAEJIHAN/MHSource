#include "GreySlider.h"
#include "HDR.h"
#include "Input.h"
CGreySlider::CGreySlider()
{
}

CGreySlider::CGreySlider(const CGreySlider& widget)
{
}

CGreySlider::~CGreySlider()
{
}

void CGreySlider::Start()
{
	CSlider::Start();
}

bool CGreySlider::Init()
{
	if (CSlider::Init())
		return true;
	return false;
}

void CGreySlider::Update(float DeltaTime)
{
	CSlider::Update(DeltaTime);

	if (CInput::GetInst()->IsPush("Attack") && m_MouseHovered)
	{
		Vector2 MPos = CInput::GetInst()->GetMouseMove();
		Vector2 tpos = GetPos();
		tpos.x = tpos.x + MPos.x;
		if (tpos.x > MinX && tpos.x < MaxX)
		{
			SetPos(tpos);
			float v = (tpos.x - MinX)/(MaxX-MinX)*100;
			CHDR::GetInst()->SetGrey(v);

		}
	}

	

	
}

void CGreySlider::PostUpdate(float DeltaTime)
{
	CSlider::PostUpdate(DeltaTime);
}

void CGreySlider::Render()
{
	CSlider::Render();
}

CSlider* CGreySlider::Clone()
{
	return new CGreySlider(*this);
}

void CGreySlider::SetInitPos(const float Grey)
{
	float xpos = Grey * 0.01f * (MaxX - MinX) + MinX;
	SetPos(xpos, 353.f);
}
