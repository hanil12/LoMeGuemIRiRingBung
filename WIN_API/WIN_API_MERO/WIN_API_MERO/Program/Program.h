#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render(HDC hdc);

	void SetScene(string scene) { _curScene = scene; }
	string CurScene() { return _curScene; }
	
	static HDC backBuffer;
	// buffer : 임시저장공간

private:
	unordered_map<string, shared_ptr<Scene>> _sceneTable;
	string _curScene;

	HBITMAP _hBitMap;
};

