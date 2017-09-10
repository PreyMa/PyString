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
    PyString replace(const std::string& in, const std::string& out, int nbr= -1 ) const;    //replace portion of a string with a new one
    PyString strip(const std::string& delimiters= PyString::whitespace) const;              //remove characters from both ends of the string
    PyString reverse() const;                                                               //reverse string
    PyString join(const PyStringList& strs, int nbr= -1) const;                             //concatenate a list of strings


    PyString lower()     const; //make all characters lower case
    PyString upper()     const; //make all characters upper case
    PyString swap_case() const; //invert the case all of all characters


    PyStringList& split     (PyStringList& strlist, const std::string& delimiter, int nbr= -1) const;                           //split string into list of strings at delimiting string
    PyStringList& mult_split(PyStringList& strlist, const std::string& delimiters= PyString::whitespace, int nbr= -1) const;    //split string into list of strings at one of the delimiting characters



    //////////////////////////////////
    /** Self modifying string functions **/
    inline PyString& sfreplace(const std::string& in, const std::string& out, int nbr= -1 ) {*this= this->replace(in, out, nbr);   return *this;};
    inline PyString& sfstrip(const std::string& delimiters= PyString::whitespace)           {*this= this->strip(delimiters);       return *this;};
    inline PyString& sfreverse()                                                            {*this= this->reverse();               return *this;};
    inline PyString& sfjoin(const PyStringList& strs, int nbr= -1);


    inline PyString& sflower()     {*this= this->lower();     return *this;};
    inline PyString& sfupper()     {*this= this->upper();     return *this;};
    inline PyString& sfswap_case() {*this= this->swap_case(); return *this;};


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

    inline int             to_int()  const {return str_to_int  (this->content);};
    inline unsigned int    to_uint() const {return str_to_uint (this->content);};
    inline double          to_dbl()  const {return str_to_dbl  (this->content);};
    inline bool            to_bool() const {return str_to_bool (this->content);};


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
    inline PyString& operator = (const std::string& text)    {content= text; return *this;}
    inline PyString& operator +=(const std::string& text)    {content+= text; return *this;}
    inline PyString& operator +=(const PyString& text)   {content+= text.content; return *this;}
    inline PyString  operator + (const std::string& text)    {return content+= text;}
    inline PyString  operator + (const PyString& text)   {return content+= text.content;}

};

/** IO Stream operator overloads **/
inline std::ostream& operator <<(std::ostream& stream, const PyString& str) { return stream << str.content;};
inline std::istream& operator >>(std::ostream& stream, const PyString& str) { return stream >> str.content;};

} //namespace pystring
#endif // PY_STRING_H_INCLUDED
