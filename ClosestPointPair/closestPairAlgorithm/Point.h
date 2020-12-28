//
//  Point.h
//  closestPairAlgorithm
//
//  Created by syfo_dias on 20/12/2020.
//  Copyright © 2020 syfo_dias. All rights reserved.
//

#ifndef Point_h
#define Point_h

namespace syfo {
    
    template <typename T>
    struct Point
    {
        Point()
        :x{T()}, y{T()} {}
        Point(T x_val, T y_val)
        :x{x_val}, y{y_val} {}
        T x;
        T y;
        friend std::ostream& operator<<(std::ostream& os, const Point& point)
        {
            os << "[" << point.x << ", " << point.y << "]";
            return os;
        };
        
    };
    
    // helpers
    template <typename T>
    T dist (const Point<T>& p1, const Point<T>& p2)
    {
        return sqrt ( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
    }
    
    template <typename T>
    T dist (std::pair<Point<T>, Point<T>>& p)
    {
        return sqrt ( (p.first.x - p.second.x) *  (p.first.x - p.second.x) + (p.first.y - p.second.y) * (p.first.y - p.second.y) );
    }
    
    template <typename T>
    class PointPair
    {
    public:
        PointPair (Point<T> p1, Point<T> p2)
        :a {p1}, b {p2}
        {}
        ~PointPair()
        {}
        
        T getDistance()
        {
            return dist(a, b);
        }
        Point<T> first() const {return a;}
        Point<T> second() const {return b;}
        
        void setFirst (const Point<T> p) { a = p;}
        void setSecond (const Point<T> p) { b = p;}
        
        friend std::ostream& operator<<(std::ostream& os, const PointPair& pp)
        {
            os << "{ " << pp.first() << " " << pp.second() << " }";
            return os;
        }
        
    private:
        Point<T> a, b;
    };
    
    template <typename T>
    struct SortY
    {
        bool operator()(const Point<T>& a, const Point<T>& b) {return a.y < b.y;}
    };
    
    template <typename T>
    struct SortX
    {
        bool operator()(const Point<T>& a, const Point<T>& b) {return a.x < b.x;}
    };
    
    /** Redundant? */
    template <typename T>
    void sortBy (std::vector<Point<T>>& points, bool sortByX = true)
    {
        if (sortByX)
        {
            std::sort (points.begin(), points.end(), [&] (Point<T> p1, Point<T> p2) {return p1.x < p2.x;});
        }
        else
        {
            std::sort (points.begin(), points.end(), [&] (Point<T> p1, Point<T> p2) {return p1.y < p2.y;});
        }
    }
    
    template <typename T>
    std::vector<Point<T>> sortBy (const std::vector<Point<T>>& points, bool sortByX = true)
    {
        std::vector<Point<T>> sortedPoints (points.size());
        std::copy (points.begin(), points.end(), sortedPoints.begin());
        if (sortByX)
        {
            std::sort (points.begin(), points.end(), [&] (Point<T> p1, Point<T> p2) {return p1.x < p2.x;});
        }
        else
        {
            std::sort (points.begin(), points.end(), [&] (Point<T> p1, Point<T> p2) {return p1.y < p2.y;});
        }
        // move ?
        return sortedPoints;
    }
}

#endif /* Point_h */
