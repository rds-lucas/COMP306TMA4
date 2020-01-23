#include <iostream>
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

    bool insert(T const &  toInsert)
    {
        auto duplicate = std::find(v.begin(), v.end(), toInsert);
        if (duplicate != v.end()) // if no duplicate
        {
            v.push_back((T*)&toInsert);
            std::sort(v.begin(), v.end());
            return true;
        }
        else
        {
            return false;
        }
    }

    bool empty() const
    {
        return v.empty();
    }

    int size() const
    {
        return v.size()
    }

    int max_size() const
    {
        return v.max_size();
    }

    void clear()
    {
        v.clear();
    }

    iterator erase(const T& toErase)
    {
        if (std::find(this->begin(), this->end(), toErase) != this->end())
        {
            return v.erase(toErase);
        }
        else
        {
            return nullptr;
        }
    }

    iterator find(const T& toFind)
    {
        return std::find(this->begin(), this->end(), toFind);
    }

    class iterator
    {
    private:
        Set s;
        int index;

    public:
        explicit iterator(Set& is)
            : s(is), index(0)
        {
        }
        iterator(Set& is, int)
            : s(is), index(s.v.size())
        {
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

        T& current() const
        {
            return *s.v.at(index);
        }

        int operator++()   // prefix
        {
            return *s.v.at(++index);
        }

        int operator++(int)  //postfix
        {
            return *s.v.at(index++);
        }

        int operator--()   // prefix
        {
            return *s.v.at(--index);
        }

        int operator--(int)  //postfix
        {
            return *s.v.at(index--);
        }

        iterator& operator+=(int amount)
        {
            s.v.at(index + amount); // use built in range check from vector class
            index += amount;
            return *this;
        }

        iterator& operator-=(int amount)
        {
            s.v.at(index - amount); // use built in range check from vector class
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

    iterator begin()
    {
        return iterator(*this);
    }

    iterator end()
    {
        return iterator(*this, 0);
    }

    iterator rbegin()
    {
        return iterator(*this, 0);
    }

    iterator rend()
    {
        return iterator(*this);
    }


    void printSet()
    {
        std::cout << "{";

        for (iterator i = begin(); i != end(); ++i)
        {
            std::cout << "{" << i;
            if (i != end())
            {
                std::cout << "}, ";
            }
        }

        std::cout << "}}" << std::endl;
    }
};

int main()
{

    Set<int> s = Set<int>();
    s.insert(4);
    s.insert(-951);
    s.insert(-297);
    s.insert(122);
    s.insert(599);
    s.insert(-120);
    s.insert(-774);
    s.insert(-738);
    s.insert(103);
    s.insert(260);
    s.insert(755);

    s.printSet();

    Set<double> ss = Set<double>();
    ss.insert(4.0);
    ss.insert(-95.1);
    ss.insert(-29.7);
    ss.insert(12.2);
    ss.insert(59.9);
    ss.insert(-1.20);
    ss.insert(-7.74);
    ss.insert(-73.8);
    ss.insert(10.3);
    ss.insert(26.0);
    ss.insert(755.0);

    s.printSet();


}