//Scott Nedvesky 104976030
//CSC 2421
//PA2
//March 1, 2016
//Cluster.cpp

#include <string>
#include <sstream>
#include <algorithm>
#include "Cluster.h"
#include "assert.h"

using namespace Clustering;
namespace Clustering {
    
    LNode::LNode(const Point & nPoint, LNodePtr nxtPtr):point(nPoint)	
    {
        next=nxtPtr;
    }
    
    Clustering::Cluster::Cluster()
    {
        __size = 0;
        __points = nullptr;
    }
    
    
    // The big three: cpy ctor, overloaded operator=, dtor
    
    Clustering::Cluster::Cluster(const Cluster &C):Cluster()
    {
        for (int count = 0; count < C.__size; ++count)
        {
            add(C[count]);
        }
    }
    
    Cluster &Clustering::Cluster::operator=(const Cluster &C)
    {
        
        if (this == &C)
            return *this;
        else
        {
            if (__points != NULL)
            {
                LNodePtr currPtr = __points;
                LNodePtr nextPtr = NULL;
                while (currPtr != NULL)
                {
                    nextPtr = currPtr->next;
                    delete currPtr;
                    currPtr = nextPtr;
                }
                __size = 0;
                __points = NULL;
            }
            for (int count = 0; count < C.__size; ++count) {
                add(C[count]);
            }
        }
        return *this;
        
        
        
    }
    
    Clustering::Cluster::~Cluster()
    {
        if (__points != NULL)
        {
            LNodePtr previousPtr = __points;
            LNodePtr currentPtr = NULL;
            while (previousPtr != NULL)
            {
                currentPtr = previousPtr->next;
                delete  previousPtr;
                previousPtr = currentPtr;
            }
        }
    }
    
    
    
    
    // Getters/setters
    
    int Clustering::Cluster::getSize() const
    {
        return __size;
    }
    
    
    
    
    // Set functions: They allow calling c1.add(c2.remove(p));
    
    void Clustering::Cluster::add(const Point &point)
    {
        
        LNodePtr nNode = new LNode(point,nullptr);
        if (__points == nullptr) {
            __points = nNode;
        }
        else{
            LNodePtr current = __points;
            LNodePtr previous = nullptr;
            while (current !=nullptr) {
                if (current->point > point) {
                    break;
                }
                else{
                    previous = current;
                    current = current->next;
                }
            }
            if (current == __points) {
                nNode->next = __points;
                __points = nNode;
            }
            else{
                nNode->next = current;
                previous->next = nNode;
            }
            
        }
        __size++;
    }
    
    const Point &Clustering::Cluster::remove(const Point &p)
    {
        
        LNodePtr prev = nullptr, del = nullptr;
        if (__points == nullptr) {
            assert(__size == 0);
        } else if (__points->point == p) {
            del = __points;
            __points = __points->next;
            delete del;
            __size--;
        } else {
            prev = __points;
            del = __points->next;
            while (del != nullptr) {
                if (del->point == p) {
                    prev->next = del->next;
                    delete del;
                    __size--;
                    break;
                }
                prev = del;
                del = del->next;
            }
        }
        return p;
    }
    
    bool Clustering::Cluster::contains(const Point &point1)
    {
        for (LNodePtr pCursor = this->__points; pCursor != nullptr; pCursor = pCursor->next)
        {
            if (pCursor->point == point1){
                return true;
            }
        }
        return false;
    }
    
    
    
    
    // Overloaded operators
    
    // Members: Subscript
    
    const Point &Cluster::operator[](unsigned int idx) const
    {
        LNodePtr pCursor=__points;
        for(int i=0;(i<idx) && (pCursor->next!=nullptr); i++)
            pCursor=pCursor->next;
        return pCursor->point;
    }
    
    
    
    // Members: Compound assignment (Point argument)
    
    Cluster &Clustering::Cluster::operator+=(const Point &point1)
    {
        add(point1);
        return *this;
    }
    
    Cluster &Clustering::Cluster::operator-=(const Point &point1)
    {
        remove(point1);
        return *this;
    }
    
    
    
    // Members: Compound assignment (Cluster argument)
    
    Cluster &Clustering::Cluster::operator+=(const Cluster &clust1)
    {
        
        for (int i = 0; i < clust1.__size; i++)
        {
            if (!contains(clust1[i]))
                add(clust1[i]);
        }
        return *this;
    }
    
    Cluster &Clustering::Cluster::operator-=(const Cluster &clust1)
    {
        for (int i = 0; i < clust1.__size; i++)
            if (contains(clust1[i]))
                remove(clust1[i]);
        return *this;
    }
    
    
    // Friends: IO
    
    std::ostream &operator<<(std::ostream &oStream, const Cluster &clust1)
    {
        LNodePtr pCursor=clust1.__points;
        for(int i=0;i<clust1.__size;i++)
        {
            oStream << pCursor->point << std::endl;
            pCursor = pCursor->next;
        }
        return oStream;
    }
    std::istream &operator>>(std::istream &inputStream, Cluster &clust1)
    {
        
        std::string line;
        while(getline(inputStream, line))
        {
            std::stringstream linestream(line);
        }
        return inputStream;
    }
    
    
    
    // Friends: Comparison
    
    bool operator==(const Cluster &c1, const Cluster &c2)
    {
        if (c1.__size != c2.__size)
        {
            return false;
        }
        
        LNodePtr curr1 = c1.__points;
        LNodePtr curr2 = c2.__points;
        bool same = true;
        
        while (curr1 != NULL && curr2 != NULL)
        {
            if (curr1->point != curr2->point)
            {
                same = false;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return same;
    }
    
    bool operator!=(const Cluster &clust1, const Cluster &clust2)
    {
        return (!(clust1==clust2));
    }
    
    
    
    // Friends: Arithmetic (Cluster and Point)
    
    
    const Cluster operator+(const Cluster &clust1, const Point &point1)
    {
        Cluster clust2(clust1);
        clust2+=point1;
        
        return clust2;
    }
    
    const Cluster operator-(const Cluster & clust1, const Point & point1)
    {
        Cluster clust2(clust1);
        clust2-=point1;
        return clust2;
    }
    
    
    
    // Friends: Arithmetic (two Clusters)
    
    const Cluster operator+(const Cluster &clust1, const Cluster &clust2)
    {
        Cluster kick1(clust1);
        kick1+=clust2;
        return kick1;
    }
    const Cluster operator-(const Cluster &clust1, const Cluster &clust2)
    {
        Cluster kick1(clust1);
        kick1-=clust2;
        return kick1;
    }
    
}