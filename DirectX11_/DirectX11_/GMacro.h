#pragma once

#define PI 3.141592f

// Macro
#define DEVICE  Device::Instance()->GetDevice()
#define DC		Device::Instance()->GetDC()
#define RTV		Device::Instance()->GetRTV()

#define WIN_WIDTH	 1200
#define WIN_HEIGHT	 720
#define CENTER		 Vector(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define SAMPLER		 StateManager::Instance()->GetSamplerState()
#define ALPHA		 StateManager::Instance()->GetAlphaState()
#define ADDITIVE	 StateManager::Instance()->GetAdditiveState()
#define NONEBLEND	 StateManager::Instance()->GetNoneBlendState()

#define KEY_UP(k)			InputManager::GetInstance()->Up(k)
#define KEY_DOWN(k)			InputManager::GetInstance()->Down(k)
#define KEY_PRESS(k)		InputManager::GetInstance()->Press(k)

#define DELTA_TIME			TimeManager::Instance()->GetDeltaTime()
#define RUN_TIME			TimeManager::Instance()->GetRunTime()