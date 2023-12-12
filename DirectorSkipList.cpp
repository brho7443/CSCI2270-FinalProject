#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;

// Constructor for DirectorSkipList with default capacity and levels
/**
 * DirectorSkipList - creates a new DirectorSkipList class with the default capacity and levels and sets size to 0
 * 
 * parameters - N/A
 * return - N/A
 */
DirectorSkipList::DirectorSkipList() {
    // TODO
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
    head = new DirectorSLNode("", levels);
    size = 0;
}

// Constructor for DirectorSkipList with given capacity and levels
/**
 * DirectorSkipList - creates a new DirectorSkipList class with given capacity and max levels and sets size to 0 and the head director to an empty string
 * 
 * paramters - int _cap (capacity) and int _levels (max levels)
 * return - N/A
 */
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    // TODO
    capacity = _cap;
    levels = _levels;
    head = new DirectorSLNode("", _levels);
    size = 0;
}

// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
/**
 * ~DirectorSkipList - goes to each node in level 0 (all nodes) and deletes them 
 * 
 * parameters- N/A
 * return - N/A
 */
DirectorSkipList::~DirectorSkipList() {
    // TODO
    DirectorSLNode* tmp = head;
    DirectorSLNode* prev = head;
   
    while(tmp!=nullptr)
    {
        prev=tmp->next[0];
        delete tmp;
        tmp = prev;
    }
}

// Inserts a movie node into the skip list with the specified director
/**
 * insert - given a director and a movie node, it first finds where to insert by comparing directors. Then if the SLNode it is on is the same director it jsut adds the 
 * movie to the node already there, or if it isn't equal then it creates a new SLNode and correctly inserts it
 * 
 * parameters - string director (director name) and MovieNode* _movie (node with movie data in it)
 * return - void
 */
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    // TODO
    // find where to insert
    DirectorSLNode* curr = head;
    vector<DirectorSLNode*> prev(levels, nullptr);

    
    for(int i = levels-1; i >= 0 ; i--)
    {
        
        while(curr->next[i] != nullptr && curr->next[i]->director < director)
        {
            curr = curr->next[i];
        }
        
        prev[i] = curr;
        //cout <<"previous dir: " << prev[i]->director << endl;       
    }
   
   
    curr = curr->next[0];
    
    

    // insert node
    if(curr != NULL && curr->director == director )
    { 
        curr->addMovie(_movie);
    }
    else
    {
        
         // find num of levels in node
        int n_levels = 1;

        while(n_levels < levels && (rand() % 2) == 0)
        {
            n_levels++;
        }

        // create new node
        DirectorSLNode* new_node = new DirectorSLNode(director, n_levels);
       
        // insert node at each level
          for(int i = 0; i < n_levels; i++)
          {
                
                new_node->next[i] = prev[i]->next[i];           
                prev[i]->next[i] = new_node;     
                
          }
        
        
          new_node->addMovie(_movie);
          size++;
    }

}

// Searches for a node in the skip list with the specified director
/**
 * search - search traverses the skip list through the levels until it gets to the node where the director should be. If the directors match, then return the curr node
 * If not then return nullptr
 * 
 * parameters- string director
 * return - DirectorSLNode*
 */
DirectorSLNode *DirectorSkipList::search(string director) {
    // TODO
    DirectorSLNode* curr = head;

    
    for(int i = levels-1; i >= 0; i--)
    {
        while(curr->next[i] != NULL && curr->next[i]->director < director)
        {  
            curr = curr->next[i];
        }
        
    }
    
    curr = curr->next[0];
   if (curr!=nullptr)
   {
    cout << "director:  " << curr->director <<  endl;
   }

    if(curr != NULL && curr->director == director)
    {
        return curr;
    }

    return nullptr;
}

// Pretty-prints the skip list
/**
 * prettyPrint - prints out each level of the SkipList with the nodes pointing to eachother in the specific levels
 * 
 * parameters- N/A
 * return - void
 */
void DirectorSkipList::prettyPrint() {
    // TODO
    for(int i=levels-1; i >= 0; i--)
    {
        cout << "Level: " << i+1 << ": ";
        DirectorSLNode* tmp = head->next[i];
        while(tmp != NULL &&tmp->next[i]!= NULL)
        {
            cout << tmp->director << " ----> ";
            tmp = tmp->next[i];
        }
        cout << "NULL" << endl;
    }
}
