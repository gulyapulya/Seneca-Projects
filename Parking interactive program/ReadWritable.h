/* Citation and Sources...
Final Project Milestone 3
Module: ReadWritable
Filename: ReadWritable.h
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
#ifndef SDDS_READWRITABLE_H__
#define SDDS_READWRITABLE_H__

#include <iostream>

namespace sdds
{
	class ReadWritable
    {
        bool commaSep;
    public:
        ReadWritable();
        virtual ~ReadWritable() {}
		bool isCsv()const;
        void setCsv(bool);
        virtual std::istream& read(std::istream & = std::cin) = 0;
        virtual std::ostream& write(std::ostream & = std::cout) const = 0;
    };
    std::istream& operator>>(std::istream&, ReadWritable&);
    std::ostream& operator<<(std::ostream&, const ReadWritable&);
}
#endif
