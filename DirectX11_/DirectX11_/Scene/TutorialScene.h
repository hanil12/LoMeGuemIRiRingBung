#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	// Scene을(를) 통해 상속됨
	void Update() override;
	void Render() override;

private:
	// mesh
	shared_ptr<VertexBuffer> _vertexBuffer;

	// material
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
	shared_ptr<SamplerState> _samplerState;
	shared_ptr<SRV> _srv;
};

