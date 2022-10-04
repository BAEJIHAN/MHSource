
#pragma once

#include "Scene/SceneMode.h"
#include "Object_Info.h"

class CTownSceneMode :
	public CSceneMode
{
public:
	CTownSceneMode();
	~CTownSceneMode();

private:
	CSharedPtr<class CMainWindow> m_MainWindow;
	std::function<void(bool, float)> m_LoadingFunction;
	std::vector<Object_Info*> m_vecObjectInfo;
	bool    m_First;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	const CharacterInfo* GetCharacterInfo(const std::string& CharacterName)  const;

private:
	void LoadMesh();
	void CreateMaterial();
	void CreateAnimationSequence();
	void CreateBillboardSequence();
	void CreateParticle();
	void AddWeaponSocket();
	void AddMonsterSocket();
	void AddLargeMonsterSocket();
	void LoadSceneFile(const char* FileName, const std::string& PathName = DATA_PATH);
	void CreateSequence(const std::string& Name, const TCHAR* FileName, int CountX, int CountY, float SizeX, float SizeY);

private:
	void AddLandScape(std::vector<TCHAR*>& vec, const TCHAR* Path);
	void SetLandScape(int Register, const std::string& Name, std::vector<TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);

public:
	template <typename T>
	void SetLoadingFunction(T* Obj, void(T::* Func)(bool, float))
	{
		m_LoadingFunction = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}
};

