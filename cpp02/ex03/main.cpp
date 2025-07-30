#include "Point.hpp"
#include <iostream>

int main(void) {
    // Test triangle: vertices at (0,0), (4,0), (2,3)
    Point a(0.0f, 0.0f);
    Point b(4.0f, 0.0f);
    Point c(2.0f, 3.0f);
    
    std::cout << "=== BSP (Binary Space Partitioning) Test ===" << std::endl;
    std::cout << "Triangle vertices:" << std::endl;
    std::cout << "A(" << a.getX() << ", " << a.getY() << ")" << std::endl;
    std::cout << "B(" << b.getX() << ", " << b.getY() << ")" << std::endl;
    std::cout << "C(" << c.getX() << ", " << c.getY() << ")" << std::endl;
    std::cout << std::endl;
    
    // Test points inside the triangle
    std::cout << "=== Points Inside Triangle ===" << std::endl;
    Point inside1(2.0f, 1.0f);
    Point inside2(1.5f, 1.5f);
    Point inside3(2.5f, 1.5f);
    
    std::cout << "Point (" << inside1.getX() << ", " << inside1.getY() << "): ";
    std::cout << (bsp(a, b, c, inside1) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    std::cout << "Point (" << inside2.getX() << ", " << inside2.getY() << "): ";
    std::cout << (bsp(a, b, c, inside2) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    std::cout << "Point (" << inside3.getX() << ", " << inside3.getY() << "): ";
    std::cout << (bsp(a, b, c, inside3) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    // Test points outside the triangle
    std::cout << std::endl << "=== Points Outside Triangle ===" << std::endl;
    Point outside1(-1.0f, 0.0f);
    Point outside2(5.0f, 0.0f);
    Point outside3(2.0f, 4.0f);
    Point outside4(0.0f, 2.0f);
    
    std::cout << "Point (" << outside1.getX() << ", " << outside1.getY() << "): ";
    std::cout << (bsp(a, b, c, outside1) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    std::cout << "Point (" << outside2.getX() << ", " << outside2.getY() << "): ";
    std::cout << (bsp(a, b, c, outside2) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    std::cout << "Point (" << outside3.getX() << ", " << outside3.getY() << "): ";
    std::cout << (bsp(a, b, c, outside3) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    std::cout << "Point (" << outside4.getX() << ", " << outside4.getY() << "): ";
    std::cout << (bsp(a, b, c, outside4) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    // Test points on edges (should return false)
    std::cout << std::endl << "=== Points On Edges (should be OUTSIDE) ===" << std::endl;
    Point onEdge1(2.0f, 0.0f);   // On edge AB
    Point onEdge2(1.0f, 1.5f);   // On edge AC
    Point onEdge3(3.0f, 1.5f);   // On edge BC
    
    std::cout << "Point (" << onEdge1.getX() << ", " << onEdge1.getY() << "): ";
    std::cout << (bsp(a, b, c, onEdge1) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    std::cout << "Point (" << onEdge2.getX() << ", " << onEdge2.getY() << "): ";
    std::cout << (bsp(a, b, c, onEdge2) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    std::cout << "Point (" << onEdge3.getX() << ", " << onEdge3.getY() << "): ";
    std::cout << (bsp(a, b, c, onEdge3) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    // Test vertices (should return false)
    std::cout << std::endl << "=== Triangle Vertices (should be OUTSIDE) ===" << std::endl;
    std::cout << "Vertex A(" << a.getX() << ", " << a.getY() << "): ";
    std::cout << (bsp(a, b, c, a) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    std::cout << "Vertex B(" << b.getX() << ", " << b.getY() << "): ";
    std::cout << (bsp(a, b, c, b) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    std::cout << "Vertex C(" << c.getX() << ", " << c.getY() << "): ";
    std::cout << (bsp(a, b, c, c) ? "INSIDE" : "OUTSIDE") << std::endl;
    
    return 0;
}