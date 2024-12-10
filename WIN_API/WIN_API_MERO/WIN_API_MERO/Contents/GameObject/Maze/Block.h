#pragma once
class Block
{
public:
	enum BlockType
	{
		NONE,
		ABLE,
		DISABLE,
	};

	Block();
	~Block();

	void Update();
	void Render(HDC hdc);

	void SetType(BlockType type) { _curType = type; }
	void SetPos(Vector pos) { _rect->Center() = pos; }

private:
	shared_ptr<RectCollider> _rect; // Component Pattern... 부품을 조립해서 쓰는 방법 => 재사용성이 매우 크게 증가한다.

	BlockType _curType = BlockType::NONE;
	vector<HBRUSH> _brushes;
};

