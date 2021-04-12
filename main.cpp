//////////////////////////////////////////
//	C++ Unique ptr
//	Naughty Panda @ 2021
//////////////////////////////////////////

#include <iostream>
#include <sstream>

//////////////////////////////////////////
//	8.1
//////////////////////////////////////////

template <typename T>
T div(const T& t1, const T& t2) {

	if (t2 == 0) throw std::exception(__FUNCSIG__);
	return t1 / t2;
}

//////////////////////////////////////////
//	8.2
//////////////////////////////////////////

class Ex {

private:
	int _x;

public:
	Ex(const int& x) : _x(x) {}
	int What() const { return _x; }
};

class Bar {

private:
	int _y;

public:
	Bar() : _y(0) {}
	void Set(const int& a);
};

void Bar::Set(const int& a) {

	if (_y + a > 100) throw Ex(pow(a, _y));
	_y = a;
}

//////////////////////////////////////////
//	8.3
//////////////////////////////////////////

enum class EDirection {
	None, Up, Down = -1, Left = 2, Right = -2
};

class OffTheField : public std::exception {

private:
	std::ostringstream _data;

public:
	OffTheField(const std::pair<uint8_t, uint8_t>& pos, const std::pair<uint8_t, uint8_t>& grid, const char* dir) noexcept
	: std::exception("Off the field") {
	
		_data.clear();
		_data << "Error: " << std::exception::what() << '\n';
		_data << "Current position: " << static_cast<int>(pos.first) << ' ' << static_cast<int>(pos.second) << '\n';
		_data << "Direction: " << dir << '\n';
		_data << "Grid size: " << static_cast<int>(grid.first) << ' ' << static_cast<int>(grid.second) << '\n';
	}

	const std::string What() const;
};

const std::string OffTheField::What() const {

	return _data.str();
}

class IllegalCommand : public std::exception {

public:
	IllegalCommand(const char* reason) : std::exception(reason) {}
};

class Robot {

private:
	const uint8_t _max_gridX{ 10 };
	const uint8_t _max_gridY{ 10 };
	uint8_t _posX{ 0 };
	uint8_t _posY{ 0 };

	std::pair<uint8_t, uint8_t> GetCurrentPos() const;
	std::pair<uint8_t, uint8_t> GetGridSize() const;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

public:
	Robot(const uint8_t& x, const uint8_t& y) : _posX(x), _posY(y) {}

	void Move(const EDirection& dir);
};

std::pair<uint8_t, uint8_t> Robot::GetCurrentPos() const {

	return { _posX, _posY };
}

std::pair<uint8_t, uint8_t> Robot::GetGridSize() const {

	return { _max_gridX, _max_gridY };
}

void Robot::Move(const EDirection& dir) {

	switch (dir) {
	case EDirection::Up:	MoveUp();		break;
	case EDirection::Down:	MoveDown();		break;
	case EDirection::Left:	MoveLeft();		break;
	case EDirection::Right: MoveRight();	break;
	default: throw IllegalCommand("No direction");
	}
}

void Robot::MoveUp() {

	if (_posY + 1 > _max_gridY) throw OffTheField(GetCurrentPos(), GetGridSize(), "up");
	++_posY;
}

void Robot::MoveDown() {

	if (_posY - 1 == UINT8_MAX) throw OffTheField(GetCurrentPos(), GetGridSize(), "down");
	--_posY;
}

void Robot::MoveLeft() {

	if (_posX - 1 == UINT8_MAX) throw OffTheField(GetCurrentPos(), GetGridSize(), "left");
	--_posX;
}

void Robot::MoveRight() {

	if (_posX + 1 > _max_gridX) throw OffTheField(GetCurrentPos(), GetGridSize(), "right");
	++_posX;
}



int main() {

	//////////////////////////////////////////
	//	8.1
	//////////////////////////////////////////

	try {
		std::cout << div<int>(4, 2) << '\n';
		std::cout << div<float>(4.3f, 0.0f) << '\n';
		std::cout << div<double>(-5.6, 1.0) << '\n';
		std::cout << div<uint16_t>(3, 3) << '\n';
	}
	catch (const std::exception& excep) {
		std::cerr << "Error in function: " << excep.what() << '\n';
	}

	//////////////////////////////////////////
	//	8.2
	//////////////////////////////////////////

	Bar bar;
	int input{ 1 };

	try	{
		while (input != 0) {

			std::cin >> input;
			bar.Set(input);
		}
	}
	catch (const Ex& ex) {
		std::cerr << "Error. " << ex.What();
	}

	//////////////////////////////////////////
	//	8.3
	//////////////////////////////////////////

	Robot rob(8, 8);
	try {
		rob.Move(EDirection::Up);
		rob.Move(EDirection::Left);
		rob.Move(EDirection::Up);
		rob.Move(EDirection::Up);
		rob.Move(EDirection::None);
	}
	catch (const OffTheField& ex) {
		std::cerr << ex.What();
	}
	catch (const IllegalCommand& ex) {
		std::cerr << ex.what();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what();
	}

	return 0;
}
