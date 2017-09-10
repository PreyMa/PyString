# PyString
A small wrapper class to add python inspired string functionalities in C++

This 'library' is made out of a single header file and an additional
cpp file which contains some of the longer method implementaions.
The header file contains a wrapper class for the cpp standard library
string type to add some of the functionalities I tend to use quite
frequently and an 'ValueError' exception that may be thrown by the
string-to-number conversion methods. It inherits directly from
std::exception and holds a constant 'what'-string, a method specific
message and the string data that caused the exception.

Performance might not be the best, however the main goal here was only
to provide a comfortable python like environment. Just for convenience
some self modifying versions of the string methods are available.

The actual std::string is a public class member, so that not all of
the standard functionalities like 'substr()', had to be reimplemented or
wrapped. Only 'compare()' and 'find()' were wrapped to return a more
intuitive bool value and reduce code.

Although I use this library myself, I can not guarantee that my
implementations always work correctly in all edge cases, or similarly
to their python equivalents.

Maybe I will add other things here later on, when I need to extend
my summary of frequenty functions.
