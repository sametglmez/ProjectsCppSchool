#include "ConnectFourAbstract.h"
#include "Cell.h"

#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H


namespace ConnectFourMode{
	using std::istream;
	using std::ostream;
	using std::string;


	class ConnectFourDiag : public ConnectFourAbstract{
	public:
		ConnectFourDiag();
		ConnectFourDiag(int width,int height);
		~ConnectFourDiag();
		int playUserOne(string& save1,string& load1);//user 1 play here
		int playUserTwo(string& save3,string& load3);//user 2 play here
		int playComputer();//computer play here
		void SaveGame(string& save4);
		void LoadGame(string& load4);
	private:
		int control(int playerNo,int loop);
	};
}
#endif