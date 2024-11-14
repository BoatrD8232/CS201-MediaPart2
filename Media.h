#pragma once
#include <vector>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Media {

private :
  char type;
  string title;
  string name;
  int rating;
  string genre;
  int length;
  int yearReleased;

public:
	//PRE: The default constructor, takes no arguments.
	//POST: Sets all the string members to the empty string and all int members to -1;
  Media();

  //PRE: Takes in values for the type, title, name, rating, genre, length, and year.
  //POST: Sets the data members with the above inputs.
  Media (char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear);

  virtual void print(ostream& out, vector < Media*> media) = 0;
  void setType  (char c);
  void setTitle (string t);
  void setName  (string n);
  void setRating (int r);
  void setGenre(string g);
  void setLength(int l);
  void setYearReleased (int yr);


  char   getType();
  string getTitle();
  string getName();
  int    getRating();
  string getGenre();
  int    getLength();
  int    getYearReleased();
};

class Movie : public Media {
	private:
		vector<string> stars;
	public:
		//PRE: Takes in a list of stars in the movie. Also takes in values for the type, title, name, rating, genre, length, and year.
		//POST: Sets the data members with the above inputs.
		Movie(vector<string> inStars, char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear);
		Movie();
		vector<string> getStars();
		void setStars(vector<string> stars);
		void print(ostream& out, vector<Media*> mediaLib);
};

class Book : public Media {
	private:
		int weeksNYT;
	public:
		//PRE: Takes in an int storing the number of weeks the book spent as a NYT bestseller. 
		// Also takes in values for the type, title, name, rating, genre, length, and year.
		//POST: Sets the data members with the above inputs.
		Book(int weeks, char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear);
		Book();
		int getWeeks();
		void setWeeks(int weeks);
		void print(ostream& out, vector<Media*> mediaLib);

};

class Song : public Media {
	private:
		bool top40;
	public:
		//PRE: .Takes in a bool that stores if the book was a NYT top 40. Also takes in values for the type, title, name, rating, genre, length, and year.
		//POST: Sets the data members with the above inputs.
		Song(bool isTop40, char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear);
		Song();
		bool getTop40();
		void setTop40(bool isTop40);
		void print(ostream& out, vector<Media*> mediaLib);
};