#include "BloomThresholdSlider.h"
#include "HDR.h"
#include "Input.h"
CBloomThresholdSlider::CBloomThresholdSlider()
{
}

CBloomThresholdSlider::CBloomThresholdSlider(const CBloomThresholdSlider& widget)
{
}

CBloomThresholdSlider::~CBloomThresholdSlider()
{
}

void CBloomThresholdSlider::Start()
{
	CSlider::Start();
}

bool CBloomThresholdSlider::Init()
{
	if (CSlider::Init())
		return true;
	return false;
}

void CBloomThresholdSlider::Update(float DeltaTime)
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
			float v = (tpos.x - MinX) / (MaxX - MinX) * 8-4.f;
			CHDR::GetInst()->SetBloomThreshold(v);

		}
	}
	

}

void CBloomThresholdSlider::PostUpdate(float DeltaTime)
{
	CSlider::PostUpdate(DeltaTime);
}

void CBloomThresholdSlider::Render()
{
	CSlider::Render();
}

CSlider* CBloomThresholdSlider::Clone()
{
	return new CBloomThresholdSlider(*this);
}

void CBloomThresholdSlider::SetInitPos(const float BloomThreshhold)
{
	float xpos = (BloomThreshhold + 4) * 0.125f * (MaxX - MinX) + MinX;
	SetPos(xpos, 173.f);
}
