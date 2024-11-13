#pragma once

// �̸� �����ϵ� ���
// pch ... pre compiled header
// 1. framework.h / framework.cpp �����.... �� �� �̸��� �߿����� �ʴ�.
// 2. framework.cpp => �Ӽ� => C++ => �̸������ϵ���� => �����/ framework.h
// 2. ������Ʈ => �Ӽ� => C++ => �̸������ϵ���� => ���/ framework.h

// framework.h�� ��� �˷��ֱ�
// - ������Ʈ �Ӽ� => VC++���丮 => ���� ���丮 => $(ProjectDir) ... ���� ������Ʈ�� ���

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

