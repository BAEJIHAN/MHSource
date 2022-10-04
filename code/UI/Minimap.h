#pragma once

#include "Widget/Widget.h"

class CMinimap :
    public CWidget
{
	friend class CWidgetWindow;

protected:
	CMinimap();
	virtual ~CMinimap();

protected:
	WidgetImageInfo		m_Info;
	CSharedPtr<class CTexture>	m_SrcMapTexture;
	CSharedPtr<class CTexture>	m_MinimapTexture;

private:
	Vector2		m_PlayerPos;
	Vector2		m_PlayerPrevPos;
	Vector2		m_MapSize;
	Vector2		m_ClipMapSize;
	Vector2		m_MapTextureSize;

public:
	WidgetImageInfo GetInfo()   const
	{
		return m_Info;
	}

	virtual void Enable(bool bEnable)
	{
		CWidget::Enable(bEnable);
	}

	float GetMinimapSize() const
	{
		return m_ClipMapSize.x;
	}

public:
	void SetTexture(CTexture* Texture)
	{
		m_Info.Texture = Texture;

		SetUseTexture(true);
	}

	void SetMapSize(Vector2 Size)
	{
		m_MapSize = Size;
	}

	bool SetTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool SetMapTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool SetTextureFullPath(const std::string& Name,
		const TCHAR* FullPath);
	bool SetTexture(const std::string& Name, const std::vector<TCHAR*>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool SetTextureFullPath(const std::string& Name,
		const std::vector<TCHAR*>& vecFullPath);
	void SetTextureTint(const Vector4& Tint);
	void SetTextureTint(unsigned char r, unsigned char g,
		unsigned char b, unsigned char a);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();

};

