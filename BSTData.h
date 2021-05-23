#pragma once
// Specification file for the Data class
// Written By: Ashley
// IDE: Visual Studio

#ifndef BSTDATA_H
#define BSTDATA_H

#include<iostream>
#include<iomanip>
#include<string>

using std::string;
using std::ostream;

class BSTData
{
private:
    string course;
    string* crn = new string[30];

public:
    //constructors
    BSTData()
    {
        course = "";
        for (int i = 0; i < 30; i++)
        {
            crn[i] = "0";
        }
    }
    int GetListCount() const
    {
        int count = 0;
        for (int i = 0; crn[i] != "0"; i++)
            count++;
        return count;
    }

   /* BSTData(string course, string CRN)
    {
        //std::cout << "inside ov constructor" << std::endl;
        this->course = course;
        string crn[25] = {"0"};
        insertCRN(CRN);
    }*/
    string* getCRNlist()
    {
        return this->crn;
    }
    void insertCRN(string* crn, string target)
    {
       if (GetListCount() == 0)
       {
           *crn = target;
       }


        else{
            int position = 0;
            for (int i = 0; crn[i] != "0"; i++)
            {
                if (crn[i] > target)
                {
                    position = i;
                    for (int x = GetListCount()+1; x > position; x--)
                    {
                        crn[x] = crn[x-1];
                    }
                    crn[position] = target;
                    break;
                }
                else if (crn[i] < target && crn[i+1] == "0")
                {
                    crn[i+1] = target;
                    break;
                }
            }
        }
    }

    //setters
    //void setCrn(string nCrn) { crn = nCrn; }
    void setCourse(string nCourse) { course = nCourse; }

    //getters
   // string getCrn()         const { return crn; }
    string getCourse()      const { return course; }
    string getCRN(int i) const
    {
        return crn[i];
    }

    //overloaded operators
    friend ostream& operator << (ostream& out, const BSTData& c)
    {
        out << std::left;
        out << "" << std::setw(5) << c.crn << "|";
        out << "" << std::setw(4) << c.course << "|";
        return out;
    }

    bool operator < (const BSTData& right);
    bool operator > (const BSTData& right);
    bool operator == (const BSTData& right);
    bool operator != (const BSTData& right);
};
 bool BSTData::operator < (const BSTData& right)
    {
        bool status;
        if (course < right.course)
            status = true;
        else
            status = false;
        return status;
    }

    bool BSTData::operator > (const BSTData& right)
    {
        bool status;
        if (course > right.course)
            status = true;
        else
            status = false;
        return status;
    }

    bool BSTData::operator == (const BSTData& right)
    {
        bool status;
        if (course == right.course)
            status = true;
        else
            status = false;
        return status;
    }

    bool BSTData::operator != (const BSTData& right)
    {
        bool status;
        if (course != right.course)
            status = true;
        else
            status = false;
        return status;
    }


#endif


