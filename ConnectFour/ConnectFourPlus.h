#include "ConnectFourAbstract.h"
#include "Cell.h"

#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H


namespace ConnectFourMode{
	using std::istream;
	using std::ostream;
	using std::string;


	class ConnectFourPlus : public ConnectFourAbstract{
	public:
		ConnectFourPlus();
		ConnectFourPlus(int width,int height);
		~ConnectFourPlus();
		int control(int playerNo,int loop);
		int playUserOne(string& save1,string& load1);//user 1 play here
		int playUserTwo(string& save3,string& load3);//user 2 play here
		int playComputer();//computer play here
		void SaveGame(string& save4);
		void LoadGame(string& load4);
		//void undo();

	private:
		
	};
}
#endif