//: TMA4Question3.cpp

/**
 * Title: TMA4Question3.cpp
 * Description:
 *       A homebrew Set template implemented using vector.
 * Date: January 20, 2020 
 * Author: Tommy Wu
 */

/**
 * DOCUMENTATION
 *
 * Program Purpose:
 *      1. Create instances of homebrew Set<int>, Set<double>, Set<string> and 
 *         Set<Integer>, then test normal insert, erase and iterator operations
 *      2. Create instances of STL std::set<int>, std::set<double>, 
 *         std::set<string> and std::set<Integer>, then test normal insert, 
 *         erase and iterator operations.
 *
 * Compile: clang++ TMA4Question3.cpp -o TMA4Question3
 * Execution : ./TMA4Question3
 */

/**
 * Test plan:
 *      1. Create instances of homebrew Set<int>, Set<double>, Set<string> and 
 *         Set<Integer>, then test normal insert, erase and iterator operations
 *      2. Create instances of STL std::set<int>, std::set<double>, 
 *         std::set<string> and std::set<Integer>, then test normal insert, 
 *         erase and iterator operations.
 *      3. print them out and compare the results.
 * 
 * By compiling with -DDEBUG, the program should display more infomation like 
 * what is inserted and what is not, duplicate or not found.
 * 
 * The program should generate following output from stdout:
 * {{-951}, {-774}, {-738}, {-297}, {-120}, {4}, {103}, {122}, {260}, {599}, {755}}
 * {{-95.1}, {-73.8}, {-29.7}, {-7.74}, {-1.2}, {4}, {10.3}, {12.2}, {26}, {59.9}, {755}}
 * {{C++}, {great!}, {is}, {really}, {template}}
 * {{C++}, {is}, {really}, {template}, {terrible!}}
 * {}
 * 
 * 
 * 
 * {{-951}, {-774}, {-738}, {-297}, {-120}, {4}, {103}, {122}, {260}, {599}, {755}}
 * {{-95.1}, {-73.8}, {-29.7}, {-7.74}, {-1.2}, {4}, {10.3}, {12.2}, {26}, {59.9}, {755}}
 * {{C++}, {great!}, {is}, {really}, {template}}
 * {{C++}, {is}, {really}, {template}, {terrible!}}
 * {}
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>


template<typename T>
class Set
{
    private:
    std::vector<T>* v;


    public:
    Set()
    {
        v = new std::vector<T>();
    }

    ~Set()
    {
        delete v;
    }

    class iterator;
    friend class iterator;

    // insert an object
    // if the object is not a duplicate, insert it and return the iterator to 
    // the inserted object
    // if the object is a duplicate, return the iterater to the duplicated 
    // object in the set
    iterator insert(const T& toInsert)
    {
        // search for duplicate
        auto search = std::find(v->begin(), v->end(), toInsert);   

        if (search == v->end())  // if not a duplicate
        {
            #ifdef DEBUG
            std::cout << "inserted: " << toInsert << std::endl;
            #endif
            v->push_back(toInsert);      // push back to vector
            std::sort(v->begin(), v->end());   // optional, sort it
            // obtain the new location
            search = std::find(v->begin(), v->end(), toInsert);   
        }
            // else (duplicate) return the iterator to the duplicated object
        else
        {
            #ifdef DEBUG
            std::cout << "duplicate: " << toInsert << std::endl;
            #endif
        }
        int index = std::distance(v->begin(), search);
        return iterator(*this, index);
    }

    // return true if the set is an empty set, otherwise return false
    bool empty() const
    {
        return v->empty();
    }

    // return number of elements in the set
    int size() const
    {
        return v->size();
    }

    // return the max size that current vector can hold without enlargement
    int max_size() const
    {
        return v->max_size();
    }

    // clear everything and empty the set
    void clear()
    {
        std::cout << "everything gone!" << std::endl;
        v->clear();
    }
    
    // remove given object from the set.
    // if object is found and removed, return true
    // otherwise return false
    bool erase(const T& toErase)
    {
        auto search = std::find(v->begin(), v->end(), toErase);

        if (search != v->end())  // if found
        {
            #ifdef DEBUG
            std::cout << "erased: " << toErase << std::endl;
            #endif
            v->erase(search);
            return true;
        }
        else  // if not found
        {
            #ifdef DEBUG
            std::cout << "not found: " << toErase << std::endl;
            #endif
            return false;
        }
    }

    iterator begin()
    {
        return iterator(*this);
    }

    iterator end()
    {
        return iterator(*this, false);
    }

    void printSet()
    {
        std::cout << "{";
        
        for (iterator i = this->begin(); i != this->end(); i++)
        {
            if (i == this->begin())
            {
                std::cout << "{";
            }
            else
            {
                std::cout << ", {";
            }
            std::cout << i << "}"; 
        }

        std::cout << "}" << std::endl;
    }


    // not a standard iterator inherited from std::vector::iterator
    class iterator 
    {
        private:
        Set& s;
        int index;


        public:
        explicit iterator(Set& is)
            : s(is), index(0)
        {
        }

        /// return end element
        iterator(Set& is, bool)
            : s(is), index(s.v->size())
        {
        }

        iterator(Set& is, int index)
            : s(is), index(index)
        {
        }

        iterator(const iterator& toCopy)
            : s(toCopy.s), index(toCopy.index)
        {
        }

        T& current() const
        {
            return s.v->at(index);
        }

        iterator& operator=(const iterator& toCopy)
        {
            if (this == &toCopy)
            {
                return *this;
            }

            s = toCopy.s;
            index = toCopy.index;
            return *this;
        }

        iterator& operator++()   // prefix
        {
            this->index++;
            return *this;
        }

        iterator operator++(int)  //postfix
        {
            iterator ret(*this);
            ++(*this);
            return ret;
        }

        iterator& operator--()   // prefix
        {
            this->index--;
            return *this;
        }

        iterator operator--(int)  //postfix
        {
            iterator ret(*this);
            --(*this);
            return ret;
        }

        iterator& operator+=(int amount)
        {
            s.v->at(index + amount); // use built in range check from vector class
            index += amount;
            return *this;
        }

        iterator& operator-=(int amount)
        {
            s.v->at(index - amount); // use built in range check from vector class
            index -= amount;
            return *this;
        }

        bool operator==(const iterator& rv) const
        {
            return index == rv.index;
        }

        bool operator!=(const iterator& rv) const
        {
            return index != rv.index;
        }

        friend std::ostream& operator<<(std::ostream& os, const iterator& it)
        {
            return os << it.current();
        }

        friend iterator Set<T>::erase(iterator&);
    };

    // remove the object that given iterator points to
    // if we found the object from given iterator, then erase it, return the 
    // next iterator
    // otherwise return the end iterator
    iterator erase(iterator& toErase)
    {
        auto next = v->erase(v->begin() + toErase.index);

        if (next == v->end())
        {
            return iterator(*this, false);
        }

        int nextIndex = std::distance(v->begin(), next);
        return iterator(*this, nextIndex);
    }

};

// a simple Integer class, with basic arithmetic operator overloaded
class Integer
{
    private:
    int payload;

    public:
    // constructors
    Integer() : payload(0) {}
    Integer(int newInteger) : payload(newInteger) {}
    Integer(const Integer& toCopy) : payload(toCopy.payload) {}

    //unary +
    const Integer operator+ () const
    {
        return *this;
    }  // unary + does nothing!

    //unary -
    const Integer operator- () const
    {
        return Integer(0 - this->payload);
    }

    // binary +
    const Integer operator+(const Integer& rvalue) const
    {
        return Integer(this->payload + rvalue.payload);
    }

    const Integer operator+(const int& rvalue) const
    {
        return Integer(this->payload + rvalue);
    }

    friend const Integer operator+(const int& lvalue, const Integer& rvalue)
    {
        return Integer(lvalue + rvalue.payload);
    }

    // binary -
    const Integer operator-(const Integer& rvalue) const
    {
        return Integer(this->payload - rvalue.payload);
    }

    const Integer operator-(const int& rvalue) const
    {
        return Integer(this->payload - rvalue);
    }

    friend const Integer operator-(const int& lvalue, const Integer& rvalue)
    {
        return Integer(lvalue - rvalue.payload);
    }

    // binary *
    const Integer operator*(const Integer& rvalue) const
    {
        return Integer(this->payload * rvalue.payload);
    }

    const Integer operator*(const int& rvalue) const
    {
        return Integer(this->payload * rvalue);
    }

    friend const Integer operator*(const int& lvalue, const Integer& rvalue)
    {
        return Integer(lvalue * rvalue.payload);
    }

    // binary /
    const Integer operator/(const Integer& rvalue) const
    {
        return Integer(this->payload / rvalue.payload);
    }

    const Integer operator/(const int& rvalue) const
    {
        return Integer(this->payload / rvalue);
    }

    friend const Integer operator/(const int& lvalue, const Integer& rvalue)
    {
        return Integer(lvalue / rvalue.payload);
    }

    bool operator==(const Integer& rv) const
    {
        return payload == rv.payload;
    }

    //prefix ++
    Integer& operator++ ()
    {
        ++ this->payload;
        return *this;
    }

    //prefix --
    Integer& operator-- ()
    {
        -- this->payload;
        return *this;
    }

    //postfix ++
    Integer operator++ (int)
    {
        Integer ret(*this);
        this->payload++;
        return ret;
    }

    //postfix --
    Integer operator-- (int)
    {
        Integer ret(*this);
        this->payload--;
        return ret;
    }

    bool operator<(const Integer& rvalue) const
    {
        return this->payload < rvalue.payload;
    }

    friend std::ostream& operator<<(std::ostream& loperand,
        const Integer& roperand)
    {
        return loperand << std::to_string(roperand.payload);
    }
};

template<typename T>
void print_set(std::set<T>& toPrint)
{
    using namespace std;

    cout << "{";

    for (auto i = toPrint.begin(); i != toPrint.end(); i++)
    {
            if (i == toPrint.begin())
            {
                std::cout << "{";
            }
            else
            {
                std::cout << ", {";
            }
            std::cout << *i << "}"; 
    }

    cout << "}" << endl;
}

int main()
{
    Set<int> S = Set<int>();
    S.insert(-951);
    S.insert(4);
    S.insert(-297);
    S.insert(122);
    S.insert(599);
    S.insert(-120);
    S.insert(-774);
    S.insert(599);
    S.insert(-738);
    S.insert(103);
    S.insert(260);
    S.insert(755);
    S.printSet();

    Set<double> Ss = Set<double>();
    Ss.insert(4.0);
    Ss.insert(-95.1);
    Ss.insert(-29.7);
    Ss.insert(12.2);
    Ss.insert(59.9);
    Ss.insert(-1.20);
    Ss.insert(-7.74);
    Ss.insert(-73.8);
    Ss.insert(10.3);
    Ss.insert(59.9);
    Ss.insert(-1.20);
    Ss.insert(26.0);
    Ss.insert(755.0);
    Ss.printSet();

    Set<std::string> Sss = Set<std::string>();
    Sss.insert("C++");
    Sss.insert("template");
    Sss.insert("is");
    Sss.insert("really");
    Sss.insert("really");
    Sss.insert("great!");
    Sss.printSet();
    Sss.erase("really");
    Sss.erase("really");
    Sss.erase("hfihsdlk");
    auto i = Sss.begin();
    while (i != Sss.end())
    {
        if (i.current() == "great!")
        {
            i = Sss.erase(i);
            break;
        }
        
        i++;
    }
    Sss.insert("really");
    Sss.insert("terrible!");
    Sss.printSet();

    Integer i1 = Integer(4);
    Set<Integer> Ssss = Set<Integer>();
    Ssss.insert(i1);
    Ssss.insert(i1);
    Ssss.erase(i1);
    Ssss.erase(i1);
    Ssss.printSet();

    std::cout << std::endl << std::endl << std::endl;

    std::set<int> s = std::set<int>();
    s.insert(-951);
    s.insert(4);
    s.insert(-297);
    s.insert(122);
    s.insert(599);
    s.insert(-120);
    s.insert(-774);
    s.insert(599);
    s.insert(-738);
    s.insert(103);
    s.insert(260);
    s.insert(755);
    print_set(s);

    std::set<double> ss = std::set<double>();
    ss.insert(4.0);
    ss.insert(-95.1);
    ss.insert(-29.7);
    ss.insert(12.2);
    ss.insert(59.9);
    ss.insert(-1.20);
    ss.insert(-7.74);
    ss.insert(-73.8);
    ss.insert(10.3);
    ss.insert(59.9);
    ss.insert(-1.20);
    ss.insert(26.0);
    ss.insert(755.0);
    print_set(ss);

    std::set<std::string> sss = std::set<std::string>();
    sss.insert("C++");
    sss.insert("template");
    sss.insert("is");
    sss.insert("really");
    sss.insert("really");
    sss.insert("great!");
    print_set(sss);
    sss.erase("really");
    sss.erase("really");
    sss.erase("hfihsdlk");
    for (auto i : sss)
    {
        if (i == "great!")
        {
            i = sss.erase(i);
        }
    }
    sss.insert("really");
    sss.insert("terrible!");
    print_set(sss);

    Integer i2 = Integer(4);
    std::set<Integer> ssss = std::set<Integer>();
    ssss.insert(i2);
    ssss.insert(i2);
    ssss.erase(i2);
    ssss.erase(i2);
    print_set(ssss);
} ///:~