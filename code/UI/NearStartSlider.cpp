#include "NearStartSlider.h"
#include "HDR.h"
#include "Input.h"
CNearStartSlider::CNearStartSlider()
{
}

CNearStartSlider::CNearStartSlider(const CNearStartSlider& widget)
{
}

CNearStartSlider::~CNearStartSlider()
{
}

void CNearStartSlider::Start()
{
	CSlider::Start();
}

bool CNearStartSlider::Init()
{
	if (CSlider::Init())
		return true;
	return false;
}

void CNearStartSlider::Update(float DeltaTime)
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
			float v = (tpos.x - MinX) / (MaxX - MinX) * 50;
			CHDR::GetInst()->SetNearStart(v);

		}
	}

	


}

void CNearStartSlider::PostUpdate(float DeltaTime)
{
	CSlider::PostUpdate(DeltaTime);
}

void CNearStartSlider::Render()
{
	CSlider::Render();
}

CSlider* CNearStartSlider::Clone()
{
	return new CNearStartSlider(*this);
}

void CNearStartSlider::SetInitPos(const float NearStaert)
{
	float xpos = NearStaert * 0.02f * (MaxX - MinX) + MinX;
	SetPos(xpos, 113.f);
}
