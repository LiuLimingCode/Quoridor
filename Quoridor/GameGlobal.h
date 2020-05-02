#pragma once

#define NUM_SQUARE		7       // 棋盘的大小
#define WALLNUM			8       // 每个棋子拥有的墙数

#define CONDITION_PAWN1_WIN(p)	( (p.col) == (NUM_SQUARE - 1) )   // 棋子1的胜利条件
#define CONDITION_PAWN1_START(p)	{ (p.row) = ((NUM_SQUARE - 1) / 2); (p.col) = 0; }    //棋子1的开始位置
#define CONDITION_PAWN2_WIN(p)	( (p.col) == 0 )
#define CONDITION_PAWN2_START(p)	{ (p.row) = ((NUM_SQUARE - 1) / 2); (p.col) = (NUM_SQUARE - 1); }
#define CONDITION_PAWN3_WIN(p)	( (p.row) == (NUM_SQUARE - 1) )
#define CONDITION_PAWN3_START(p)	{ (p.row) = 0; (p.col) = ((NUM_SQUARE - 1) / 2); }
#define CONDITION_PAWN4_WIN(p)	( (p.row) == 0 )
#define CONDITION_PAWN4_START(p)	{ (p.row) = (NUM_SQUARE - 1); (p.col) = ((NUM_SQUARE - 1) / 2); }

enum OrderType { // 指令类型
	WALLH, // 横墙
	WALLV, // 竖墙
	MOVE,  // 移动
	NONE,  // 无
};

class Point {
public:
	int row;
	int col;
	Point(int r = 0, int c = 0) : row(r), col(c) {}
};

template <class T>
class Array2D {
public:
	T** array2D = nullptr;
	int row = 0;
	int col = 0;

	Array2D() = default;

	Array2D(int numOfRow, int numOfCol, T initValue) {
		row = numOfRow;
		col = numOfCol;
		array2D = new T*[numOfRow];
		for (int temp = 0; temp < numOfRow; temp++)
			array2D[temp] = new T[numOfCol];

		for (int r = 0; r < row; ++r) {
			for (int c = 0; c < col; ++c) {
				array2D[r][c] = initValue;
			}
		}
	}

	Array2D(const Array2D& copyArry) {
		*this = copyArry;
	}

	~Array2D() {
		for (int temp = 0; temp < row; temp++)
			delete[]array2D[temp];
		delete[]array2D;
	}

	void operator=(const Array2D& copyArry) {
		row = copyArry.row;
		col = copyArry.col;
		array2D = new T * [row];
		for (int temp = 0; temp < row; temp++)
			array2D[temp] = new T[col];

		for (int r = 0; r < row; ++r) {
			for (int c = 0; c < col; ++c) {
				array2D[r][c] = copyArry.array2D[r][c];
			}
		}
	}

	inline const T* operator[](const int index) const {
		//if (index >= row) return nullptr;
		return array2D[index];
	}

	inline T* operator[](const int index) {
		//if (index >= row) return nullptr;
		return array2D[index];
	}

	void clear() {
		for (int temp = 0; temp < row; temp++)
			delete[]array2D[temp];
		delete[]array2D;
		array2D = nullptr;
		col = 0;
		row = 0;
	}
};

class Order {
public:
    OrderType type;
	Point point;
	Order() { type = OrderType::NONE; point = Point(0, 0); };
	Order(int t, Point p) : type((OrderType)t), point(p) {}
	Order(int t, int row, int col) : type((OrderType)t), point(Point(row, col)) {}
};

#define MAX_PAWN_NUM  4
enum PawnId
{
	EMPTY = -1,
	PAWN1 = 0,
	PAWN2 = 1,
	PAWN_NUM = 2,
};
