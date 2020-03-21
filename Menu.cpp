/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.cpp
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

#include <iostream>
#include <cstring>
#include "Menu.h"
#include <iomanip>

using namespace std;

namespace sdds {

    MenuItem::MenuItem() {
        m_item = nullptr;
    }

    MenuItem::MenuItem(const char* item) {
        m_item = nullptr;
        setItem(item);
    }

    MenuItem::~MenuItem() {
        delete [] m_item;
        m_item = nullptr;
    }

    bool MenuItem::isEmpty() const {
        return m_item == nullptr;
    }

    void MenuItem::setItem(const char* item) {

        delete [] m_item;

        if (!isEmpty()){
            m_item = nullptr;
        } else {
            m_item = new char[strlen(item)+1];
            strcpy(m_item, item);
        }
    }

    ostream& MenuItem::display(ostream& os) const {
        os << m_item << endl;
        return os;
    }

    // Menu Class

    bool Menu::validTitle(const char* title) const {
        return (title != nullptr || title[0] != '\0');
    }

    void Menu::setTitle(const char * title) {
        if (validTitle(title)){

            delete [] m_title;


            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);
        }
    }

    Menu::Menu(const char * title, int indent) {
        m_title = nullptr;
        m_indentation = indent;
        setTitle(title);
        m_index = 0;

    }


    Menu::~Menu() {

        delete [] m_title;
        m_title = nullptr;

        for (int i = 0; i < m_index; i++) {
            if (m_items[i] != nullptr) {
                delete m_items[i];
                m_items[i] = nullptr;
            }
        }
    }

    Menu& Menu::operator=(const Menu& nMenu) {
        if (nMenu.m_title != nullptr) {
            setTitle(nMenu.m_title);

            for (int i = 0; i < m_index; i++)
                if (m_items[i] != nullptr)
                    delete m_items[i];

            if (nMenu.m_index > 0)
                for (int i = 0; i < nMenu.m_index; i++)
                    add(nMenu.m_items[i]->m_item);

            m_index = nMenu.m_index;
        } else
            empty();
        m_indentation = nMenu.m_indentation;
        return *this;
    }

    Menu& Menu::operator=(const char * nTitle) {
        if (nTitle != nullptr) {
            setTitle(nTitle);
        } else
            m_title = nullptr;

        return *this;
    }

    Menu::operator bool() const {
        return !isEmpty();
    }

    Menu::operator int() const {
        return run();
    }

    Menu& operator<<(Menu& nMenu, const char* item) {
        nMenu.add(item);
        return nMenu;
    }

    bool Menu::isEmpty() const {
        return m_title == nullptr;
    }

    void Menu::add(const char* item) {
        if (item != nullptr) {
            if (!isEmpty()) {
                if (m_index <= 10) {
                    m_items[m_index] = new MenuItem(item);
                    m_index++;
                    m_items[m_index] = nullptr;
                }
            }
        }
        else
            empty();
    }

    void Menu::empty() {
        m_index = 0;
        m_indentation = 0;
        m_items[0] = nullptr;
        m_title = nullptr;
    }

    int Menu::run(istream& is, ostream& os) const {
        int selection = 0;
        bool isValid = false;
        display(os);
        if (!isEmpty() && m_index > 0) {
            do {
                int tmp;
                is >> tmp;
                if (!is) {
                    os << "Invalid Integer, try again: ";
                    is.clear();
                }
                else if (tmp <= 0 || tmp > m_index) {
                    os << "Invalid selection, try again: ";
                    is.clear();
                }
                else {
                    selection = tmp;
                    isValid = true;
                }
                is.ignore(1000, '\n');
                is.clear();
            } while (!isValid);
        }
        return selection;
    }

    ostream& Menu::display(ostream& os) const {
        if (!isEmpty()) {
            for (int i = 0; i < m_indentation; i++){
                os << setfill(' ') << setw(4) << ' ';
            }
            os << m_title << endl;
            if (m_index > 0) {
                for (int i = 0; i < m_index; i++) {
                    for (int i = 0; i < m_indentation; i++){
                        os << setfill(' ') << setw(4) << ' ';
                    }
                    os << i + 1 << "- ";
                    m_items[i]->display();
                }
                for (int i = 0; i < m_indentation; i++){
                    os << setfill(' ') << setw(4) << ' ';
                }
                os << "> ";
            } else
                os << "No Items to display!" << endl;

        } else
            os << "Invalid Menu!" << endl;
        return os;
    }
}