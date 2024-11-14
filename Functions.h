#pragma once
#include "Media.h"

//PRE: Takes in a string and checks is it is numeric
//POST: Returns true if numeric, false otherwise.
bool isDigits(string str1);

//PRE: Takes in a string and checks if it is a valid type for a media item.
//POST: Returns true if valid, false otherwise.
bool isValidType(string type);

//PRE: Takes in the input stream of the list file, the output stream, and the emtpy vector of media
//POST: Fills the vector with media and outputs any errors.
int  readMediaList(istream &i, ostream &o, vector<Media*> &m);

//PRE: Takes in the output stream and the vector of media to be printed.
//POST: Outputs the total list of media.
void printMedia(ostream& outFile, vector<Media*>& media);

//PRE: Takes in the output stream, the vector of media to be printed, and the character 
// representing the type.
//POST: Outputs the list of the given type.
void printType(ostream& outFile, vector<Media*>& media, char type);

//PRE: Takes in the output stream, the error ouput stream, the vector of media to be printed,
// and the character represneting the type.
//POST: Outputs the list of items of the given type and meeting the rating requirement.
void printRating(ostream& outFile, ostream& errFile, vector<Media*>& media, char type, int rating);

//PRE: Takes in the output stream, the error output stream,  the vector of media to be printed, the 
// type character, and the desired genre.
//POST: Outputs a list of media of the given type and genre.
void printGenre(ostream& outFile, ostream& errFile, vector<Media*>& media, char type, string genre);

//PRE: Takes in the output stream and the vector of media to be counted.
//POST: Outputs the total of each type of media.
void printTotals(ostream& outFile, const vector<Media*>& media);

//PRE: Takes in the output stream, the error output stream,  the vector of media to be printed, and the string containing the movie title.
//POST: Outputs the stars if the movie that is found.
void printPart(ostream& outFile, ostream& errFile, const vector<Media*>& media, string part);

//PRE: Takes in the output stream, the error output stream,  the vector of media to be printed, and the star to be found in the list of movies.
//POST: Outputs the movies that star the given actor.
void printStars(ostream& outFile, ostream& errFile, const vector<Media*>& media, string star);

//PRE: Takes in the output stream, the error output stream,  the vector of media to be searched, and the name to be found.
//POST: Outputs the media that was written or produced by the given name.
void printName(ostream& outFile, ostream& errFile, const vector<Media*>& media, string name);

//PRE: takes in the error output stream, the output stream, the vector containing the media, and the 
// vector of strings containing the input line.
//POST: Adds the input line as a new piece of media and adds it to the list or outputs an error.
void addNewItem(ostream& errFile, ostream& outFile, vector<Media*>& media, const vector<string>& tokens);
