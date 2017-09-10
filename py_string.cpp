//  Project:        PyString
//  Name:           py_string.cpp

#include "py_string.h"
#include <cmath>

namespace PyStr
{
/** Definition of the static PyString class constants **/

constexpr char PyString::alphabeth[];
constexpr char PyString::numbers[];
constexpr char PyString::whitespace[];



/** Implementations **/

bool PyString::is_number() const
{
    bool comma= false;
    for(std::string::const_iterator pos= content.begin(); pos!= content.end(); pos++)
    {
        if((*pos< 48)|| (*pos> 57))
        {
            if(*pos== '.')
            {
                if(comma)
                {
                    return false;
                }
                comma= true;
            }else
            {
                return false;
            }
        }
    }

    return true;
}

bool PyString::is_integer() const
{
    for(std::string::const_iterator pos= content.begin(); pos!= content.end(); pos++)
    {
        if((*pos< '0')|| (*pos> '9'))
        {
            return false;
        }
    }

    return true;
}

bool PyString::is_alpha() const
{
    for(std::string::const_iterator pos= content.begin(); pos!= content.end(); pos++)
    {
        if((*pos< 'A')|| (*pos> 'Z'))
        {
            if((*pos< 'a')|| (*pos> 'z'))
            {
                return false;
            }
        }
    }

    return true;
}

bool PyString::is_whitespace() const
{
    for(std::string::const_iterator pos= content.begin(); pos!= content.end(); pos++)
    {
        bool iswhite= false;
        for(const char *wpos= PyString::whitespace; (*wpos)&& (!iswhite); wpos++)
        {
            iswhite= (*wpos== *pos);
        }

        if(!iswhite)
        {
            return false;
        }
    }

    return true;
}

bool PyString::is(const PyString& comp) const
{
    return !this->content.compare(comp.content);
}

bool PyString::contains(const PyString& comp) const
{
    return (this->content.find(comp.content, 0)!= std::string::npos);
}

bool PyString::contains(const char comp) const
{
    for(std::string::const_iterator pos= this->content.begin(); pos!= this->content.end(); pos++)
    {
        if(*pos== comp)
        {
            return true;
        }
    }

    return false;
}

bool PyString::mult_contains(const std::string& comp) const
{
    for(std::string::const_iterator pos= this->content.begin(); pos!= this->content.end(); pos++)
    {
        for(std::string::const_iterator cpos= comp.begin(); cpos!= comp.end(); cpos++)
        {
            if(*cpos== *pos)
            {
                return true;
            }
        }
    }

    return false;
}


PyString PyString::reverse() const
{
    std::string revstr;

    for(std::string::const_reverse_iterator pos= content.rbegin(); pos!= content.rend(); pos++)
    {
        revstr.push_back(*pos);
    }

    return revstr;
}


PyString PyString::replace(const std::string& in, const std::string& out, int nbr ) const
{
    std::string nstr;

    int pos= 0;
    size_t fndat= content.find(in, pos);

    while((fndat!= std::string::npos)&& (nbr))
    {
        nstr.append( content.substr(pos, fndat- pos)+ out );
        pos= fndat+ in.length();
        fndat= content.find(in, pos);

        nbr--;
    }

    nstr.append( content.substr(pos, content.length()-1) );

    return nstr;
}


PyString PyString::lower() const
{
    std::string nstr;

    for(std::string::const_iterator pos= content.begin(); pos!= content.end(); pos++)
    {
        if((*pos>= 'A')&& (*pos<= 'Z'))
        {
            nstr.push_back( (*pos)+ 32 );
        }
        else
        {
            nstr.push_back( *pos );
        }
    }

    return nstr;
}


PyString PyString::upper() const
{
    std::string nstr;

    for(std::string::const_iterator pos= content.begin(); pos!= content.end(); pos++)
    {
        if((*pos>= 'a')&& (*pos<= 'z'))
        {
            nstr.push_back( (*pos)- 32 );
        }
        else
        {
            nstr.push_back( *pos );
        }
    }

    return nstr;
}


PyString PyString::swap_case() const
{
    std::string nstr;

    for(std::string::const_iterator pos= content.begin(); pos!= content.end(); pos++)
    {
        if((*pos>= 'a')&& (*pos<= 'z'))
        {
            nstr.push_back( (*pos)- 32 );
        }
        else if((*pos>= 'A')&& (*pos<= 'Z'))
        {
            nstr.push_back( (*pos)+ 32 );
        }
        else
        {
            nstr.push_back( *pos );
        }
    }

    return nstr;
}


PyString PyString::strip(const std::string& delimiters) const
{
    int start= 0, backstart= 0;
    bool run;

    std::string::const_iterator pos;
    for(pos= this->content.begin(); pos!= this->content.end(); pos++)
    {
        run= true;
        for(std::string::const_iterator dpos= delimiters.begin(); run&& (dpos!= delimiters.end()); dpos++)
        {
            if(*dpos== *pos)
            {
                run= false;
            }
        }

        if(run)
        {
            break;
        }
    }

    start= pos- this->content.begin();

    for(std::string::const_reverse_iterator pos= this->content.rbegin(); pos!= this->content.rend(); pos++)
    {
        run= true;
        for(std::string::const_iterator dpos= delimiters.begin(); run&& (dpos!= delimiters.end()); dpos++)
        {
            if(*dpos== *pos)
            {
                run= false;
            }
        }

        if(run)
        {
            backstart= pos- this->content.rbegin();
            break;
        }
    }

    return this->content.substr(start, this->content.length() -start -backstart);
}


int PyString::str_to_int(const std::string& text)
{
    unsigned int power= 0;
    int value= 0;
    for(std::string::const_reverse_iterator pos= text.rbegin(); pos!= text.rend(); pos++)
    {
        if((*pos< '0')|| (*pos> '9'))
        {
            if((*pos== '-')&& (pos+1== text.rend()))
            {
                value*= -1;
            }
            else
            {
                throw ValueError("Error: Can not convert given string data to integer value.\n", text);
            }
        }
        else
        {
            value+= (*pos- '0')* pow(10, power);

            power++;
        }
    }

    return value;
}


unsigned int PyString::str_to_uint(const std::string& text)
{
    unsigned int power= 0, value= 0;

    for(std::string::const_reverse_iterator pos= text.rbegin(); pos!= text.rend(); pos++)
    {
        if((*pos< '0')|| (*pos> '9'))
        {
            throw ValueError("Error: Can not convert given string data to unsigned integer value.\n", text);
        }

        value+= (*pos- '0')* pow(10, power);

        power++;
    }

    return value;
}


double PyString::str_to_dbl(const std::string& text)
{
    double value= 0;
    int    ivalue= 0;
    std::string inttext;

    std::string::const_iterator pos;
    for(pos= text.begin(); pos!= text.end(); pos++)
    {
        if(*pos== '.')
        {
            break;
        }

        inttext.push_back(*pos);
    }

    try
    {
        ivalue= str_to_int(inttext);
    }
    catch(ValueError& e)
    {
        e.setdata("Error: Can not convert given string data to integer value for to-floating-point-conversion.\n");
        throw e;
    }

    if(pos!= text.end())
    {
        for(std::string::const_reverse_iterator rpos= text.rbegin(); rpos!= text.rend()- (pos- text.begin())- 1; rpos++)
        {
            std::cout << *rpos << std::endl;
            if((*rpos< '0')|| (*rpos> '9'))
            {
                throw ValueError("Error: Can not convert given string data to floating point value.\n", text);
            }


            value= (value + (*rpos- '0'))/ 10;
        }
    }


    return std::copysign(value, ivalue)+ (double)ivalue;
}


bool PyString::str_to_bool(const std::string& text)
{
    if(!text.compare("true"))
    {
        return true;
    }
    else if(!text.compare("false"))
    {
        return false;
    }
    else
    {
        try
        {
            return PyString::str_to_int(text);
        }
        catch(ValueError& e)
        {
            e.setdata("Error: Can not convert given string data to integer value for to-bool-conversion.\n");
            throw e;
        }
    }
}

PyStringList& PyString::split(PyStringList& strlist, const std::string& delimiter, int nbr) const
{
    unsigned int pos= 0;
    size_t fndat= content.find(delimiter, pos);

    strlist.resize(0);

    while((nbr)&& (fndat!= std::string::npos))
    {
        strlist.push_back( content.substr( pos, fndat-pos ) );

        pos= fndat+ delimiter.length();

        fndat= content.find(delimiter, pos);

        nbr--;
    }

    strlist.push_back( content.substr( pos, content.length()- pos ) );

    return strlist;
}

PyStringList& PyString::mult_split(PyStringList& strlist, const std::string& delimiters, int nbr) const
{
    std::string::const_iterator pos= content.begin();
    bool ischar, lastischar= false;

    strlist.resize(1);

    while((nbr)&& (pos!= content.end()))
    {
        //std::cout << strlist.back() << std::endl;
        ischar= true;
        for(std::string::const_iterator dpos= delimiters.begin(); (ischar)&& (dpos!= delimiters.end()); dpos++)
        {
            ischar= (*pos!= *dpos);
        }

        if( ischar|| (!lastischar) )
        {
           strlist.back().content.push_back(*pos);
        }
        else
        {
            strlist.push_back( PyString() );
        }

        lastischar= ischar;

        pos++;
        nbr--;
    }

    return strlist;
}

PyString PyString::join(const PyStringList& strs, int nbr) const
{
    std::string nstr= this->content;

    for(PyStringList::const_iterator pos= strs.begin(); (nbr)&& ( pos!= strs.end() ); pos++)
    {
        nstr+= pos->content;

        nbr--;
    }

    return nstr;
}

PyString& PyString::sfjoin(const PyStringList& strs, int nbr)
{
    for(PyStringList::const_iterator pos= strs.begin(); (nbr)&& ( pos!= strs.end() ); pos++)
    {
        this->content+= pos->content;

        nbr--;
    }

    return *this;
}

} //namespace pystring
