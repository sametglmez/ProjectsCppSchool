#ifndef MUSIC_H
#define MUSIC_H


namespace common{


	using namespace std;


	class music{
	public:
		music();
		music(string filename);
		void divide(string line,int sayi);
		int divideCommand(string line);
		int search(string vocab,string field);
		void operation();
		vector<int> sort(vector<string> name,string field);
		int findSearch(string vocab,string temp);
		vector<int> number;
		vector<string> title;
		vector<string> artist;
		vector<string> year;
		vector<string> genre;
		vector<string> full;
	private:

		
	};
}
#endif
