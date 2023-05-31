#include <iostream>
#include <cmath>
#include "R3Graph/R3Graph.h"

using namespace R3Graph;

R3Vector radiusVector(double lat, double lon);
void earthCoords(const R3Vector &v, double &lat, double &len);
constexpr double EARTH_RADIUS = 6378000.0;

int main()
{
    while (true)
    {
        double lat0, lon0;
        double lat1, lon1;
        std::cout << "Enter coordinates of 2 points on the Earth:" << std::endl;
        std::cin >> lat0 >> lon0 >> lat1 >> lon1;
        if (!std::cin.good())
        {
            break;
        }
        R3Vector v0 = radiusVector(lat0, lon0);
        R3Vector v1 = radiusVector(lat1, lon1);
        double alpha = v0.angle(v1);
        double dist = alpha * EARTH_RADIUS;
        std::cout << "Distance = " << dist << std::endl;
    }
    return 0;
}

R3Vector radiusVector(double lat, double lon)
{
    double phi = lon * M_PI / 180.;
    double theta = lat * M_PI / 180.;

    double cosTheta = cos(theta);
    return R3Vector(cos(phi) * cosTheta, sin(phi) * cosTheta, sin(theta));
}
