#pragma once

#define PI 3.141592f

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define LinearInterpolation(s,e,t) s + (e - s) * t

// COLOR
#define RED			 RGB(255,0,0)
#define GREEN		 RGB(0,255,0)
#define BLUE		 RGB(0,0,255)
#define WHITE		 RGB(255,255,255)
#define BLACK		 RGB(0,0,0)
#define GREY		 RGB(100,100,100)
#define SAND_DOLLAR	 RGB(150,120,100)
#define CYAN		 RGB(0,150,150)

using int16 = short;
using int32 = int;
using int64 = __int64;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned __int64;