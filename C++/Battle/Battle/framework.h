#pragma once

// 미리 컴파일된 헤더
// pch ... pre compiled header
// 1. framework.h / framework.cpp 만들기.... 이 때 이름은 중요하지 않다.
// 2. framework.cpp => 속성 => C++ => 미리컴파일된헤더 => 만들기/ framework.h
// 2. 프로젝트 => 속성 => C++ => 미리컴파일된헤더 => 사용/ framework.h

// framework.h의 경로 알려주기
// - 프로젝트 속성 => VC++디렉토리 => 포함 디렉토리 => $(ProjectDir) ... 현재 프로젝트의 경로

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>

using namespace std;


#include "Objects/Creature.h"
#include "Objects/Player.h"
#include "Objects/Monster.h"
#include "Objects/Knight.h"
#include "Objects/Goblin.h"
#include "Objects/Boss.h"

#include "World.h"

