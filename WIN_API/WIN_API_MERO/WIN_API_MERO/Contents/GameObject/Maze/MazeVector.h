#pragma once
struct MazeVector
{
	MazeVector() = default;
	MazeVector(int y, int x) : y(y), x(x) {}

    MazeVector operator+(const MazeVector& other) const
    {

        MazeVector result;

        result.x = this->x + other.x;
        result.y = this->y + other.y;

        return result;
    }
    MazeVector operator-(const MazeVector& other) const
    {
        MazeVector result;

        result.x = this->x - other.x;
        result.y = this->y - other.y;

        return result;
    }
    MazeVector operator*(const float& value) const
    {
        return MazeVector(y * value, x * value);
    }

    MazeVector& operator=(const MazeVector& other)
    {
        x = other.x;
        y = other.y;

        return *this;
    }
    MazeVector& operator+=(const MazeVector& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }
    MazeVector& operator-=(const MazeVector& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

	int y = 0; // row
	int x = 0; // column
};

