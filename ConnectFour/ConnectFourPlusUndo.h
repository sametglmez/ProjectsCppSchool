#include "ConnectFourAbstract.h"
#include "Cell.h"
#include "ConnectFourPlus.h"

#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

namespace ConnectFourMode{

	using std::istream;
	using std::ostream;
	using std::string;

	class ConnectFourPlusUndo:public ConnectFourPlus{

	public:
		ConnectFourPlusUndo();
		ConnectFourPlusUndo(int width,int height);
		~ConnectFourPlusUndo();
		void undoBack();
		int playComputer();//computer play here
		void SaveGame(string& save4);
		void LoadGame(string& load4);
	private:
		int playUserOne(string& save1,string& load1);
		int playUserTwo(string& save3,string& load3);
		//int input(const int size, string& save,string& load,int& choice);//taking a input for game
	};
}
#endif