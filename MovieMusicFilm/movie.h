#ifndef MOVIE_H
#define MOVIE_H


namespace common{


	using namespace std;


	class movie{
	public:
		movie();
		movie(string filename);
		void divide(string line,int sayi);
		int divideCommand(string line);
		int search(string vocab,string field);
		void operation();
		vector<int> sort(vector<string> name,string field);
		int findSearch(string vocab,string temp);
		vector<int> number;
		vector<string> title;
		vector<string> director;
		vector<string> year;
		vector<string> genre;
		vector<string> starring;
		vector<string> full;
	private:

		
	};
}
#endif