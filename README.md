<img src="https://www.colorado.edu/cs/profiles/express/themes/ucb/images/cu-boulder-logo-text-black.svg" alt="CU Boulder Logo" width="500">

# CSCI 2270: Data Structures <br/> IMDB Movies Database Project

This project is a simple implementation of a movie database using C++ and two data structures: a hash table and a skip list. Please go through *CSCI2270_Spring23_Project.pdf* for the detailed instructions.

## Requirements

1. C++ compiler 
2. A CSV file containing movie data (e.g. IMDB-Movie-Data.csv)

## Installation

1. Clone the repository
2. Compile the code : `g++ -std=c++11 driver.cpp MovieHashTable.cpp DirectorSkipList.cpp -o movie-db`
3. Run the program: `./movie-db IMDB-Movie-Data.csv 2000 2000`
4. Follow the on-screen menu to perform different operations on the movie database.

## Data Structures

This project uses two data structures to store and retrieve movie data: a hash table and a skip list.

### Hash Table
The hash table is used to map movie titles to `MovieNode` objects. 
The hash function used is a custom function that takes the sum of the ASCII codes of all characters in the title string and calculates the modulo of the sum by the hash table size. Students must use their identikey to come up with a creative hash function that minimizes collisions
for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.

### Skip List
The skip list is used to map director names to `DirectorSLNode` objects, which contain a vector of `MovieNode` pointers. The skip list is a probabilistic data structure that allows for efficient search, insertion, and deletion of elements. It is implemented using a linked list with multiple levels, where each level has fewer nodes than the level below it. The skip list used in this project has a fixed number of levels (10) and a fixed capacity (2000).


Question 1:
I used chaining as my hash resolution method. I chose it because it felt like it was more organized way to store data because it goes to the hash index instead of checking through the rest of the hash table if its not there if I used linear probing.

Question 2:
My hash function takes in the movie name, then adds my identikey "brho7443" to it to make it unique. 
Then it gets an index from that value of all the characters modulo table size. If some movie node is already stored
at that specific index, then I use chaining to point the new node's next to the existing node and put the new node into the 0th postion
of the index. To find a certain movie, it goes to the specific index and checks if the 0th node at the index matches the movie, if not then it goes through
the linked list at that index to try and find it. If it still isn't found, then it tells the user the movie isn't in the hash table

Question 3:
I did implement the skip list because I wanted practice with a new data structure especially one as powerful and efficient as a skiplist.

Question 4:
Although the PrettyPrint function was in the write up, I added it as an option to the menu for the user to see the organization of the skiplist.


