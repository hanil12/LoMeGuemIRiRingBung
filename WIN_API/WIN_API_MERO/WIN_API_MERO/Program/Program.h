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

private:
	unordered_map<string, shared_ptr<Scene>> _sceneTable;
	string _curScene;
};

