#include "Point.hpp"

// Calculate the area of a triangle using the cross product formula
// Area = 0.5 * |det([[x1, y1, 1], [x2, y2, 1], [x3, y3, 1]])|
// Which simplifies to: 0.5 * |(x1(y2-y3) + x2(y3-y1) + x3(y1-y2))|
static Fixed triangleArea(Point const a, Point const b, Point const c) {
    Fixed area = (a.getX() * (b.getY() - c.getY()) +
                  b.getX() * (c.getY() - a.getY()) +
                  c.getX() * (a.getY() - b.getY()));
    
    return Fixed::abs(area) / Fixed(2);
}

// Binary Space Partitioning (BSP) algorithm
// A point is inside a triangle if the sum of areas of three sub-triangles
// formed by the point and each edge of the original triangle equals
// the area of the original triangle
bool bsp(Point const a, Point const b, Point const c, Point const point) {
    // Calculate the area of the original triangle
    Fixed originalArea = triangleArea(a, b, c);
    
    // If the original triangle has zero area, it's degenerate
    if (originalArea == Fixed(0)) {
        return false;
    }
    
    // Calculate areas of sub-triangles
    Fixed area1 = triangleArea(point, b, c);  // Triangle formed by point, b, c
    Fixed area2 = triangleArea(a, point, c);  // Triangle formed by a, point, c
    Fixed area3 = triangleArea(a, b, point);  // Triangle formed by a, b, point
    
    // Sum of sub-triangle areas
    Fixed sumAreas = area1 + area2 + area3;
    
    // Check if any sub-triangle has zero area (point is on an edge)
    if (area1 == Fixed(0) || area2 == Fixed(0) || area3 == Fixed(0)) {
        return false;  // Point is on the edge or vertex
    }
    
    // Point is inside if sum of sub-areas equals original area
    return (sumAreas == originalArea);
}