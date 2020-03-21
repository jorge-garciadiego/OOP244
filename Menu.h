/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.h
Version 1.0
Author Jorge Garciadiego
Revision History
-----------------------------------------------------------
Date
Reason
2020/03/15 Preliminary release
2020/03/16 Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------*/


#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__

#include <iostream>

using namespace std;

const int MAX_NO_OF_ITEMS = 10;

namespace sdds {

    class MenuItem {
        char* m_item;
        friend class Menu;

        MenuItem(); //iorch
        explicit MenuItem(const char*);
        ~MenuItem();

        MenuItem(const MenuItem&) = delete; // disable copying
        //void operator=(const MenuItem&) const;
        bool isEmpty() const;
        void setItem(const char*);
        ostream& display(ostream& = cout) const;
    };

    class Menu {

        char* m_title;
        class MenuItem* m_items[MAX_NO_OF_ITEMS]{};
        int m_indentation;
        int m_index;
    public:
        Menu();
        Menu(const char*, const int = 0);

        ~Menu();

        Menu& operator=(const Menu&);
        Menu& operator=(const char*);

        operator bool() const;
        operator int() const;
        friend Menu& operator<<(Menu&, const char*);

        bool validTitle(const char*) const;

        bool isEmpty() const;
        void setTitle(const char*);
        void add(const char*);
        void empty();
        int run(istream& = cin, ostream& = cout) const;
        ostream& display(ostream& = cout) const;
    };
}

#endif