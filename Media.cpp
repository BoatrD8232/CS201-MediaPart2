#include "Media.h"

Media::Media(){
  this->type = ' ';
  this->title = " ";
  this->name = " ";
  this->rating = -1;
  this->genre = " ";
  this->length = -1;
  this->yearReleased = -1;

}

Media::Media(char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear) {
	type = inType;
	title = inTitle;
	name = inName;
	rating = inRating;
	genre = inGenre;
	length = inLength;
	yearReleased = inYear;
}

void Media::setType(char c) { type = c; }
void Media::setTitle(string t) { title = t; }
void Media::setName(string n) { name = n; }
void Media::setRating(int r) { rating = r; }
void Media::setGenre(string g) { genre = g; }
void Media::setLength(int l) { length = l; }
void Media::setYearReleased(int yr) { yearReleased = yr; }

char   Media::getType() { return type; }
string Media::getTitle() { return title; }
string Media::getName() { return name; }
int    Media::getRating() { return rating; }
string Media::getGenre() { return genre; }
int    Media::getLength() { return length; }
int    Media::getYearReleased() { return yearReleased; }

Movie::Movie(vector<string> inStars, char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear) : Media(inType, inTitle, inName, inRating, inGenre, inLength, inYear) { stars = inStars; }
Movie::Movie() : Media() {};
vector<string> Movie::getStars() { return stars; }
void Movie::setStars(vector<string> inStars) { stars = inStars; }
void Movie::print(ostream& out, vector<Media*> mediaLib) {
	out << left << setw(40) << getTitle() << setw(8) << getYearReleased()
		<< setw(8) << getRating() << setw(25) << getGenre() << "Stars: ";
	for (int i = 0; i < stars.size(); ++i) {
		out << stars.at(i) << ", ";
	}
	out << endl;
}

Book::Book(int weeks, char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear) : Media(inType, inTitle, inName, inRating, inGenre, inLength, inYear) { weeksNYT = weeks; }
Book::Book() : Media() { weeksNYT = 0; };
int Book::getWeeks() { return weeksNYT; }
void Book::setWeeks(int weeks) { weeksNYT = weeks; }
void Book::print(ostream& out, vector<Media*> mediaLib) {
	out << left << setw(40) << getTitle() << setw(8) << getYearReleased()
		<< setw(8) << getRating() << setw(25) << getGenre();
	out << "Weeks NYT: " << weeksNYT;
	out << endl;
}

Song::Song(bool isTop40, char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear) : Media(inType, inTitle, inName, inRating, inGenre, inLength, inYear) { top40 = isTop40; }
Song::Song() : Media() { top40 = false; };
bool Song::getTop40() { return top40; }
void Song::setTop40(bool isTop40) { top40 = isTop40; }
void Song::print(ostream& out, vector<Media*> mediaLib) {
	out << left << setw(40) << getTitle() << setw(8) << getYearReleased()
		<< setw(8) << getRating() << setw(25) << getGenre();
	if (top40) {
		out << "Top 40 Hit";
	}
	else {
		out << "___";
	}
	out << endl;
}


 
 