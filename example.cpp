#include <iostream>
#include "py_string.h"


int main()
{
    //open file
    PyStr::PyInFile csvfile("afile.csv");

    //check if file is actually opened
    if(!csvfile.isopen())
    {
        std::cout << "Error: Unknown file.\n";
        return 1;
    }
    else
    {
        std::cout << "Opened file: " << csvfile.getname() << std::endl;
    }

    //print out a header for the table
    PyStr::PyString header;

    std::cout <<    header.set("Name").    tabpad(' ', 11) <<
                    header.set("Country"). tabpad(' ', 11) <<
                    header.set("Age").     tabpad(' ', 11) << std::endl <<
                    header.clear().        tabpad('-', 33) << std::endl;


    //read all lines of the file and iterate through them
    PyStr::PyStringList lines, words;
    unsigned int age= 0, people= 0;

    /** The library itself actually does not require C++11 for loops **/

    for(const auto& line : csvfile.readlines(lines))
    {
        //ignore empty lines
        if( !line.is_whitespace() )
        {
            //make list of columns and remove last one (is empty)
            line.split(words, ";").pop_back();

            //check number of columns
            if(words.size() != 3)
            {
                std::cout << "Error: Corrupted table. Expected 3 columns.\n";
                return 1;
            }

            //iterate through the columns and print them out as a table row
            for(auto&& word : words)
            {
                std::cout << word.sfstrip().tabpad(' ', 11);
            }
            std::cout << std::endl;

            //increment the counter for valid data lines
            people++;

            //try to convert third column (age) to an unsigned integer
            // (a negative age is not allowed)
            try
            {
                age+= words[2].to_uint();
            }
            catch(const PyStr::ValueError& e)
            {
                std::cout << "Error: Can not convert age to a uint value.\n";
                std::cout << "Caused by: " << e.get_value() << std::endl;
                return 1;
            }
        }
    }

    //calculate average age
    std::cout << std::endl;
    std::cout << "Read " << people << " people from the file.\n";
    std::cout << "Their average age is: " << (float)age/people << std::endl;

    //close file
    csvfile.close();

    return 0;
}
