// Specification file for the HashList class
// Written By: Ashley Irawan
// IDE: CodeBlocks


#ifndef HASHLIST_H_INCLUDED
#define HASHLIST_H_INCLUDED
#include "Data.h"
#include <string>
#include <iostream>
#include <fstream>
using std::string;


template <class T>
struct HashNode
{
private:
    T item;
public:
    // constructors
    HashNode() {item = T();}
    HashNode(T anItem) {item = anItem;}
    // setters
    void setItem(const T & anItem) {item = anItem;}
    // getters
    T getItem() const {return item;}
};

template<class T>
class HashList {
private:
    HashNode<T> **table;
    int list_size;
    int count;
    int collisions;
    int longestCollision;

    //Fills array with the contents of hashList
    //array's contents are sorted by primary key
    void _sortedArray(HashNode<T>* array)
    {
        int j = 0;
        //Deposit contents of hashList into array
        for (int i = 0; i < list_size; i++)
            if (table[i])
                if(table[i]->getItem() != T())
                {
                    array[j].setItem(table[i]->getItem());
                    j++;
                }

        //Sorting
        for (int i = 0; i < count-1; i++)
            for (j = 0; j < count-i-1; j++)
                if (array[j].getItem() > array[j+1].getItem())
                {
                    HashNode<T> temp;
                    temp.setItem(array[j].getItem());
                    array[j].setItem(array[j+1].getItem());
                    array[j+1].setItem(temp.getItem());
                }
    }

public:
     //Constructor
     HashList(int size)
     {
         list_size = size;
         count = collisions = longestCollision = 0;
         table = new HashNode<T> * [list_size];
         for (int i = 0; i < list_size; i++)
         {
             table[i] = NULL;
         }
     }


     //Getters
     int getSize()  {return list_size;}
     int getCount() {return count;}
     int getCollisions() {return collisions;}
     int getLongestCollision() {return longestCollision;}
     //Function to return a 'bucket' key given any key value
     //This allows us to use keys larger than the size of our list
     //Assumes input_key is comprised of only numbers
     int hashFunc(int input_key)
     {
         return input_key % list_size;
     }


     //Insert an object into the hash table
     bool insert(T value, int key_to_index(const T &key, int list_size))
     {
         if (count >= list_size)
         {
             std::cout << "Error: List is full" << std::endl;
             return false;
         }
         int newKey = key_to_index(value, list_size);
         int collides = 0;
         //std::cout << newKey << ": ";
         while (table[newKey] != NULL && table[newKey]->getItem() != value)
         {
             //std::cout << newKey << " -> ";
             newKey = hashFunc(newKey + 1);
             collides++;
         }
         if (table[newKey] != NULL)
            delete table[newKey];
         table[newKey] = new HashNode<T>();
         table[newKey]->setItem(value);

         count++;
         collisions += collides;
         if (collides > longestCollision)
            longestCollision = collides;
         return true;
         //std::cout << newKey << " -> " << table[newKey]->getItem().getTitle() << std::endl;
     }


     //Finds a specified item in the table given a key
     //If the item is found, returns number of collisions and sets itemOut to found value
     //If item is not found, returns -1
     int searchKey(T &itemOut, const T key, int key_to_index(const T &key, int list_size))
     {
         int counter = 0;
         int newKey = key_to_index(key, list_size);
         while(table[newKey] != NULL && table[newKey]->getItem() != key)
         {
             counter++;
             newKey = hashFunc(newKey + 1);
         }
         if (table[newKey] == NULL)
         {
             return -1;
         }
         else if (table[newKey]->getItem() == T())
         {
             return -1;
         }
         else
         {
             itemOut = table[newKey]->getItem();
             return counter;
         }

     }


     //Removes a class given a key to the table
     //Returns true if successful, false if not
     bool remove(T &itemOut, const T key, int key_to_index(const T &key, int list_size))
     {
         int collides = 0;
         int newKey = key_to_index(key, list_size);
         while (table[newKey] != NULL)
         {
             if (table[newKey]->getItem() == key)
                break;
             newKey = hashFunc(newKey + 1);
             collides++;
         }
         if (table[newKey] == NULL)
            return false;
         else
         {
            itemOut = table[newKey]->getItem();
            table[newKey]->setItem(T());

            count--;
            collisions -= collides;
            if (collides == longestCollision)
                longestCollision = collides;

            return true;
         }
      }

     //Displays entire contents of the table
     //Contents are processed by _sortedArray
     void display()
     {
        if (count == 0)
        {
            std::cout << "List is empty!" << std::endl;
            return;
        }
        HashNode<T> array[count];
        _sortedArray(array);
        for (int i = 0; i < count; i++)
            std::cout << array[i].getItem() << std::endl;
    }

    //Outputs contents of table into output file
    //Contents are processed by _sortedArray
    void output()
    {
        std::ofstream outFile;
        outFile.open("output.txt");
        if (!outFile)
        {
            std::cout << "Failed to generate output file" << std::endl;
            return;
        }
        HashNode<T> array[count];
        _sortedArray(array);
        for (int i = 0; i < count; i++)
            outFile << array[i].getItem() << "\n";
        outFile.close();
        std::cout << "List contents have been written to output.txt.\n\n";
    }


      //Returns the hash load of the list
      double hashLoad()
      {
            return count / (list_size * 1.0);
      }

      //Destructor
      ~HashList()
      {
        for (int i = 0; i < list_size; i++)
        {
            if (table[i] != NULL)
                delete table[i];
            delete[] table;
        }
      }
};

#endif // HASHLIST_CLASS_H_INCLUDED
