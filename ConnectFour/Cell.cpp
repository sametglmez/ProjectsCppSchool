#include <iostream>
#include "Cell.h"


namespace ConnectFourMode{
	using std::istream;
	using std::ostream;
	using std::string;

	Cell::Cell() :rowNumber(0) , position(empty)
	{

	}
	Cell::Cell(int rowNumber,char position){
		setRowNumber(rowNumber);
		setPosition(position);
	}
	int Cell::getRowNumber()const{return rowNumber;}
	char Cell::getPosition()const{return position;}
	char Cell::getType()const{return type;}
	void Cell::setRowNumber(const int rowNumber){
		this->rowNumber= rowNumber;
		}
		void Cell::setPosition(const char position){
			this->position = position;
		}
		void Cell::setType(const char type){
			this->type = type;
		}
}