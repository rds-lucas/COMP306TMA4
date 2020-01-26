//: TMA4Question1.cpp

/**
 * Title: TMA4Question1.cpp
 * Description:
 *      A class hierarchy for simple geometry.
 * Date: January 20, 2020 
 * Author: Tommy Wu
 */

/**
 * DOCUMENTATION
 *
 * Program Purpose:
 *      1. Create 2 Point objects
 *      2. Create Circle, Triangle, Square objects
 *      3. Print their area, circunferenfce and coordinates of bounding box.
 *
 * Compile: clang++ TMA4Question1.cpp -o TMA4Question1
 * Execution : ./TMA4Question1
 */

/**
 * This program includes following test:
 *  1. Create and print Point (8, 12) and Point (-2, -2)
 *  2. Create and print a Circle with centre (10, -5), radius 23, area, circunferenfce and coordinates of bounding box
 *  3. Create and print a Triangle with Point (0, 0), (10, 10), (-15, 15), it's area, circunferenfce and coordinates of bounding box
 *  4. Create and print a Square with Point (5, -5), (-10, 7), (4, 23), (-6, 12), it's area, circunferenfce and coordinates of bounding box
 *  5. Create and print a Square with Point (5, 5), (-5, 5), (-5, -5), (5, -5), it's area, circunferenfce and coordinates of bounding box
 *
 * The program should generate following output from stdout:
 *	Point (8, 12)
 *  Point (-2, -2)
 *
 *  Circle
 *  centre = (10, -5)
 *  radius = 23
 *  area = 1661.9025
 *  circumference = 144.5133
 *  boundingBox = (-13, 33), (-13, -13), (33, -13), (33, 33)
 *
 *  Triangle
 *  p1 = (0, 0)
 *  p2 = (10, 10)
 *  p3 = (-15, 15)
 *  area = 187.5000
 *  circumference = 60.8504
 *  boundingBox = (-15, 15), (-15, 0), (10, 0), (10, 15)
 *
 *  Square
 *  p1 = (5, -5)
 *  p2 = (-10, 7)
 *  p3 = (4, 23)
 *  p4 = (-6, 12)
 *  area = 58.5000
 *  circumference = 75.5842
 *  boundingBox = (-10, 23), (-10, -5), (5, -5), (5, 23)
 *
 *  Square
 *  p1 = (5, 5)
 *  p2 = (-5, 5)
 *  p3 = (-5, -5)
 *  p4 = (5, -5)
 *  area = 100.0000
 *  circumference = 40.0000
 *  boundingBox = (-5, 5), (-5, -5), (5, -5), (5, 5)
 */

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

    Point() : x(0), y(0)
    {
    }

    Point(int newX, int newY) : x(newX), y(newY)
    {
    }

    Point(const Point& copy) : x(copy.x), y(copy.y) // NOLINT(hicpp-use-equals-default,modernize-use-equals-default)
    {
    }

    friend std::ostream& operator<<(std::ostream& ostream,
        const Point& point)
    {
        return ostream << point.to_string();
    }

    std::string to_string() const
    {
        // return "(x, y)"
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

    Point operator+(const Point& rvalue) const
    {
        return { this->x + rvalue.x, this->y + rvalue.y };
    }

    Point operator-(const Point& rvalue) const
    {
        return { this->x - rvalue.x, this->y - rvalue.y };
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

    // area and circumference can really be a construct-time calculated field, and stored in this base class.
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
    Circle() : Shape(), centre(0, 0), radius(0)
    {
    }

    Circle(int centreX, int centreY, int newRadius) :
        Shape
        (
            Point(centreX - newRadius, centreX + newRadius),
            Point(centreX - newRadius, centreX - newRadius),
            Point(centreX + newRadius, centreX - newRadius),
            Point(centreX + newRadius, centreX + newRadius)
        ),
        centre(centreX, centreY),
        radius(newRadius)
    {
    }
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
        cout << "area = " << this->area() << endl;
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
    Triangle() : p1(0, 0), p2(0, 0), p3(0, 0)
    {
    }

    Triangle(int p1X, int p1Y, int p2X, int p2Y, int p3X, int p3Y) :
        Shape
        (
            Point(minimum(p1X, p2X, p3X), maximum(p1Y, p2Y, p3Y)),
            Point(minimum(p1X, p2X, p3X), minimum(p1Y, p2Y, p3Y)),
            Point(maximum(p1X, p2X, p3X), minimum(p1Y, p2Y, p3Y)),
            Point(maximum(p1X, p2X, p3X), maximum(p1Y, p2Y, p3Y))
        ),
        p1(p1X, p1Y),
        p2(p2X, p2Y),
        p3(p3X, p3Y)
    {
    }

    double area() override
    {
        return
            (double)(_boundingBox[2].getX() - _boundingBox[1].getX()) *
            (double)(_boundingBox[0].getY() - _boundingBox[1].getY()) / 2;
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
        cout << "area = " << this->area() << endl;
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
    Square() : p1(0, 0), p2(0, 0), p3(0, 0), p4(0, 0)
    {
    }

    // these points must be passed in the correct order for area() and circumference() to work properly.
    // ABCD should be at least a closed quadrilateral, without any of its sides crossing each other.
    // ABDC or other permutations would not work!
    Square(int p1X, int p1Y, int p2X, int p2Y, int p3X, int p3Y, int p4X, int p4Y) :
        Shape
        (
            Point(minimum(p1X, p2X, p3X, p4X), maximum(p1Y, p2Y, p3Y, p4Y)),
            Point(minimum(p1X, p2X, p3X, p4X), minimum(p1Y, p2Y, p3Y, p4Y)),
            Point(maximum(p1X, p2X, p3X, p4X), minimum(p1Y, p2Y, p3Y, p4Y)),
            Point(maximum(p1X, p2X, p3X, p4X), maximum(p1Y, p2Y, p3Y, p4Y))
        ),
        p1(p1X, p1Y),
        p2(p2X, p2Y),
        p3(p3X, p3Y),
        p4(p4X, p4Y)
    {
    }

    double area() override
    {
        // Think the word of 'square', it should be a polygon with 4 sides with equal length, and 4 rectangle corner.
        // It should be defined with an origin, length and a direction, or as simple as a diagonal further defined by
        // 2 points.

        // Don't have enough time on this. Used formula from http://mathworld.wolfram.com/PolygonArea.html

        // had the program treat 4 points like a quadrilateral, and find the area for the quadrilateral.
        // (here the crossing lines would still be an issue)

        return fabs(0.5 *
            (
                p1.getX() * p2.getY() - p2.getX() * p1.getY() +
                p2.getX() * p3.getY() - p3.getX() * p2.getY() +
                p3.getX() * p4.getY() - p4.getX() * p3.getY() +
                p4.getX() * p1.getY() - p1.getX() * p4.getY()
            ));
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
        cout << "area = " << this->area() << endl;
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

    std::cout << "Point " << c << std::endl;
    std::cout << "Point " << d << std::endl;

    std::cout << std::endl;

    Circle cc = Circle(10, -5, 23);
    cc.display();

    std::cout << std::endl;

    Triangle tt = Triangle(0, 0, 10, 10, -15, 15);
    tt.display();

    std::cout << std::endl;

    Square ss = Square(5, -5, -10, 7, 4, 23, -6, 12);
    ss.display();

    std::cout << std::endl;

    Square sss = Square(5, 5, -5, 5, -5, -5, 5, -5);
    sss.display();
} ///:~