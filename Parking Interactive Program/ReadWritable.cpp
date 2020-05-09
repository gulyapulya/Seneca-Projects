/* Citation and Sources...
Final Project Milestone 3
Module: ReadWritable
Filename: ReadWritable.cpp
Version 1.0
Author Baimukhambetova Gulnur
Revision History
-----------------------------------------------------------
Date Reason
2020/03/25 Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include "ReadWritable.h"

using namespace std;

namespace sdds
{
    ReadWritable::ReadWritable()
    {
        commaSep = 0;
    }

    bool ReadWritable::isCsv() const
    {
        return commaSep;
    }

    void ReadWritable::setCsv(bool value)
    {
        commaSep = value;
    }

    istream& operator>>(istream& is, ReadWritable& rw)
    {
        rw.read(is);
        return is;
    }

    ostream& operator<<(ostream& os, const ReadWritable& rw)
    { 
        rw.write(os);
        return os;
    }

} // namespace sdds