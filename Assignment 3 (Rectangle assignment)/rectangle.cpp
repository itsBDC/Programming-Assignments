#include <bits/stdc++.h>

using namespace std;

class Rectangle 
{
private:
    double width;
    double length;

public:
    Rectangle() : width(1.0), length(1.0) {}

    Rectangle(double w, double l) : width(1.0), length(1.0) 
    {
        setWidth(w);
        setLength(l);
    }

    double getWidth() const { return width; }
    double getLength() const { return length; }

    void setWidth(double w) 
    {
        if (w <= 0) {
            throw invalid_argument("Width must be greater than zero.");
        }
        width = w;
    }

    void setLength(double l) 
    {
        if (l <= 0) {
            throw invalid_argument("Length must be greater than zero.");
        }
        length = l;
    }

    double calculateArea() const { return width * length; }
    double calculatePerimeter() const { return 2 * (width + length); }
};

int main() 
{

    Rectangle r1;
    cout << "Rectangle 1 (default)\n";
    cout << "  Width:     " << r1.getWidth() << "\n";
    cout << "  Length:    " << r1.getLength() << "\n";
    cout << "  Area:      " << r1.calculateArea() << "\n";
    cout << "  Perimeter: " << r1.calculatePerimeter() << "\n\n";

    Rectangle r2(5.0, 3.0);
    cout << "Rectangle 2 (5 x 3)\n";
    cout << "  Width:     " << r2.getWidth() << "\n";
    cout << "  Length:    " << r2.getLength() << "\n";
    cout << "  Area:      " << r2.calculateArea() << "\n";
    cout << "  Perimeter: " << r2.calculatePerimeter() << "\n\n";

    r1.setWidth(10.5);
    r1.setLength(4.0);
    cout << "Rectangle 1 after setWidth(10.5) and setLength(4.0)\n";
    cout << "  Width:     " << r1.getWidth() << "\n";
    cout << "  Length:    " << r1.getLength() << "\n";
    cout << "  Area:      " << r1.calculateArea() << "\n";
    cout << "  Perimeter: " << r1.calculatePerimeter() << "\n\n";

    try 
    {
        r2.setWidth(-2.0);
    } catch (const invalid_argument& e) 
    {
        cout << "Error caught: " << e.what() << "\n";
    }
    cout << "Rectangle 2 width is still " << r2.getWidth() << "\n";

    return 0;
}
