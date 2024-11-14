// CS201-MediaPt2
// NAME:  David Boatright
// 11/14/2024

#include "Functions.h"
#include "Media.h"


int main() {

    ifstream inList, inCommands;
    ofstream outFile, outErr;

    try {
        inList.exceptions(ifstream::failbit);
        inList.open("mediaList.txt");
        inCommands.exceptions(ifstream::failbit);
        inCommands.open("mediaCommands.txt");
        outFile.exceptions(ofstream::failbit);
        outFile.open("mediaReport.txt");
        outErr.exceptions(ofstream::failbit);
        outErr.open("mediaError.txt");
    }
    catch (ifstream::failure& fail) {
        cout << "Could not open input file" << endl;
        cout << fail.what() << endl;
        cout << fail.code() << endl;
        exit(1);
    }

    vector <Media*> myLib;

    // read data into myLib
    readMediaList(inList, outErr, myLib);
    inList.close();


    // prepare to read the commands
    string commandRecord, token;
    int rating;
    // The input line broken up and stored as strings.
    vector<string> tokens;

    getline(inCommands, commandRecord);
    char choice = commandRecord[0];

    while (choice != 'Q') {
        stringstream inss(commandRecord);
        tokens.clear();
        while (getline(inss, token, ',')) {
            tokens.push_back(token);
        }
        //you can parse input record into tokens here
        //OR
        //send commandRecord to another function to subdivide this work
        //this is an idea of how to handle this

        if (choice == 'M') {
            // Handles printing of movies.
            // If the line is just a letter.
            if (tokens.size() == 1) {
                printType(outFile, myLib, choice);
            }
            // If the line is a letter and a number.
            else if (isDigits(tokens.at(1))) {
                rating = stoi(tokens.at(1));
                printRating(outFile, outErr, myLib, choice, rating);
            }
            // If the line is a letter and a word.
            else {
                printGenre(outFile, outErr, myLib, choice, tokens.at(1));
            }
        }

        else if (choice == 'S') {
            // Handles printing of songs.
            // The same brancing logic as movies. 
            if (tokens.size() == 1) {
                printType(outFile, myLib, choice);
            }
            else if (isDigits(tokens.at(1))) {
                rating = stoi(tokens.at(1));
                printRating(outFile, outErr, myLib, choice, rating);
            }
            else {
                printGenre(outFile, outErr, myLib, choice, tokens.at(1));
            }
        }

        else if (choice == 'B') {
            // Handles printing of books.
            // The same brancing logic as movies. 
            if (tokens.size() == 1) {
                printType(outFile, myLib, choice);
            }
            else if (isDigits(tokens.at(1))) {
                rating = stoi(tokens.at(1));
                printRating(outFile, outErr, myLib, choice, rating);
            }
            else {
                printGenre(outFile, outErr, myLib, choice, tokens.at(1));
            }
        }

        else if (choice == 'T') {
            printTotals(outFile, myLib);
        }

        else if (choice == 'N') {
            addNewItem(outErr, outFile, myLib, tokens);
        }

        else if (choice == 'A') {
            // Handles the printing of all types of media.
            // If the input line is only a letter.
            if (tokens.size() == 1) {
                printMedia(outFile, myLib);
            }
            // If the input line is a letter and  something else, will handle the second item as a rating.
            else {
                rating = stoi(tokens.at(1));
                printRating(outFile, outErr, myLib, choice, rating);
            }
        }

        else if (choice == 'L') {
            //Prints the stars of a given movie.
            printPart(outFile, outErr, myLib, tokens.at(1));
        }

        else if (choice == 'F') {
            //Prints the list of movies a star is in.
            printStars(outFile, outErr, myLib, tokens.at(1));
        }

        else if (choice == 'K') {
            //Print media made/produced by a given name.
            printName(outFile, outErr, myLib, tokens.at(1));
        }

        else if (choice == 'Q') {
            cout << "Thank You for Using Media Everywhere" << endl;
            break;
        }

        else {
            outErr << "There is an error in the input command: " << commandRecord << "\n" << endl;
        }

        getline(inCommands, commandRecord);
        choice = commandRecord[0];
    }

    inCommands.close();
    outFile.close();
    outErr.close();
}
