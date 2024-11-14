#include "Functions.h"
#include "Media.h"


bool isDigits(string str1) {
    return (str1.find_first_not_of("-1234567890") == string::npos);
}

bool isValidType(string type) {
    return (type.find_first_not_of("MBS") == string::npos);
}
 
int readMediaList(istream& inFile, ostream& outFile, vector<Media*>& mediaLib) {
    //The input line and each word in the line.
    string line, word;
    // Creates a temporary media that will be added to the vector.
    Media* tempMedia = nullptr;
    // Stores the words in the (expected) order: type, title, name, rating, genre, length, year.
    vector<string> words;
    // Stores a list of stars to be used in movie declarations;
    vector<string> tempStars;
    string type, title, name, genre;
    // Stores the first letter of the type.
    char tyChar;
    int rating, length, year;
    while (getline(inFile, line)) {
        stringstream inss(line);
        words.clear();
        while (getline(inss, word, ',')) {
            words.push_back(word);
        }
        // Ends the loop if the quit chracter is found.
        if (words.at(0) == "Q") {
            break;
        }
        type = words.at(0);
        if (!isValidType(type)) {
            outFile << "Error- Invalid type: " << line << "\n" << endl;
            continue;
        }
        title = words.at(1);
        name = words.at(2);
        genre = words.at(4);
        try {
            rating = stoi(words.at(3));
            length = stoi(words.at(5));
            year = stoi(words.at(6));
        }
        // Invalid items in the numeric fields.
        catch (invalid_argument) {
            outFile << "Error- invalid stoi argument: " << line << "\n" << endl;
            continue;
        }
        if (rating <= 0 || length <= 0 || year <= 0) {
            outFile << "Error- numeric value <= 0: " << line << "\n" << endl;
            continue;
        }
        if (rating > 10) {
            outFile << "Error- invalid rating: " << line << "\n" << endl;
            continue;
        }
        if (year < 1920 || year > 2024) {
            outFile << "Error- invalid year: " << line << "\n" << endl;
            continue;
        }
        tyChar = type.at(0);
        // Checks what type of media to create and makes it. Stores the newly created media in tempMedia.
        switch (tyChar) {
            case 'M':
                tempStars.clear();
                //Fills the list of stars.
                for (int i = 7; i < words.size(); ++i) {
                    tempStars.push_back(words.at(i));
                }
                tempMedia = new Movie(tempStars, tyChar, title, name, rating, genre, length, year);
                break;
            case 'B':
                try {
                    int weeks = stoi(words.at(7));
                    tempMedia = new Book(weeks, tyChar, title, name, rating, genre, length, year);
                }
                catch (invalid_argument) {
                    outFile << "Error in reading weeks: " << line << endl << endl;
                    tempMedia = nullptr;
                }
                break;
            case 'S':
                try {
                    bool isTop40 = stoi(words.at(7));
                    tempMedia = new Song(isTop40, tyChar, title, name, rating, genre, length, year);
                }
                catch(invalid_argument){
                    outFile << "Error in reading Top 40: " << line << endl << endl;
                    tempMedia = nullptr;
                }
                break;
        }
        if (tempMedia == nullptr) {
            continue;
        }
        mediaLib.push_back(tempMedia);
    }
    return 0;
}

void printMedia(ostream& outFile, vector<Media*>& media) { 
    // Count is used to keep track of what number each item is in the list.
    int count = 1;
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your Media List\n" << endl;
    outFile << left << setw(4) << "#" << setw(40) << "Title" << setw(8) << "Year" 
            << setw(8) << "Rating" << setw(25) << "Genre" << "Other Fields" << endl;
    for (const auto &i : media) {
        outFile << setw(4) << count;
        i->print(outFile, media);
        count++;
    }
    outFile << "\n\n" << endl;
}

void printType(ostream& outFile, vector<Media*>& media, char type) {
    string dispType;
    // Count is used to keep track of what number each item is in the list.
    int count = 1;
    // Chooses a type for use in displaying.
    switch (type) {
        case 'M':
            dispType = "Movie";
            break;
        case 'S':
            dispType = "Song";
            break;
        case 'B':
            dispType = "Book";
            break;
    }
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your " << dispType << " List\n" << endl;
    outFile << left << setw(4) << "#" << setw(40) << "Title" << setw(8) << "Year"
        << setw(8) << "Rating" << setw(25) << "Genre" << "Other Fields" << endl;
    for (const auto &i : media) {
        if (i->getType() == type) {
            outFile << setw(4) << count;
            i->print(outFile, media);
        }
        count++;
    }
    outFile << "\n\n" << endl;
}

void printRating(ostream& outFile, ostream& errFile, vector<Media*>& media, char type, int rating) {
    // Count is used to keep track of what number each item is in the list.
    int count = 1;
    if (rating > 10 || rating < 0) {
        errFile << "Error- rating of " << rating << " is invaild\n" << endl;
        return;
    }
    string dispType;
    // Chooses a type for use in displaying.
    switch (type) {
    case 'M':
        dispType = "Movie";
        break;
    case 'S':
        dispType = "Song";
        break;
    case 'B':
        dispType = "Book";
        break;
    case 'A':
        dispType = "Media";
        break;
    }
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your " << dispType << " List With Rating >= " << rating << "\n" << endl;
    outFile << left << setw(4) << "#" << setw(40) << "Title" << setw(8) << "Year"
        << setw(8) << "Rating" << setw(25) << "Genre" << "Other Fields" << endl;
    // Checks if all types of media will be output or only a specific type.
    if (type != 'A') {
        for (const auto& i : media) {
            if (i->getRating() >= rating && i->getType() == type) {
                outFile << setw(4) << count;
                i->print(outFile, media);
            }
            count++;
        }
    }
    else {
        for (const auto& i : media) {
            if (i->getRating() >=  rating) {
                outFile << setw(4) << count;
                i->print(outFile, media);
            }
            count++;
        }
    }
    outFile << "\n\n" << endl;
}

void printGenre(ostream& outFile, ostream& errFile, vector<Media*>& media, char type, string genre) {
    string dispType;
    // Count is used to keep track of what number each item is in the list.
    int count = 1;
    // Stores if any media has been output.
    bool printed = false;
    // Chooses a type for use in displaying.
    switch (type) {
    case 'M':
        dispType = "Movie";
        break;
    case 'S':
        dispType = "Song";
        break;
    case 'B':
        dispType = "Book";
        break;
    }
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your " << dispType << " List For Genre " << genre <<  "\n" << endl;
    outFile << left << setw(4) << "#" << setw(40) << "Title" << setw(8) << "Year"
        << setw(8) << "Rating" << setw(25) << "Genre" << "Other Fields" << endl;
    for (const auto& i : media) {
        if (i->getGenre() == genre && i->getType() == type) {
            outFile << setw(4) << count;
            i->print(outFile, media);
            printed = true;
        }
        count++;
    }
    // If no media of the genre found, output an error.
    if (!printed) {
        outFile << "No items of genre " << genre << endl;
        errFile << "Error - No items of genre " << genre << "\n" <<endl;
    }
    outFile << "\n\n" << endl;
}

void printTotals(ostream& outFile, const vector<Media*>& media) {
    int numMovie = 0, numBook = 0, numSong = 0;
    char type;
    for (int i = 0; i < media.size(); i++) {
        // Totals the number of types.
        type = media.at(i)->getType();
        switch (type) {
        case 'M':
            numMovie++;
            break;
        case 'S':
            numSong++;
            break;
        case 'B':
            numBook++;
            break;
        }
    }
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your Media Library" << endl;
    outFile << setw(3) << "#" << "Type" << endl;
    outFile << setw(3) << numMovie << "Movies" << endl;
    outFile << setw(3) << numBook << "Books" << endl;
    outFile << setw(3) << numSong << "Songs" << endl;
    outFile << setw(3) << numMovie + numBook + numSong << "Items" << endl;
    outFile << "\n\n" << endl;
}

void printPart(ostream& outFile, ostream& errFile, const vector<Media*>& media, string title) {
    // Printed stores if any ouput has been written. If the final value of printed is false, an error is output.
    bool printed = false;
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Stars of the Movie " << title << "\n" << endl;
    for (int i = 0; i < media.size(); i++) {
        if (media.at(i)->getType() == 'M' && media.at(i)->getTitle() == title) {
            printed = true;
            const vector<string>& stars = static_cast<Movie*>(media.at(i))->getStars();
            for (int i = 0; i < stars.size(); ++i) {
                outFile << stars.at(i) << endl;
            }
            printed = true;
            break;
        }
    }

    if (!printed) {
        outFile << "No movie named " << title  << " found." << endl;
        errFile << "Error - No movie named " << title << "\n" << endl;
    }
    outFile << "\n\n" << endl;
}

void printStars(ostream& outFile, ostream& errFile, const vector<Media*>& media, string star) {
    // Printed stores if any ouput has been written. If the final value of printed is false, an error is output.
    bool printed = false;
    // Found stores if a star has been found in a movie. If set to true, that movie is ouput to the ouput file.
    bool found;
    vector<string> stars;
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Movies starring " << star << "\n" << endl;
    for (int i = 0; i < media.size(); i++) {
        found = false;
        if (media.at(i)->getType() == 'M') {
            stars.clear();
            stars = static_cast<Movie*>(media.at(i))->getStars();
            for (int i = 0; i < stars.size(); ++i) {
                if (stars.at(i) == star) {
                    found = true;
                    break;
                }
            }
        }
        if (found) {
            printed = true;
            outFile << media.at(i)->getTitle() << endl;
        }
    }
    if (!printed) {
        outFile << "No movies starring " << star << endl;
        errFile << "Error - No movies starring " << star << "\n" << endl;
    }
    outFile << "\n\n" << endl;
}

void printName(ostream& outFile, ostream& errFile, const vector<Media*>& media, string name) {
    // Count is used to keep track of what number each item is in the list.
    int count = 1;
    // Printed stores if any ouput has been written. If the final value of printed is false, an error is output.
    bool printed = false;
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Media produced by " << name << "\n" << endl;
    outFile << left << setw(4) << "#" << setw(40) << "Title" << setw(8) << "Year"
        << setw(8) << "Rating" << setw(25) << "Genre" << "Other Fields" << endl;
    for (const auto& i : media) {
        if (i->getName() == name) {
            outFile << setw(4) << count;
            i->print(outFile, media);
            printed = true;
        }
        count++;
    }
    if (!printed) {
        outFile << "No items produced by " << name << endl;
        errFile << "Error - No items produced by " << name << "\n" << endl;
    }
    outFile << "\n\n" << endl;
}

void addNewItem(ostream& errFile, ostream& outFile, vector<Media*>& media, const vector<string>& tokens) {
    // The temporary media to be added to the vector.
    Media* tempMedia = nullptr;
    string type, title, name, genre;
    char tyChar;
    int rating, length, year;
    // Stores a list of stars to be used in movie declarations;
    vector<string> tempStars;

    type = tokens.at(1);
    tyChar = type.at(0);
    title = tokens.at(2);
    name = tokens.at(3);
    genre = tokens.at(5);
    if (!isValidType(type)) {
        errFile << "Cannot add item- Invalid type: " << type << "\n" << endl;
        return;
    }

    try {
        rating = stoi(tokens.at(4));
        length = stoi(tokens.at(6));
        year = stoi(tokens.at(7));
    }
    // Invalid items in the numeric fields.
    catch (invalid_argument) {
        errFile << "Cannot add item- invalid stoi argument: " << title << "\n" << endl;
        return;
    }
    if (rating <= 0 || length <= 0 || year <= 0) {
        errFile << "Cannot add item- numeric value <= 0: " << title << "\n" << endl;
        return;
    }
    if (rating > 10) {
        errFile << "Cannot add item- invaild rating: " << title << "\n" << endl;
        return;
    }
    if (year < 1920 || year > 2024) {
        errFile << "Cannot add item- invalid year: " << title << "\n" << endl;
        return;
    }
    switch (tyChar) {
    case 'M':
        tempStars.clear();
        //Fills the list of stars
        for (int i = 8; i < tokens.size(); ++i) {
            tempStars.push_back(tokens.at(i));
        }
        tempMedia = new Movie(tempStars, tyChar, title, name, rating, genre, length, year);
        break;
    case 'B':
        try {
            int weeks = stoi(tokens.at(8));
            tempMedia = new Book(weeks, tyChar, title, name, rating, genre, length, year);
        }
        catch (invalid_argument) {
            errFile << "Error in reading weeks: " << title << endl << endl;
            tempMedia = nullptr;
        }
        break;
    case 'S':
        try {
            bool isTop40 = stoi(tokens.at(8));
            tempMedia = new Song(isTop40, tyChar, title, name, rating, genre, length, year);
        }
        catch (invalid_argument) {
            errFile << "Error in reading Top 40: " << title << endl << endl;
            tempMedia = nullptr;
        }
        break;
    }
    if (tempMedia == nullptr) {
        return;
    }
    outFile << title << " was added to your list\n\n" << endl;
    media.push_back(tempMedia);
}