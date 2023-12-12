#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
/**
 * main - creates a new MovieHashTable and DirectorSkipList class and takes in 4 command-line arguments
 * Ad=fter it takes in the correct 4 argument, it parses the file and correctly fills both the HashTable with movienames 
 * and the nodes and the SkipList with the directors and nodes
 * It then prints out the amount of collisions in the HashTable and the menu for the user to pick from
 * Based on the user's option it goes to the required data structure to retrieve the data for the user
 * After the user choses to quit the program both deconstructors are called
 * 
 * parameters - N/A
 * return - N/A
 */
int main(int argc, char* argv[]) {
    // TODO
    // MovieHashTable x;
    // DirectorSkipList y;

    if(argc != 4)
    {
        cout << "Invalid number of arguments" << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size> <skipList Size>" << endl;
        return 0;
    }
    

    string file_name = argv[1];
    int hashTable_size = atoi(argv[2]);
        int skipList_size = atoi(argv[3]); // make sure thats the right function 

        MovieHashTable x(hashTable_size);
        DirectorSkipList y(skipList_size,DEFAULT_LEVELS);
        readMovieCSV(file_name, x, y);
        
   
    cout << "Number of Collisions: "<< x.getCollisions() << endl;
    int option;
    display_menu();
    cin >> option;

    
    while(option != 6)
    {
    if(option > 6 || option < 1)
    {
        cout << "Invalid Input. Please retry" << endl;
    }
    // find director of movie
    else if(option == 1)
        {
           
            cout << "Enter a movie name: " ;
            string title;
            cin.ignore(1000, '\n');
            getline(cin, title); 

            MovieNode* tmp = x.search(title);
            if(tmp == NULL)
            {
                cout << "Movie Not found!" << endl;
            }
            else
            {
                cout << "The director of " << tmp->title << " is " << tmp->director << "." << endl;
            }
            
        }
        // find director and num of movies
        else if(option == 2)
        {
            string director;
            cout << "Enter director name: ";
            cin.ignore(1000, '\n');
            getline(cin, director); 

            // search for director in skip list and return how many movies he/she directed  
            DirectorSLNode* tmp = y.search(director); // here
        
            if(tmp == NULL)
            {
                cout << "Director not found!" << endl;
    
            }
            else
            {
                cout << tmp->director << " has directed " << tmp->movies.size() << " movies." << endl;
            }
            
            
        }
        // find description of movie
        else if(option == 3)
        {
            string title;
            cout << "Enter a movie name: " ;
            cin.ignore(1000, '\n');
            getline(cin, title); 

            MovieNode* tmp = x.search(title);
            if(tmp == NULL)
            {
                cout << "Movie Not found!" << endl;
            }
            else
            {
                cout << "Title: " << tmp->title << " was made in " << tmp->year << " and stars " << tmp->actors << endl;
                cout << "Plot: " << tmp->description << ". It is directed by " << tmp->director << ". Its genre is " << tmp->genre << endl;
            }
            
        }
        // find director and the specific movies they directed
        else if(option == 4)
        {
            string director;
            cout << "Enter director name: ";
            cin.ignore(1000, '\n');
            getline(cin, director); 

            // print out all movies where direcetor has directed
            DirectorSLNode* tmp = y.search(director);
            
            if(tmp == NULL)
            {
                cout << "Director not found!" << endl;
            }
            else
            {

                cout << tmp->director << " has directed the following movies:" << endl;
                for(int i = 0; i < tmp->movies.size(); i++)
                {
                    cout << i << ": " << tmp->movies[i]->title << endl;
                }
            }
            
        }
        else if(option == 5)
        {
             y.prettyPrint();
        }

        cout << "---------------------------" << endl;
        display_menu();
        cin >> option;
        
    }
    // quit and call deconstructors
    
    if(option == 6)
    {
        cout << "Goodbye" << endl;
    }

    return 0;

}


// Function to parse a CSV line into a MovieNode object
/**
 * parseMovieLine - given a lin from the file, the function populates a Movie node appropiatley unless line given is in an invalid format
 * 
 * Parameter - string line (line from file with correct format)
 * Return - MovieNode* (node with new data from line in file)
 */ 
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
/**
 * readMovieCSV - opens a file and goes line by line and calls parseMovieLine to populate a node, then inserts movie title and node to HashTable
 * and movie director and node to Skip List
 * 
 * parameters- string filename (file), MovieHashTable &movieTable (address to HashTable), DirectorSkipList &directorList. (address to Skip List)
 * return - N/A
 */  
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    // TODO
    string line;

    ifstream fin;

    fin.open(filename);
    if(fin.is_open())
        {
            getline(fin, line);
            while(getline(fin, line))
            {
                MovieNode* tmp = parseMovieLine(line);
                movieTable.insert(tmp->title, tmp);
                directorList.insert(tmp->director, tmp); 
                
               
            }
        }

    fin.close();
}

// Function to display the menu options
/**
 * display_menu - prints out user menu to user
 * 
 * parameters - N/A
 * return - N/A
 */ 
void display_menu() {
    // TODO
   
    cout << "Please select an option: "<< endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Pretty Print Skip List" << endl;
    cout << "6. Quit" << endl;
    cout << endl;
    cout << "Enter an option: ";
    
}
