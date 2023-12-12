#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

// Constructor for MovieHashTable with default size
/**
 * MovieHashTable - sets default table_size to 1001 and creates new hash table of that size
 * Parameters - N/A
 * Return - N/A
*/
MovieHashTable::MovieHashTable() {
    // TODO
    table_size = DEFAULT_HTABLE_CAPACITY; 
    table = new MovieNode*[table_size];
    for(int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
}

// Constructor for MovieHashTable with given size
/**
 * MovieHashTable - sets table_size to parameter given and creates hash table of that size
 * Parameter - int s (size of hash table)
 * return - N/A
 */
MovieHashTable::MovieHashTable(int s) {
    // TODO
    table_size = s;
    table = new MovieNode*[table_size];
    for(int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
}

// Destructor for MovieHashTable that deletes all nodes in the hash table
/**
 * ~MovieHashTable - goes to every index in hash and deletes all nodes stored at each index
 * Parameters - N/A
 * Return - N/A
*/
MovieHashTable::~MovieHashTable() {
    // TODO
    for(int i = 0; i < table_size; i ++)
    {
        if(table[i] != nullptr)
        {
            if(table[i]->next != nullptr)
            {
                MovieNode* prev = table[i];
                MovieNode* curr = table[i];

                while(curr->next != nullptr)
                {
                    prev = curr;
                    curr = curr->next;
                    delete prev;
                }

                delete curr;
            }
            else
            {
                delete table[i];
            }
        }
    }
    delete[] table;

}

// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
/**
 * hash - takes in title parameter and adds my identikey to it then calculates the size of string from ASCI values of each character
 * then take modulo the size of the table to get a unique index with limited collision from my identikey
 * Parameter - string title
 * return - int (index)
*/
int MovieHashTable::hash(string title) {
    // TODO
    int index = 0;
    string tmp = title + "brho7443";
    for(int i = 0; i < tmp.length(); i++)
    {
        index = index + tmp[i];
    }
    index = index % table_size;
    return index;
}

// Inserts a movie node into the hash table with the specified title
/**
 * insert - takes in title and the movie node then calls hash function to get hash index of movie. Then checks if there is a collision at index. 
 * If so, point next of given movie node to movie node already at index (chaining)
 * If not, put movie node at index
 * Parameters - string title (movie title) and MovieNode* movie (node of movie)
 * Return - N/A
 */
void MovieHashTable::insert(string title, MovieNode* movie) {
    // TODO
    
    int index = hash(title);
   
        if(table[index] == NULL)
        {
            table[index] = movie;
        }
        else
        {
            movie->next = table[index];
            table[index] = movie;
            setCollisions();
        }

    }


// Searches for a node in the hash table with the specified title
/**
 * search - Takes in title of movie, uses hash function to get index of that title and goes to that index in hash table. 
 * If node at index has the same title as given return that node
 * If 1st node's title at index doesn't match title, then go through all nodes in index. If it is found, return node, if not found return nullptr
 * Parameters - string title (movie title)
 * Return - MovieNode* (pointer to node with same title or nullptr)
 */
MovieNode* MovieHashTable::search(string title) {
    // TODO
    int index = hash(title);
    
    MovieNode* tmp = table[index];
    if(table[index] != NULL)
    {
    if(table[index]->title == title)
    {
        return tmp;
    }
    else
    {
        while(tmp->next != NULL)
        {
            if(tmp->title == title)
            {
                return tmp;
            }
            tmp = tmp->next;
        }
    }
    }
    return nullptr;
}

// Returns the number of collisions that have occurred during insertion into the hash table
/**
 * getCollisions - returns the number of collision after hash table is filled with data
 * Parameters - N/A
 * Return - int n_collisions (number of collisions in hash)
*/
int MovieHashTable::getCollisions() {
    // TODO
    return n_collisions;
}

// Increments the number of collisions that have occurred during insertion into the hash table
/**
 * setCollisions - every time function is called increment number of collision variable by 1
 * Parameters - N/A
 * Return - N/A
*/
void MovieHashTable::setCollisions() {
    // TODO
    n_collisions = n_collisions + 1;
}
