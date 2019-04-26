#include "pch.h"
#include "CPosition.h"
#include<iostream>

/*
array reference for moving the rover forward along the coordinates
*/
//					  { N, E, S,  W }
signed int x_mov[4] = { 0, 1, 0, -1 };
signed int y_mov[4] = { 1, 0, -1, 0 };
/*
array reference for orientation of Rover
*/
char Orientation[5] = { 'N','E','S','W','X'}; // X - in case invalid orientation is provided



using namespace std;


CPosition::CPosition():m_x(0),m_y(0),m_Orientation(0xff)
{
}

CPosition::CPosition(int x, int y, char Orientation) :m_x(x), m_y(y)
{

	/*
storing the index of the array Orientation based on the input
*/
	switch (Orientation) {
	case 'N':
		m_Orientation = 0;
		break;
	case 'E':
		m_Orientation = 1;
		break;
	case 'S':
		m_Orientation = 2;
		break;
	case 'W':
		m_Orientation = 3;
		break;
	default:
		m_Orientation = 4;
		cerr << "invalid orientation" << endl;
		//exit(0);
		break;
	}
}

void CPosition::printLocation(void) const
{
	cout << "location of rover = {" << m_x << "," << m_y << "} " << Orientation[m_Orientation] << endl;;
}

void CPosition::setRoverCommand(string command)
{
	for (int i = 0; i < command.length(); i++) {
		MoveRover(command[i]);
	}
}

void CPosition::MoveRover(char command)
{
	/*
	call appropirate method based on commands
	*/
	switch (command) {
	case 'M':
		moveForward();
		break;
	case 'L':
		moveLeft();
		break;
	case 'R':
		moveRight();
		break;
	default:
		cerr << " MoveRover:: invalid command, cannot move Rover = " << command <<  endl;
		exit(0);
		break;
	}
}

void CPosition::moveLeft(void)
{
	/*
	storing the index of the array Orientation based on the input
	*/
	switch (m_Orientation) {
	case 0:
		m_Orientation = 3;
		break;
	case 1:
		m_Orientation = 0;
		break;
	case 2:
		m_Orientation = 1;
		break;
	case 3:
		m_Orientation = 2;
		break;
	default: /*
			 case will never be reached
			 */
		break;
	}
}

void CPosition::moveRight(void)
{
	switch (m_Orientation) {
	case 0:
		m_Orientation = 1;
		break;
	case 1:
		m_Orientation = 2;
		break;
	case 2:
		m_Orientation = 3;
		break;
	case 3:
		m_Orientation = 0;
		break;
	default: /*
			 case will never be reached
			 */
		break;
	}
}

void CPosition::moveForward(void)
{
	switch (m_Orientation) {
	case 0:
		m_x += x_mov[0];
		m_y += y_mov[0];
		break;
	case 1:
		m_x += x_mov[1];
		m_y += y_mov[1];
		break;
	case 2:
		m_x += x_mov[2];
		m_y += y_mov[2];
		break;
	case 3:
		m_x += x_mov[3];
		m_y += y_mov[3];
		break;
	default:/*
			case will never be reached
			*/
		break;
	}
}

bool CPosition::checkCoordinates(signed int x_right, signed int y_right)
{
	if (m_x > x_right || m_y > y_right) {
		cerr << "the commands can make rover move to outside the boundary" << endl;
		//reset back to default position
		m_x = 0;
		m_y = 0;
		m_Orientation = 0;
		return false;
	}

	return true;
}

int CPosition::get_x(void)
{
	return m_x;
}

int CPosition::get_y(void)
{
	return m_y;
}

char CPosition::get_orientation(void)
{
	return Orientation[m_Orientation];
}

void CPosition::set_xyo(const int & x, const int & y, const char & orient)
{
	m_x = x;
	m_y = y;
/*
storing the index of the array Orientation based on the input
*/
	switch (orient) {
	case 'N':
		m_Orientation = 0;
		break;
	case 'E':
		m_Orientation = 1;
		break;
	case 'S':
		m_Orientation = 2;
		break;
	case 'W':
		m_Orientation = 3;
		break;
	default:
		m_Orientation = 4;
		cerr << "invalid orientation" << endl;
		//exit(0);
		break;
	}
}


CPosition::~CPosition()
{
}
