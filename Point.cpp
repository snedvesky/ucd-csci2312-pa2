//Scott Nedvesky 104976030
//CSC 2421
//PA2
//March 1, 2016
//Point.cpp

#include <math.h>
#include <string>
#include <sstream>
#include "point.h"

using namespace Clustering;
namespace Clustering {
    
    unsigned int Point::__idGen=0;
    
    
    Point::Point(int __nDimension) {
        
        __dim = __nDimension;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++)
            __values[i] = 0.0;
        __id=__idGen++;
    }
    
    Point::Point(int d, double * aY)
    {
        __id = __idGen;
        ++__idGen;
        __dim = d;
        __values = new double[__dim];
        
        for (int i = 0; i < __dim; ++i) {
            __values[i] = aY[i];
        }
    }
    
    
    
    // Big three: cpy ctor, overloaded operator=, dtor
    
    Point::Point(const Point &copy)
    {
        __dim = copy.__dim;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++)
            __values[i] = copy.__values[i];
        __id = copy.__id;
    }
    
    Point &Clustering::Point::operator=(const Point &p)
    {
        __id = ++__idGen;
        __dim = p.getDims();
        delete[]__values;
        __values = new double[__dim];
        for (int i = 0; i < __dim; ++i)
        {
            __values[i] = p.getValue(i);
        }
        return *this;
    }
    
    Point::~Point()
    {
        if(__values != nullptr)
        {
            delete [] __values;
        }
    }
    
    
    
    // Accessors & Mutators
    
    int Point::getId() const
    {
        return __id;
    }
    
    int Point::getDims() const
    {
        return __dim;
    }
    
    void Point::setValue(int idx, double nValue)
    {
        __values[idx] = nValue;
    }
    
    double Point::getValue(int idx) const
    {
        return __values[idx];
    }
    
    
    // Functions
    
    double Point::distanceTo(const Point &dPoint) const
    {
        double SqrOfD =0;
        double i1 = 0;
        double i2 = 0;
        
        for (int i = 0; i < __dim; ++i)
        {
            i1 = dPoint.__values[i] - __values[i];
            i2 = dPoint.__values[i] - __values[i];
            SqrOfD +=(i1 * i2);
        }
        return (sqrt(SqrOfD));
    }
    
    
    // Overloaded operators
    
    // Members
    
    Point &Point::operator*=(double right)
    {
        for (int i = 0; i < __dim; i++)
            __values[i] *= right;
        return *this;
    }
    
    Point &Point::operator/=(double Q)
    {
        for (int i = 0; i < __dim; i++)
            __values[i] /= Q;
        return *this;
    }
    
    const Point Point::operator*(double Q) const
    {
        Point p(*this);
        p *= Q;
        return p;
    }
    
    const Point Point::operator/(double Q) const
    {
        Point p(*this);
        p /= Q;
        return p;
    }
    
    
    
    
    
    double &Point::operator[](int idx)
    {
        return __values[idx];
    }
    
    
    
    
    // Friends
    
    Point &operator+=(Point &left, const Point &right)
    {
        for (int i = 0; i < left.__dim; ++i) {
            left.__values[i] += right.__values[i];
        }
        return left;
    }
    
    Point &operator-=(Point &left, const Point &right)
    {
        for (int i = 0; i < left.__dim; ++i) {
            left.__values[i] -=right.__values[i];
        }
        return left;
    }
    
    const Point operator+(const Point &left, const Point &right)
    {
        Clustering::Point tempP(left);
        tempP +=right;
        return tempP;
    }
    
    const Point operator-(const Point &left, const Point &right)
    {
        Clustering::Point tempP(left);
        tempP -=right;
        return tempP;
    }
    
    
    
    
    bool operator==(const Point &left, const Point &right)
    {
        bool A =false;
        if (left.__id == right.__id) {
            if (left.__dim == right.__dim) {
                A = true;
                for (int i = 0; i<left.__dim; ++i) {
                    if (left.__values[i] != right.__values[i]) {
                        A = false;
                        break;
                    }
                }
            }
        }
        return A;
    }
    
    bool operator!=(const Point &left, const Point &right)
    {
        return !operator==(left, right);
    }
    
    
    
    
    
    bool operator<(const Point &left, const Point &right)
    {
        bool L = false;
        for (int i = 0; i < left.__dim; i++)
        {
            if (left.__values[i] < right.__values[i])
                return true;
            if(left.__values[i]>right.__values[i])
                return false;
        }
        return L;
    }
    
    bool operator>(const Point &left, const Point &right)
    {
        return operator<(right, left);
    }
    
    bool operator<=(const Point &left, const Point &right)
    {
        return !operator>(left, right);
    }
    
    bool operator>=(const Point &left, const Point &right)
    {
        return !operator<(left, right);
    }
    
    std::ostream &operator<<(std::ostream &outputStream, const Point &p)
    {
        for (int i = 0; i < p.__dim; ++i) {
            outputStream << p.__values[i];
            if(i !=(p.__dim-1))
                outputStream << ", ";
        }
        return outputStream;
    }
    
    std::istream &operator>>(std::istream &inputStream, Point &p)   
    {
        std::string temp;
        for (int i = 0; i < p.__dim; ++i) {
            getline(inputStream, temp, ',');
            std::stringstream ss (temp);
            ss >> p.__values[i];
        }
        return inputStream;
    }
}
