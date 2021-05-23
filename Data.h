// Specification file for the Data class
// Written By: Ashley Irawan
// IDE: CodeBlocks

#ifndef DATA_H
#define DATA_H

#include<iostream>
#include<iomanip>
#include<string>

using std::string;
using std::ostream;

class Data
{
    private:
        string crn;
        string prefix;
        string course;
        string section;
        string title;
        string instructor;

    public:
        //constructors
        Data()
        {   crn = prefix = course = section = title = instructor = ""; }
        Data(string crn, string prefix, string course, string section, string title, string instructor)
        {   this->crn = crn;        this->prefix = prefix;
            this->course = course;  this->section = section;
            this->title = title;    this->instructor = instructor; }

        //setters
        void setCrn(string nCrn)                { crn = nCrn;}
        void setPrefix(string nPrefix)          { prefix = nPrefix;}
        void setCourse(string nCourse)          { course = nCourse;}
        void setSection(string nSection)        { section = nSection;}
        void setTitle(string nTitle)            { title = nTitle;}
        void setInstructor(string nInstructor)  { instructor = nInstructor;}

        //getters
        string getCrn()         const {return crn;}
        string getPrefix()      const {return prefix;}
        string getCourse()      const {return course;}
        string getSection()     const {return section;}
        string getTitle()       const {return title;}
        string getInstructor()  const {return instructor;}

        //overloaded operators
        friend ostream & operator << (ostream &out, const Data &c)
        {
            out << std::left;
            out << "" << std::setw(5) << c.crn << "|";
            out << "" << std::setw(4) << c.prefix << "|";
            out << "" << std::setw(4)<< c.course << "|";
            out << "" << std::setw(3)<< c.section << "|";
            out << "" << std::setw(30) << c.instructor << "|";
            out << "" << std::setw(65) << c.title;

            return out;
        }

};

#endif

