#include "WhiteSlider.h"
#include "HDR.h"
#include "Input.h"
CWhiteSlider::CWhiteSlider()
{
}

CWhiteSlider::CWhiteSlider(const CWhiteSlider& widget)
{
}

CWhiteSlider::~CWhiteSlider()
{
}

void CWhiteSlider::Start()
{
	CSlider::Start();
}

bool CWhiteSlider::Init()
{
	if (CSlider::Init())
		return true;
	return false;
}

void CWhiteSlider::Update(float DeltaTime)
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
			float v = (tpos.x - MinX) / (MaxX - MinX) * 100;
			CHDR::GetInst()->SetWhite(v);

		}
	}




}

void CWhiteSlider::PostUpdate(float DeltaTime)
{
	CSlider::PostUpdate(DeltaTime);
}

void CWhiteSlider::Render()
{
	CSlider::Render();
}

CSlider* CWhiteSlider::Clone()
{
	return new CWhiteSlider(*this);
}

void CWhiteSlider::SetInitPos(const float White)
{
	float xpos = White * 0.01f * (MaxX - MinX) + MinX;
	SetPos(xpos, 293.f);
}
