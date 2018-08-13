//definition of book class

#ifndef BOOK_H
#define BOOK_H

//my namespace
namespace common{

	using namespace std;


	class book{
	public:
		book();//no parameter constructor
		book(string filename);//one parameter constructor
		void divide(string line,int sayi);//this function for divide line for each field
		int divideCommand(string line);//divie command.txt file
		vector<int> sort(vector<string> name,string field);//sort
		int search(string vocab,string field);//search funciton
		int findSearch(string vocab,string temp);//sub funciton for search
		void operation();//all operations doing in this funciton
		//All variable
		vector<int> number;
		vector<string> title;
		vector<string> authors;
		vector<string> year;
		vector<string> tags;
		vector<string> full;
	private:

		
	};
}
#endif
