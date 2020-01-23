#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


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

    iterator insert(const T& toInsert)
    {
        auto search = std::find(v->begin(), v->end(), toInsert);   // search for duplicate
//        int index = std::distance(v->begin(), search);   // get index for search


        if (search == v->end())  // if not a duplicate
        {
            std::cout << "not a duplicate" << toInsert << std::endl;

            v->push_back(toInsert);      // push back to vector
//            std::sort(v->begin(), v->end());   // sort it
            search = std::find(v->begin(), v->end(), toInsert);   // obtain the new location
        }
            // else (duplicate) return the iterator to the duplicated object
        else
        {
            std::cout << "duplicate" << std::endl;
        }
        int index = std::distance(v->begin(), search);
        return iterator(*this, index);
    }

    bool empty() const
    {
        return v->empty();
    }

    int size() const
    {
        return v->size();
    }

    int max_size() const
    {
        return v->max_size();
    }

    void clear()
    {
        v->clear();
    }

    // https://zh.cppreference.com/w/cpp/container/set/erase
    int erase(const T& toErase)
    {
        auto search = std::find(v->begin(), v->end(), toErase);

        if (search != v->end())  // if found
        {
            v->erase(search);
            return 1;
        }
        else  // if not found
        {
            return 0;
        }
    }

    iterator erase(iterator& toErase)
    {
        auto search = std::find(v->begin(), v->end(), toErase);

        if (search != v->end())  // if found return next iterator
        {
            search = v->erase(search);
            int index = std::distance(v->begin(), search);
            return iterator(*this, index);
        }
        else  // if not found return end iterator
        {
            return iterator(*this, true);
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

        //for (auto i : *v)

        for (iterator i = this->begin(); i != this->end(); i++)
        {
            std::cout << "{" << i;
            if (i != end())
            {
                std::cout << "}, "; // TODO: output
            }
        }

        std::cout << "}}" << std::endl;
    }


    class iterator // not a standard iterator inherited from std::vector::iterator
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

        iterator& operator=(const iterator& toCopy) // NOLINT(cert-oop54-cpp)
        {
            // I already handled self-assignment situation properly, retarded clang-tidy!
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
    };
};

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


    // const DoStuff& operator++ (DoStuff& a) is invalid in c++11!!!!
    // prefix overloaded operater++ function takes no parameters

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

    friend std::ostream& operator<<(std::ostream& loperand,
        const Integer& roperand)
    {
        return loperand << std::to_string(roperand.payload);
    }
};

int main()
{
    Integer i1 = Integer(4);
    Set<Integer> s = Set<Integer>();
    s.insert(i1);
    s.insert(i1);
    s.erase(i1);
    s.erase(i1);

    s.printSet();

//    Set<int> s = Set<int>();
//    s.insert(4);
//    s.insert(-951);
//    s.insert(-297);
//    s.insert(122);
//    s.insert(599);
//    s.insert(-120);
//    s.insert(-774);
//    s.insert(-738);
//    s.insert(103);
//    s.insert(260);
//    s.insert(755);
//
//    s.printSet();

//    Set<double> ss = Set<double>();
//    ss.insert(4.0);
//    ss.insert(-95.1);
//    ss.insert(-29.7);
//    ss.insert(12.2);
//    ss.insert(59.9);
//    ss.insert(-1.20);
//    ss.insert(-7.74);
//    ss.insert(-73.8);
//    ss.insert(10.3);
//    ss.insert(26.0);
//    ss.insert(755.0);
//
//    ss.printSet();


//    Set<std::string> sss = Set<std::string>();
//
//    sss.insert("fuck");
//    sss.insert("it");
//    sss.insert("fuck");
//    sss.insert("c++");
//    sss.insert("template!");
//
//    sss.printSet();

} ///:~