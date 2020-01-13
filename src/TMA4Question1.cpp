//
// Created by tommyvct on 06/01/2020.
//

//#include "TMA4Question1.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

//using namespace std;

const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;

int maximum(int& a, int& b, int& c, int& d)
{
    return std::max(std::max(a, b), std::max(c, d));
}

int maximum(int& a, int& b, int& c)
{
    return std::max(std::max(a, b), c);
}

int minimum(int& a, int& b, int& c, int& d)
{
    return std::min(std::min(a, b), std::min(c, d));
}

int minimum(int& a, int& b, int& c)
{
    return std::min(std::min(a, b), c);
}



class Point
{
private:
    int x;
    int y;
public:
    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    Point() : x(0), y(0) {}
    Point(int newX, int newY) : x(newX), y(newY) {}
    Point(const Point& copy) : x(copy.x), y(copy.y) {} // NOLINT(hicpp-use-equals-default,modernize-use-equals-default)

    friend std::ostream& operator<<(std::ostream& ostream,
                                    const Point& point)
    {
        return ostream << point.to_string();
    }

    std::string to_string() const
    {
        // return "(x, y)"
        return "(" + std::to_string(x) + ", " +  std::to_string(y) + ")";
    }

    Point operator+ (const Point& rvalue) const
    {
        return {this->x + rvalue.x, this->y + rvalue.y};
    }

    Point operator- (const Point& rvalue) const
    {
        return {this->x - rvalue.x, this->y - rvalue.y};
    }

    double distance(Point& a)
    {
        int deltaLength = std::abs(a.x - this->x);
        int deltaHeight = std::abs(a.y - this->y);
        return std::sqrt(std::pow(deltaLength, 2) + std::pow(deltaHeight, 2));
    }

};

class Shape
{
protected:
    std::vector<Point> _boundingBox;


public:
    Shape() = default;
    Shape(Point&& upperLeft, Point&& lowerLeft, Point&& lowerRight, Point&& upperRight)
    {
        _boundingBox = std::vector<Point>();
        _boundingBox.push_back(upperLeft);
        _boundingBox.push_back(lowerLeft);
        _boundingBox.push_back(lowerRight);
        _boundingBox.push_back(upperRight);
    }
    virtual ~Shape() = default;

    virtual double area() = 0;
    virtual double circumference() = 0;
    virtual std::vector<Point>& boundingBox() = 0;
    virtual void display() = 0;

};

class Circle : public Shape
{
private:
    Point centre;
    int radius;

public:
    Circle(): centre(0, 0), radius(0), Shape() {}
    Circle(int centreX, int centreY, int newRadius):
        centre(centreX, centreY),
        radius(newRadius),
        Shape
        (
            Point(centreX - newRadius, centreX + newRadius),
            Point(centreX - newRadius, centreX - newRadius),
            Point(centreX + newRadius, centreX - newRadius),
            Point(centreX + newRadius, centreX + newRadius)
        )
    {}
//    Circle(const Circle& copy) : centre(copy.centre), radius(copy.radius) {}

    double area() override
    {
        return PI * radius * radius; // pi * r ^ 2
    }

    double circumference() override
    {
        return 2.0 * PI * radius;
    }

    std::vector<Point>& boundingBox() override
    {
        return this->_boundingBox;
    }

    void display() override
    {
        using namespace std;

        cout << "Circle" << endl;
        cout << "centre = " << this->centre << endl;
        cout << "radius = " << this->radius << endl;

        cout << fixed;
        cout.precision(4);
        cout << "area = "   << this->area() << endl;
        cout << "circumference = " << this->circumference() << endl;

        cout << "boundingBox = " << this->boundingBox()[0] << ", ";
        cout << this->boundingBox()[1] << ", ";
        cout << this->boundingBox()[2] << ", ";
        cout << this->boundingBox()[3] << endl;
    }
};

class Triangle : public Shape
{
private:
    Point p1;
    Point p2;
    Point p3;

public:
    Triangle(): p1(0, 0), p2(0, 0), p3(0, 0) {}
    Triangle(int p1X, int p1Y, int p2X, int p2Y, int p3X, int p3Y) :
        p1(p1X, p1Y),
        p2(p2X, p2Y),
        p3(p3X, p3Y),
        Shape
        (
            Point(minimum(p1X, p2X, p3X), maximum(p1Y, p2Y, p3Y)),
            Point(minimum(p1X, p2X, p3X), minimum(p1Y, p2Y, p3Y)),
            Point(maximum(p1X, p2X, p3X), minimum(p1Y, p2Y, p3Y)),
            Point(maximum(p1X, p2X, p3X), maximum(p1Y, p2Y, p3Y))
        )
    {}

    double area() override
    {
        return
                (double) (_boundingBox[2].getX() - _boundingBox[1].getX()) *
                (double) (_boundingBox[0].getY() - _boundingBox[1].getY()) / 2;
    }

    double circumference() override
    {
        return p1.distance(p2) + p1.distance(p3) + p2.distance(p3);
    }

    std::vector<Point>& boundingBox() override
    {
        return this->_boundingBox;
    }

    void display() override
    {
        using namespace std;

        cout << "Triangle" << endl;
        cout << "p1 = " << p1 << endl;
        cout << "p2 = " << p2 << endl;
        cout << "p3 = " << p3 << endl;

        cout << fixed;
        cout.precision(4);
        cout << "area = "   << this->area() << endl;
        cout << "circumference = " << this->circumference() << endl;

        cout << "boundingBox = " << this->boundingBox()[0] << ", ";
        cout << this->boundingBox()[1] << ", ";
        cout << this->boundingBox()[2] << ", ";
        cout << this->boundingBox()[3] << endl;
    }
};

class Square : public Shape
{
private:
    Point p1;
    Point p2;
    Point p3;
    Point p4;

public:
    Square(): p1(0, 0), p2(0, 0), p3(0, 0), p4(0, 0) {}
    Square(int p1X, int p1Y, int p2X, int p2Y, int p3X, int p3Y, int p4X, int p4Y) :
            p1(p1X, p1Y),
            p2(p2X, p2Y),
            p3(p3X, p3Y),
            p4(p4X, p4Y),
            Shape
            (
                    Point(minimum(p1X, p2X, p3X, p4X), maximum(p1Y, p2Y, p3Y, p4Y)),
                    Point(minimum(p1X, p2X, p3X, p4X), minimum(p1Y, p2Y, p3Y, p4Y)),
                    Point(maximum(p1X, p2X, p3X, p4X), minimum(p1Y, p2Y, p3Y, p4Y)),
                    Point(maximum(p1X, p2X, p3X, p4X), maximum(p1Y, p2Y, p3Y, p4Y))
            )
    {}

    double area() override
    {
        // TODO: figure out how this works
        return -99;
    }

    double circumference() override
    {
        return p1.distance(p2) + p2.distance(p3) + p3.distance(p4) + p4.distance(p1);
    }

    std::vector<Point>& boundingBox() override
    {
        return this->_boundingBox;
    }

    void display() override
    {
        using namespace std;

        cout << "Square" << endl;
        cout << "p1 = " << p1 << endl;
        cout << "p2 = " << p2 << endl;
        cout << "p3 = " << p3 << endl;
        cout << "p4 = " << p4 << endl;

        cout << fixed;
        cout.precision(4);
        cout << "area = "   << this->area() << endl;
        cout << "circumference = " << this->circumference() << endl;

        cout << "boundingBox = " << this->boundingBox()[0] << ", ";
        cout << this->boundingBox()[1] << ", ";
        cout << this->boundingBox()[2] << ", ";
        cout << this->boundingBox()[3] << endl;
    }
};

int main()
{
    Point a = Point(3, 5);
    Point b = Point(5, 7);
    Point c;
    Point d;

    c = a + b;
    d = a - b;

    std::cout << c << std::endl;
    std::cout << d << std::endl;



    Circle cc = Circle(10, -5, 23);
    cc.display();

    std::cout << std::endl;

    Triangle tt = Triangle(0,0,10,10,-15,15);
    tt.display();

    std::cout << std::endl;

    Square ss = Square(5, -5, -10,7, 4,23, -6,12);
    ss.display();
}