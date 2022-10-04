#include "FarStartSlider.h"
#include "HDR.h"
#include "Input.h"
CFarStartSlider::CFarStartSlider()
{
}

CFarStartSlider::CFarStartSlider(const CFarStartSlider& widget)
{
}

CFarStartSlider::~CFarStartSlider()
{
}

void CFarStartSlider::Start()
{
	CSlider::Start();
}

bool CFarStartSlider::Init()
{
	if (CSlider::Init())
		return true;
	return false;
}

void CFarStartSlider::Update(float DeltaTime)
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
			float v = (tpos.x - MinX) / (MaxX - MinX) * 300.f;
			CHDR::GetInst()->SetFarStart(v+300.f);
		}
	}
}

void CFarStartSlider::PostUpdate(float DeltaTime)
{
	CSlider::PostUpdate(DeltaTime);
}

void CFarStartSlider::Render()
{
	CSlider::Render();
}

CSlider* CFarStartSlider::Clone()
{
	return new CFarStartSlider(*this);
}

void CFarStartSlider::SetInitPos(const float FarStart)
{
	float xpos = (FarStart-300.f)  * 0.0033f * (MaxX - MinX) + MinX;
	SetPos(xpos, 53.f);
}
