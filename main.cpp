//main.cpp
//main.cpp
#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <fstream>

#include "BinarySearchTree.h"
#include "BinaryTree.h"
#include "BinaryNode.h"
#include "BSTData.h"
#include "HashList.h"
#include "Data.h"
using namespace std;


void printInfo();
void menuDisplay();
void inputData(string, HashList<Data>&, BinarySearchTree<BSTData>&);
void buildBST(BinarySearchTree<BSTData>& bst, string crn, string course);
int hashSize(string filename);
//void primaryKeySearchManager(const HashList& hash);
void secondaryKeySearchManager(const BinarySearchTree<BSTData>& bst);
void vDisplay(BSTData item);
void hDisplay(BSTData& item);
void displayManager(const HashList<Data>& hash, const BinarySearchTree<BSTData>& bst, int option);
//void insertManager(HashList& hash);
void deleteManager(const HashList<Data>& hash, BinarySearchTree<BSTData>& bst, int option);
//void writeToFile(const HashList& hash);
//void displayHashStatistics(const HashList& hash);
void displayIndentedTree(const BinarySearchTree<BSTData>& bst);
void iDisplay(BSTData& item, int level);
void displayTeamMembers();

int main()
{
    BinarySearchTree<BSTData> bst;
    HashList<Data> hash(hashSize("Input.txt"));
    inputData("Input.txt",hash, bst);

    int choice;
    void printInfo();

    menuDisplay();
    cin >> choice;

    while (choice != 0)
    {
        switch (choice)
        {
        case 1: //hash = inputData(bst);
            break;
        case 2: //insertManager(hash);
            break;
        case 3:// primaryKeySearchManager(hash);
            break;
        case 4: secondaryKeySearchManager(bst);
            break;
        case 5:
        case 6: displayManager(hash, bst, choice);
            break;
        case 7:
        case 8: deleteManager(hash, bst, choice);
            break;
        case 9: //writeToFile(hash);
            break;
        case 10: //displayHashStatistics(hash);
            break;
        case 11: displayIndentedTree(bst);
            break;
        case 12: displayTeamMembers();
            break;
        case 99: menuDisplay();
            break;
        default: cout << "=== End of Program ===";
            exit(101);
        }

        menuDisplay();
        cin >> choice;
    }
    return 0;
}

// printInfo() displays welcome messange
// and information of this program
void printInfo()
{
    cout << "     Welcome to De Anza's Summer 2020 Listing Database\n"
        << "A data structure team project designed and developed by Team 5\n"
        << "     BST Algorithms & File I/O - Ashley Emily Irawan\n"
        << "          Hash List Algorithms - David Belshaw\n"
        << "   Team Coordination & Screen Output - Lai Chi Choy (Lychee)\n\n";
}

// menuDisplay() displays menu options
void menuDisplay()
{
    cout << "---------------------------------\n"
        << "           M E N U\n"
        << "---------------------------------\n"
        << "1. Insert - Data File\n"
        << "2. Insert - Keyboard Input\n"
        << "3. Search - CRN\n"
        << "4. Search - Course Prefix\n"
        << "5. Display - CRN\n"
        << "6. Display - Course Prefix\n"
        << "7. Delete - CRN\n"
        << "8. Delete - Course Prefix\n"
        << "9. Output - Write to File (CRN order)\n"
        << "10. Display Hashlist Statistics\n"
        << "99. Help - Display Menu\n"
        << "0. Quit - End Program\n"
        << "---------------------------------\n\n"
        << "Please enter an option from menu (e.g. 3): ";
}

// inputData() reads data from text file,
// insert data into hash table and BST,
// and displays message of completion/ failure
void inputData(string fileName, HashList<Data>& hash, BinarySearchTree<BSTData>& bst)
{
    cout << "=== Input from Data File ===\n";

    ifstream inFile;
    // string fileName = "";
    // fileName = "CIS22C_Team5_Input_Randomized.txt";

   // cin.ignore();
    cout << "Enter name of input text file: ";
    cin >> fileName;
    cout << "Opening.. " << fileName << endl;
    inFile.open(fileName);

    if (!inFile)
    {
        //cin.ignore();
        cout << "Error reading from file.\n"
            << "Please re-enter name of input text file or Q to exit: ";
        getline(cin, fileName);

        if (fileName == "Q" || fileName == "q")
        {
            cout << "=== End of Program ===";
            exit(101);
        }
        inFile.open(fileName.c_str());
    }
   // cout << "Successful" << endl;
   // HashList hash = HashList(hashSize(fileName));
    // BinarySearchTree<BSTData> bst; --> moved to main
    string crn, prefix, course, section, title, instructor;

    cout << "Reading from " << fileName << " ...\n";
    while (inFile)
    {
        //cout << "reading file" << endl;
        getline(inFile, crn, ';');
      //  cout << crn << endl;
        getline(inFile, prefix, ';');
        //cout << prefix << endl;
        getline(inFile, course, ';');
        //cout << course << endl;
        getline(inFile, section, ';');
        //cout << section << endl;
        getline(inFile, title, ';');
        //cout << title << endl;
        getline(inFile, instructor, '\n');
        //cout << instructor << endl;

        Data input = Data(crn, prefix, course, section, title, instructor);
        //hash.insert(input);
        buildBST(bst, crn, prefix);
        //cout << "BST built" << endl;
        cout << input << endl;
    }

    inFile.close();
    cout << "Reading completed.\n";
}

// buildBST() builds BST node and insert it into bst
void buildBST(BinarySearchTree<BSTData>& bst, string crn, string course)
{
    // create a Data object and initialize it with data from file
   // cout << "inside build BST" << endl;
    BSTData Data;
    BSTData temp;
    Data.setCourse(course);

    Data.insertCRN(Data.getCRNlist(), crn);
    if(bst.search(Data, temp))
       bst.insertCRNList(Data);
    else
    bst.insert(Data);

}

// hashSize() counts the lines in the input file, multiply it
// by 2 and choose the next prime number as size of hash table

int hashSize(string filename)
{
    string temp;
    int lines = 0;
    ifstream inFile;
    inFile.open(filename.c_str());
    if (!inFile)
    {
        cout << "Error";
        return 1;
    }
    while (inFile)
    {
        getline(inFile, temp, '\n');
        lines++;
    }
    inFile.close();
    int hashsize = (lines-1) * 2;
    int flag = 0;
    int prime = 0;
    do
    {
        for (int i = 2; i <= lines; i++)
        {
            if (hashsize % i == 0)
            {
                hashsize++;
            }
            else
            {
                flag = 1;
            }
        }
    } while (flag == 0);
    prime = hashsize;
    //cout << prime << endl;
    return prime;
}

// secondarySearchManager() prompts user to enter a course prefix,
// calls search() in BST, displays result or message if not found
void secondaryKeySearchManager(const BinarySearchTree<BSTData>& bst)
{
    string targetCode;
    BSTData data;

    cout << "\n=== Search by Course Prefix ===\n";
    cin.get();

    // allow course prefix that beings with Q
    while (targetCode != "Q" || targetCode != "q")
    {
        cout << "\nEnter a course code (or Q to stop searching) : \n";

        getline(cin, targetCode, '\n');
        unsigned int i = 0;
        while (i < targetCode.length())
        {
            targetCode[i] = toupper(targetCode[i]);
            i++;
        }
        if (toupper(targetCode[0]) != 'Q')
        {
            BSTData target;
            target.setCourse(targetCode);
            if (bst.search(target, data))
                vDisplay(data);
            else
                cout << "Course \"" << targetCode << "\" was not found in this list." << endl;
        }
    }
    cout << "___End of Search by Course Prefix___\n";
}

void vDisplay(BSTData item)
{
    cout << "            Course: " << item.getCourse() << endl;
    cout << "               CRN: " << item.getCRN(0) << endl;
    for (int i = 1 ; item.getCRN(i)!= "0"; i++)
    {
        cout << "                    " << item.getCRN(i) << endl;
    }

}

void hDisplay(BSTData& item)
{
    cout << item.getCourse() << endl;
}
/*
// primaryKeySearchManager() prompts user to enter a CRN,
// calls search() in hash table, displays result or message if
// not found
void primaryKeySearchManager(const HashList& hash)
{
    Data found; // will store a copy of the item found in the hash table
    string crn;   // name to insert
    cout << "=== Search by CRN ===\n"
        << "Enter course CRN or Q to quit: ";
    cin >> crn;
    while (crn != "Q" || crn != "q")
    {
        // create key, a data object, to hold the name to search for
        if (hash.searchKey(crn, found) == -1)
            cout << "CRN " << crn << " cannot be found.\n";
        else
            cout << found << endl;

        cout << "Enter course CRN: ";
        cin >> crn;
    }

}*/


// displayManager() displays all data sorted by CRN or course prefix
void displayManager(const HashList<Data>& hash, const BinarySearchTree<BSTData>& bst, int option)
{
    if (option == 5)
    {
        cout << "=== Display All Data Sorted by CRN ===\n";
        // display data sorted by CRN
        cout << "___End of Data Display by CRN___\n";
    }
    else
    {
        cout << "=== Display All Data Sorted by Course Prefix ===\n";
        bst.inOrder(hDisplay);
        cout << "___End of Data Display by Course Prefix___\n";
    }
}

// insertManager() prompts user to provide data to insert
// into hash table and displays message of completion/failure
void insertManager(HashList<Data>& hash)
{/*
    string crn, prefix, course, section, title, instructor;

    cout << "=== Insert New Data ===\n"
        << "Please enter info for new class:\n"
        << "Class CRN (e.g. 24689): ";
    cin >> crn;

    while (hash.searchKey(crn) != null)
    {
        cout << "\nDuplicate key: " << crn << " - rejected! \n"
            << "Please enter a new Class CRN (e.g. 24689): ";
        cin >> crn;
    }

    cout << "\nClass prefix (e.g. CIS): ";
    cin >> prefix;
    cout << "\nClass code (e.g. 22C): ";
    cin >> course;
    cout << "\nClass section (e.g. 03Y): ";
    cin >> section;
    cin.ignore();
    cout << "\nClass title (e.g. Data Abstraction and Structures): ";
    getline(cin, title);
    cin.ignore();
    cout << "\nName of instructor (e.g. Delia Garbacea): ";
    getline(cin, instructor);

    Data newData = Data(crn, prefix, course, section, title, instructor);
    hash.insert(newData);
    cout << "Data insert completed.\n"
        << "___End of Data Insert by Keyboard Input___\n";
        */
}

// deleteManager() prompts user to provide CRN or course
// prefix to delete found data and displays completion or
// failure if not found
void deleteManager(const HashList<Data>& hash, BinarySearchTree<BSTData>& bst, int option)
{

    if (option == 7)
    {
        cout << "=== Delete Data by CRN ===\n";
        // delete data by CRN

        string crn;
        cout << "Enter CRN or Q to quit: ";
        cin >> crn;
        //while (crn != "Q" || crn != "q")
        //{
            //Data itemOut, found, key(name, 0);
            /*if (hash.remove(itemOut, key))
                cout << endl << itemOut.getCrn() << " "
                << itemOut.getPrefix()
                << itemOut.getCourse()
                << " - deleted!" << endl;

            cout << "Load Factor: " << hash.getLoadFactor() << endl;

            cout << "Enter name or Q to quit: ";
            cin >> name;
        }

        cout << "___End of Data Display by Course CRN___\n";*/
    }
    else
    {
        cout << "=== Delete Data by Course Prefix ===\n";
        string course;
        cout << "Enter course prefix or Q to quit: ";
        cin >> course;
        while (course != "Q" || course != "q")
        {

            BSTData item;
            item.setCourse(course);
            bool success = bst.removeNode(bst, item);
            if (success)
            {
                cout << endl << item.getCourse() << " "
                << " - deleted!" << endl;
            }
            else
            {
                cout << endl << "Unable to delete" << endl;
            }
            cout << "Enter course prefix or Q to quit: ";
            cin >> course;
            if (course == "Q" || course == "q")
                break;
        }
        cout << "___End of Data Display by Course Prefix___\n";
    }
}

// writeToFile() writes data in hash table sequence to a text file
// and displays message of completion/ failure
/*void writeToFile(const HashList& hash)
{
    cout << "=== Write Data to File ===\n";

    cout << "___End of Writing to File___\n";
}*/

// displayHashStatistics() displays load factor, number of
// collisions (total), and longest collision path
//void displayHashStatistics(const HashList& hash)
/*
    cout << "=== Display Hash Statistics ===\n";
    // display hash stats
    hash.getLoadFactor();
    // get number of collisions (total)
    // get longest collision path
    cout << "___End of Hash Statistics Display___\n";
    */


// displayIndentedTree() displays BST as an indented tree
// with level number and BST key
void displayIndentedTree(const BinarySearchTree<BSTData>& bst)
{
    cout << "=== Display BST Indented Tree ===\n";
    bst.printTree(iDisplay);
    cout << "___End of BST Indented Tree Display___\n";
}


// iDisplay() displays one item per line, including the level number
// of binary tree
void iDisplay(BSTData& item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item.getCourse() << endl;
}

// displayTeamMembers() displays names of team members
void displayTeamMembers()
{
    cout << "Team 5 Members:\n"
        << "Ashley Emily Iranwan,\n"
        << "David Belshaw,\n"
        << "Lai Chi Choy (Lychee)\n";
}

/*
#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <fstream>

#include "BinarySearchTree.h"
#include "BinaryTree.h"
#include "BinaryNode.h"
#include "BSTData.h"
#include "HashList.h"
#include "Data.h"
using namespace std;

HashList inputData(string);

int main()
{
    HashList hash = inputData("input.txt");
    return 0;
}

void buildBST(BinarySearchTree<BSTData>& bst, string crn, string course)
{
        // create a College object and initialize it with data from file
        BSTData Data(crn, course);
        bst.insert(Data);
}

int hashsize(string filename)
{
    string temp;
    int lines = 0;
    ifstream inFile;
    inFile.open(filename.c_str());
    if (!inFile)
    {
        cout << "Error";
        return 1;
    }
    while (inFile.peek() != std::ifstream::traits_type::eof())
    {
        getline(cin, temp, '\n');
        lines++;
    }
    inFile.close();
    int hashsize = lines * 2;
    int flag = 0;
    int prime = 0;
    do
    {
        for (int i = 2; i <= lines; i++)
        {
            if (hashsize % i == 0)
            {
                hashsize++;
            }
            else
            {
                flag = 1;
            }
        }
    } while (flag == 0);
    prime = hashsize;
    return prime;


}
//Inputs Data into Hash List from text file
HashList inputData(string filename)
{
    ifstream inFile;
    inFile.open(filename.c_str());
    if (!inFile)
    {
        cout << "Error";
        return 1;
    }
    HashList hash = HashList(hashsize(filename));
    BinarySearchTree<BSTData> bst;
    string crn, prefix, course, section, title, instructor;
    while (inFile.peek() != std::ifstream::traits_type::eof())
    {
        getline(inFile, crn, ';');
        getline(inFile, prefix, ';');
        getline(inFile, course, ';');
        getline(inFile, section, ';');
        getline(inFile, title, ';');
        getline(inFile, instructor);

        Data input = Data(crn, prefix, course, section, title, instructor);
        hash.insert(input);
        buildBST(bst, crn, course);
        //cout << input << endl;
    }
    inFile.close();
    return hash;
}

string searchManager(const BinarySearchTree<BSTData>& bst)
{
    string targetCode;
    BSTData data;

    cout << "\n Search\n";
    cout << "=======\n";
    cin.get();
    while (toupper(targetCode[0]) != 'Q')
    {
        cout << "\nEnter a course code (or Q to stop searching) : \n";

        getline(cin, targetCode, '\n');
        unsigned int i = 0;
        while (i < targetCode.length())
        {
            targetCode[i] = toupper(targetCode[i]);
            i++;
        }
        if (toupper(targetCode[0]) != 'Q')
        {
            BSTData target;
            target.setCourse(targetCode);
            if (bst.search(target, data))
                vDisplay(data);
            else
                cout << "Course \"" << targetCode << "\" was not found in this list." << endl;
        }
    }
    cout << "___________________END SEARCH SECTION _____\n";
}

void vDisplay(BSTData item)
{
    cout << "               CRN: " << item.getCrn() << endl;
    cout << "            Course: " << item.getCourse() << endl;
}
*/
