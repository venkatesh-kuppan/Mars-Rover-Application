#pragma once

class CPosition
{
public:

	//Default constructor and methods for setting the private members added for google test case testing,
	//otherwise better to use overloaded constructors that provide rover position before hand.
	CPosition();

	//make user to supply coordinates and orientation before hand
	CPosition(int x, int y, char Orientation);
	void printLocation(void) const;
	void setRoverCommand(std::string command);


	bool checkCoordinates(signed int x_right, signed int y_right);

	int get_x(void);
	int get_y(void);
	char get_orientation(void);

	void set_xyo(const int& x, const int& y, const char& orient);

	~CPosition();



private:
	int m_x;
	int m_y;
	char m_Orientation;

	void MoveRover(char command);
	void moveLeft(void);
	void moveRight(void);
	void moveForward(void);
};

