#pragma once
class Device
{
public:
	static void Create()
	{
		if(_instance == nullptr)
			_instance = new Device();
	}

	static void Delete()
	{
		if(_instance != nullptr)
			delete _instance;
	}

	static Device* Instance()
	{
		return _instance;
	}

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return _device; }
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDC() { return _deviceContext; }
	Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() { return _swapChain; }
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV() { return _renderTargetView; }

private:
	Device();
	~Device();

	static Device* _instance;

	Microsoft::WRL::ComPtr<ID3D11Device>					 _device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>				 _deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>					 _swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			 _renderTargetView;
};

