#ifndef CELL_H
#define CELL_H

namespace ConnectFourMode{
	using std::istream;
	using std::ostream;
	using std::string;
	typedef enum user{
	user1 = 'X',
	user2 = 'O',
	computer = 'O',
	empty = '*',
	}user;

	class Cell{
			public:
			Cell();
			Cell(int rowNumber,char position);
			int getRowNumber()const;
			char getPosition()const;
			char getType()const;
			void setRowNumber(const int rowNumber);
			void setPosition(const char position);
			void setType(const char type);
			
			private:
			int rowNumber;
			char position;
			char type;
			
		};
}
	#endif