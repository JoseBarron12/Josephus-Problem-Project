//***************************************************************************
//
// Jose Barron
// Z02013735
// Fall 2023 CSCI 340 - PE1 Data Struct Algorithm Analysis
// Assignment 04: This program is intended to solve the Josephus Problem
// and simulate it using the given SPQ class and function declarations
// (print_underlined_string and print_list).
// Due Date: 9/25/23
// I certify that this is my own work and where appropriate an extension
// of the starter code provided for the assignment.
//
//***************************************************************************

#include "josephus.h"

#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <getopt.h>


// Simple function that underlines a given string using its length as
// a the size of the underline
void print_underlined_string(const std::string & message)
{
    std::cout << std::string(message.length(), '-');
}


// A function that prints a given list with given eliminations and desired
// number of columns in the desired format
void print_list(const std::list<std::string> &collection, const unsigned &eliminations, int num_cols)
{
    
    //No eliminations means that the initial list is being printed
    if (eliminations == 0) 
    {
        std::string msg1 = "Initial Group of People";
        std::cout << '\n' << msg1 << '\n';
        print_underlined_string(msg1);
        std::cout << '\n';
        int cols = 0;
        
        // This for loop uses an iterator to traverse the list since a list
        // is a container where one object points to another. [DOESNT allow
        // random access]
        for (auto it = std::begin(collection); it != std::end(collection); ++it) 
        {  
            // cols keeps track of the number of columns created
            ++cols; 
            // next is the next iterator
            auto next = it;
            ++next; 
            
            // If cols reaches the desired columns or the next iterator (next)
            // is a position outside the list then the the last person is
            // displayed and a newline is created to create a new row.
            // The count is reset to zero to ensure that for the next row
            // there is the desired amount of columns.
            if(cols == num_cols|| next == std::end(collection))
            {
                cols = 0;
                std::cout << *it << '\n'; 
            }
            // Otherwise the person is displayed with the right format
            else
            {
                std::cout << *it << ", ";
            }      
        }
    }
    // Exact same setup as for a case with no eliminations. The only
    // difference is the msg string
    else 
    {
        std::string msg = "After eliminating " + std::to_string(eliminations) + " people";
        std::cout << '\n' << msg << '\n';
        print_underlined_string(msg);
        std::cout << '\n';
        int cols = 0;
        for (auto it = std::begin(collection); it != std::end(collection); ++it)
        {  
            ++cols;
            auto next = it;
            ++next;
            if(cols == num_cols || next == std::end(collection))
            {
                cols = 0;
                std::cout << *it << '\n'; 
            }
            else
            {
                std::cout << *it << ", ";
            }      
        }  

    }
}


/**
* Print a 'Usage' message and exit(1).
*
* @param a0 The name of the command to include in the usage message.
*****************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-n number of people] [-m modulus] [-p print frequency] [-c print columns]" << std::endl;
    exit(1);
}


/**
* Create a std::list of prople with generated ID/names and reduce the
* list as per the Josephus problem algorithm.
*****************************************************************************/
int main(int argc, char **argv)
{
    unsigned num_people = 41;       // The number of people to start with
    unsigned modulus = 3;           // The count used to determine the elimination
    unsigned print_frequency = 13;  // How often to print the state of the system
    unsigned num_cols = 12;         // Number of colums to print per line

    int opt;
    while ((opt = getopt(argc, argv, "n:m:p:c:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            std::istringstream(optarg) >> num_people;
            break;
        case 'm':
            std::istringstream(optarg) >> modulus;
            break;
        case 'p':
            std::istringstream(optarg) >> print_frequency;
            break;
        case 'c':
            std::istringstream(optarg) >> num_cols;
            break;
        default:
            usage(argv[0]);
        }
    }

    if (optind < argc)
        usage(argv[0]); // If we get here, there was extra junk on command line

    // LIST is a list of strings that are generated from the SEQ class
    // using the function generate_n a STL algorithm. To simulate a group
    // of people
    std::list<std::string>LIST;
    std::generate_n(std::back_inserter(LIST),num_people,SEQ(num_people));
    
    // elim is used to keep track of the number of eliminated people and
    // count is used to keep track of eliminated people for the desired
    // print frequency
    unsigned elim = 0;
    unsigned count = 0;
    print_list(LIST,elim,num_cols); // Prints generated list
    std::list<std::string>::iterator it = LIST.begin(); // An iterator to the 
                                                        // first element of 
                                                        // the list
    
    // This while loop ensures that the list is left with one element
    // or until one person remains
    while (LIST.size() != 1)
    {
    
    // This for loops unsures that the list is traversed using the counting
    // distance and ensures that the iterator is giving a reference to an
    // a position inside the list. If it isnt then the iterator is made to
    // reference the first element. This is done until the next element is
    // is found to be eliminated
    for (unsigned i = 1; i != modulus; ++i)
    {
        ++it;
        if (it == LIST.end())
        {
            it = LIST.begin();
        }
    }
    
    // The next iterator is the next iterator in the list and is used to 
    // ensure that the iterator keep traversing the list in increments.
    // Since if the next iterator references outside the list then
    // traversing the list in increments wouldnt be possible
    auto next = it;
    ++next;
    if (next == LIST.end())
    {
        next = LIST.begin();
    }
    
    // This ensures that the element is erased and ensures that the
    // resulting iterator references an element inside the list
    it = LIST.erase(it); 
    if (it == LIST.end())
    {
        it = LIST.begin();
    }
    
    // After every elimination, elim and count are incremented. Once count
    // reaches the desired print frequency then the list is printed with
    // elim used for number of elimination as one of the parameters for
    // print list. Count is reset to zero once it reaches the desired print
    // frequency to ensure that the list is being printed at the desired
    // frequency. Elim is not reset since it is used to display the total
    // number of current eliminations
    ++elim;
    ++count;
    if (count == print_frequency)
    {
        count = 0;
        print_list(LIST, elim, num_cols);
    }
    }
    
    // Once the list is left with one element, then the while loop
    // ends and the last element is printed.
    std::cout << "\nElimination Completed";
    print_list(LIST, elim, num_cols);

    return 0;
}
