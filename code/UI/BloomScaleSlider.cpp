#include "BloomScaleSlider.h"
#include "HDR.h"
#include "Input.h"
CBloomScaleSlider::CBloomScaleSlider()
{
}

CBloomScaleSlider::CBloomScaleSlider(const CBloomScaleSlider& widget)
{
}

CBloomScaleSlider::~CBloomScaleSlider()
{
}

void CBloomScaleSlider::Start()
{
	CSlider::Start();
}

bool CBloomScaleSlider::Init()
{
	if (CSlider::Init())
	{		
		return true;
	}
		
	return false;
}

void CBloomScaleSlider::Update(float DeltaTime)
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
			float v = (tpos.x - MinX) / (MaxX - MinX) * 4-2.f;
			CHDR::GetInst()->SetBloomScale(v);

		}
	}

	


}

void CBloomScaleSlider::PostUpdate(float DeltaTime)
{
	CSlider::PostUpdate(DeltaTime);
}

void CBloomScaleSlider::Render()
{
	CSlider::Render();
}

CSlider* CBloomScaleSlider::Clone()
{
	return new CBloomScaleSlider(*this);
}

void CBloomScaleSlider::SetInitPos(const float BloomScale) 
{
	float xpos = (BloomScale + 2) * 0.25f * (MaxX - MinX) + MinX;
	SetPos(xpos, 233.f);
}
