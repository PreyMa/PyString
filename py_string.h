//  Project:        PyString
//  Name:           py_string.h

//  Description:    Simple std::string wrapper library for
//                  C++ to provide Python like string functionalities
//  Files:          py_string.h, py_string.cpp;

//  Author:         Matthias Preymann HTBL-Hollabrunn
//  Date:           10th September 2017
//  License:        MIT License



#ifndef PY_STRING_H_INCLUDED
#define PY_STRING_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <fstream>

namespace PyStr
{

class ValueError : std::exception
{
    std::string data;
    std::string value;

public:
    ValueError(const std::string& datatext, const std::string& valuetext): data(datatext), value(valuetext){}

    virtual const char* what(){return "Value Error of PyString conversion.";}
    const std::string& get_data(){return data;}
    const std::string& get_value(){return value;}

    void setdata(const std::string& text){data= text;}
};



class PyString;
typedef std::vector<PyString> PyStringList;



class PyString
{
public:
    /** Data members **/
    std::string content;

    /** Constants **/
    static constexpr char alphabeth[]= "abcdefghijklmnopqrstuvwxyz";
    static constexpr char numbers[]= "0123456789";
    static constexpr char whitespace[]= " \t\n\f\r\v";

    /** Constructors **/
    PyString(const std::string& data): content(data){}          //from standard string
    PyString(const PyString& cpy):     content(cpy.content){}   //from pystring: copy constructor
    PyString(){}                                                //empty string


    /** Copy returning string functions **/
    PyString replace(const std::string& in, const std::string& out, int nbr= -1 ) const;            //replace portion of a string with a new one
    PyString strip(const std::string& delimiters= PyString::whitespace) const;                      //remove characters from both ends of the string
    PyString reverse() const;                                                                       //reverse string
    PyString join(const PyStringList& strs, int nbr= -1) const;                                     //concatenate a list of strings
    PyString tabpad(const char spacer, const unsigned int nbr, const std::string& term= "") const;  //pad string to desired length with spacer character


    inline PyString append(const char c)            const {return (this->content)+ c;}              //add character to copy
    inline PyString append(const std::string& text) const {return (this->content)+ text;}           //add string to copy
    inline PyString append(const PyString&    text) const {return (this->content)+ text.content;}   //add string to copy


    PyString lower()     const; //make all characters lower case
    PyString upper()     const; //make all characters upper case
    PyString swap_case() const; //invert the case all of all characters


    PyStringList& split     (PyStringList& strlist, const std::string& delimiter, int nbr= -1) const;                           //split string into list of strings at delimiting string
    PyStringList& mult_split(PyStringList& strlist, const std::string& delimiters= PyString::whitespace, int nbr= -1) const;    //split string into list of strings at one of the delimiting characters



    //////////////////////////////////
    /** Self modifying string functions **/
    inline PyString& sfreplace(const std::string& in, const std::string& out, int nbr= -1 )           {*this= this->replace(in, out, nbr);     return *this;};
    inline PyString& sfstrip(const std::string& delimiters= PyString::whitespace)                     {*this= this->strip(delimiters);         return *this;};
    inline PyString& sfreverse()                                                                      {*this= this->reverse();                 return *this;};
    inline PyString& sfjoin(const PyStringList& strs, int nbr= -1);
    inline PyString& sftabpad(const char spacer, const unsigned int nbr, const std::string& term= "") {*this= this->tabpad(spacer, nbr, term); return *this;};


    inline PyString& sfappend(const char c)            {(this->content)+= c;            return *this;}  //add character
    inline PyString& sfappend(const std::string& text) {(this->content)+= text;         return *this;}  //add string
    inline PyString& sfappend(const PyString&    text) {(this->content)+= text.content; return *this;}  //add string


    inline PyString& sflower()     {*this= this->lower();     return *this;};
    inline PyString& sfupper()     {*this= this->upper();     return *this;};
    inline PyString& sfswap_case() {*this= this->swap_case(); return *this;};


    inline PyString& clear()       {(this->content).erase(); return *this;}


    /** Query functions **/
    bool is_number() const;                             //check if string is a valid number, may contain '.' once
    bool is_integer() const;                            //check if string is a valid integer, '.' is not allowed
    bool is_alpha() const;                              //check if string is only text
    bool is_whitespace() const;                         //check if string is only made out of whitespace characters
    bool is(const PyString& comp) const;                //compare two strings
    bool contains(const PyString& comp) const;          //check if string contains sub-string
    bool contains(const char comp) const;               //check if string contains character
    bool mult_contains(const std::string& comp) const;  //check if string contains one of the characters

    /** Conversion functions **/
    static int              str_to_int  (const std::string& text);
    static unsigned int     str_to_uint (const std::string& text);
    static double           str_to_dbl  (const std::string& text);
    static bool             str_to_bool (const std::string& text);

    static std::string      int_to_str  (int          value );
    static std::string      uint_to_str (unsigned int value );
    static std::string      dbl_to_str  (double       value, int accuracy= 8 );
    static std::string      bool_to_str (bool         value );

    inline int             to_int()  const {return str_to_int  (this->content);};
    inline unsigned int    to_uint() const {return str_to_uint (this->content);};
    inline double          to_dbl()  const {return str_to_dbl  (this->content);};
    inline bool            to_bool() const {return str_to_bool (this->content);};

    inline PyString& set(const std::string& value){(this->content)= value; return *this;};
    inline PyString& set(const int          value){(this->content)= PyString::int_to_str  ( value ); return *this;};
    inline PyString& set(const unsigned int value){(this->content)= PyString::uint_to_str ( value ); return *this;};
    inline PyString& set(const double       value){(this->content)= PyString::dbl_to_str  ( value ); return *this;};
    inline PyString& set(const bool         value){(this->content)= PyString::bool_to_str ( value ); return *this;};

    /** Character access operator overloads **/

    char& operator [](int position)
    {
        if(position< 0)
        {
            position= content.length()+ position;

            if(position< 0)
            {
                position= 0;
            }
        }

        return content.at(position);
    }

    const char& operator [](int position) const
    {

        if(position< 0)
        {
            position= content.length()+ position;

            if(position< 0)
            {
                position= 0;
            }
        }


        return content.at(position);
    }

    /** Concatenation operator overloads **/
    inline PyString& operator = (const std::string& text)   {content= text; return *this;}
    inline PyString& operator +=(const std::string& text)   {content+= text; return *this;}
    inline PyString& operator +=(const PyString& text)      {content+= text.content; return *this;}
    inline PyString  operator + (const std::string& text)   {return content+ text;}
    inline PyString  operator + (const PyString& text)      {return content+ text.content;}

};

/** IO Stream operator overloads **/
inline std::ostream& operator <<(std::ostream& stream, const PyString& str) { return stream << str.content;};
inline std::istream& operator >>(std::ostream& stream, const PyString& str) { return stream >> str.content;};


class PyInFile
{
    /** Data members **/
private:
    PyString pathname;
public:

    std::ifstream stream;


    /** Constructors **/
    PyInFile(): stream(std::ifstream()){};
    PyInFile(const std::string& path)                               {this->open(path); };
    PyInFile(const std::string& path, std::ios_base::openmode mode) {this->open(path, mode); };


    /** Methods **/
    inline PyInFile& open(const std::string& path, std::ios_base::openmode mode= std::ios_base::in) {pathname= path; stream.open(path, mode); return *this;};
    inline void      close()                                                                        {stream.close(); pathname.clear();};

    unsigned int length();  //get length of file in bytes

    PyString&       readline(PyString& str, const std::string& delimiters= "\n", int length= -1);                                                                           //read a single line
    inline PyString readline(               const std::string& delimiters= "\n", int length= -1) { PyString str; this->readline(str, delimiters, length); return str; };

    PyString&     readfile(PyString& str, int length= -1);      //read whole file content into one string
    PyStringList& readlines(PyStringList& strs, int nbr= -1);   //read all lines of the file into list of strings


    /** Query functions **/
    inline bool     isopen()  const {return stream.is_open();}
    inline bool     iseof()   const {return stream.eof();}
    const PyString& getname() const {return pathname;}

};

} //namespace pystring
#endif // PY_STRING_H_INCLUDED
