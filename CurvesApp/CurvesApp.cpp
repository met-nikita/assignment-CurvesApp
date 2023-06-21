#include <cstdlib>
#include <iostream>
#include "curves.h"
#include <vector>
#include <algorithm>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

bool compareCircles(Circle* c1, Circle* c2)
{
    return c1->GetRadius() < c2->GetRadius();
}

int main()
{
    //Populate a container (e.g. vector or list) of objects of these types created in random manner with random parameters.
    std::vector<Curve*> curves;
    for (int i = 0; i < 200; i++)
    {
        int random = std::rand()%10;
        if (random < 4)
        {
            curves.push_back(new Ellipse(std::rand() % 100, std::rand() % 100));
        }
        else if (random < 8)
        {
            curves.push_back(new Circle(std::rand() % 100));
        }
        else
        {
            curves.push_back(new Helix(std::rand() % 100, std::rand() % 10));
        }
    }
    //Print coordinates of points and derivatives of all curves in the container at t=PI/4.
    double t = M_PI/4;
    for (Curve* curve : curves)
    {
        switch (curve->GetCurveType())
        {
        case CT_Ellipse:
            std::cout << "Ellipse\n";
            break;
        case CT_Circle:
            std::cout << "Circle\n";
            break;
        case CT_Helix:
            std::cout << "Helix\n";
            break;
        default:
            std::cout << "Unknown\n";
        }
        Vector3D point = curve->GetPoint(t);
        std::cout << "\tPoint: [" << point._x << ", " << point._y << ", " << point._z << "]\n";
        Vector3D vector = curve->GetVector(t);
        std::cout << "\tVector: [" << vector._x << ", " << vector._y << ", " << vector._z << "]\n";
    }
    //Populate a second container that would contain only circles from the first container. Make sure the second container shares (i.e. not clones) circles of the first one, e.g. via pointers. 
    std::vector<Circle*> circles;
    for (Curve* curve : curves)
    {
        if (curve->GetCurveType() == CT_Circle)
        {
            circles.push_back((Circle*)curve);
        }
    }
    //Sort the second container in the ascending order of circles’ radii. That is, the first element has the smallest radius, the last - the greatest. 
    std::sort(circles.begin(), circles.end(), compareCircles);
    for (Circle* circle : circles)
    {
        std::cout << "Radius:" << circle->GetRadius() <<"\n";
    }
    //Compute the total sum of radii of all curves in the second container. * Implement computation of the total sum of radii using parallel computations (e.g. OpenMP or Intel TBB library).
    double sum = 0;
#pragma omp parallel for reduction (+:sum)
    for (int i = 0; i<circles.size(); i++)
        sum = sum + circles[i]->GetRadius();
    std::cout << "Radii sum: "<< sum << "\n";
    system("pause");
}