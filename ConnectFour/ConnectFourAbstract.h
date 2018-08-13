#include "Cell.h"

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

namespace ConnectFourMode{
	using std::istream;
	using std::ostream;
	using std::string;
	using std::vector;

class ConnectFourAbstract{
	private :
		virtual int playUserOne(string& save1,string& load1);//user 1 play here
		virtual int playUserTwo(string& save3,string& load3);//user 2 play here
		virtual int control(int playerNo,int loop);//its controlling the game for finish or contiune
	protected:
		int width;
		int height;
		Cell **gameBoard;
		vector<int> Undo;	
		virtual void SaveGame(string& save4);
		virtual void LoadGame(string& load4);
		int findColumn(char ch);//use it for computer play
	public:
		ConnectFourAbstract();// no parameter consructor
		ConnectFourAbstract(int width,int height);// two parameter constructor
		ConnectFourAbstract(const ConnectFourAbstract& cell1);//copy constructor
		int getWidth()const;// getter of width
		int getHeight()const;// getter of height
		int getFinish()const;//getter of finish
		char getFigure()const;// getter of figure
		char getgameType()const;
		Cell ** getBoard();
		void setWidth(const int width);//setter of width
		void setHeight(const int height);//setter of height
		int playGame();//playing game here and control of finish
		int input(const int size, string& save,string& load,int& choice);//taking a input for game
		void initialize();//if constructur take no parameter or two parameter use this initilaize
		void print();//print the current mode of board
		virtual int playComputer();//computer play here
		int downControl(int x,int y,int playerNo,char player,int loop);
		int sideContro(int x,int y,int playerNo,char player,int loop);
		int sagcapraz(int x,int y,int playerNo,char player,int loop);
		int solcapraz(int x,int y,int playerNo,char player,int loop);
		~ConnectFourAbstract();//destructor
	};
}
#endif