#include "framework.h"
#include "Cannon.h"

#include "Barrel.h"

Barrel::Barrel()
{
	_line = make_shared<Line>(Vector(), Vector());
}

Barrel::~Barrel()
{
}

void Barrel::Update()
{
	if(_cannon.expired() == true)
		return;

	_line->_start = _cannon.lock()->GetCenter();
	_line->_end = _line->_start + _direction * _length;

	_line->Update();
}

void Barrel::Render(HDC hdc)
{
	_line->Render(hdc);
}
