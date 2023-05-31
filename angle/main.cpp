#include <iostream>
#include <cmath>
#include "R3Graph/R3Graph.h"

using namespace R3Graph;
constexpr double EARTH_RADIUS = 6378000.0;
R3Vector radiusVector(double lat, double lon);

void coordsInMap(double mlat, double mlon, R3Vector &ex, R3Vector &ey);
void mapCoords(double mlat, double mlon, double lat, double lon, double &x, double &y);
void earthCoords(const R3Vector &r, double &lat, double &lon);

bool intersectPlaneAndLineMy(const R3Point &p0, const R3Vector &n, const R3Point &p1, const R3Vector &v, R3Point &p);

int main()
{
    double lat, lon, mlat, mlon;
    double x, y;

    while (true)
    {
        std::cout << "Enter latitude and longitude of point on Earth" << std::endl;
        std::cin >> lat >> lon;
        std::cout << "Enter latitude and longitude of map center" << std::endl;
        std::cin >> mlat >> mlon;
        mapCoords(mlat, mlon, lat, lon, x, y);
        std::cout << "x= " << x << " y= " << y << std::endl;
    }
    /*
    lat = 55.727852;
    lon = 37.513595;
    mlat = 55.721008;
    mlon = 37.520387;
    mapCoords(mlat, mlon, lat, lon, x, y);
    std::cout << "x= " << x << " y= " << y << std::endl;
    */
}

R3Vector radiusVector(double lat, double lon)
{
    double phi = lon * M_PI / 180;
    double theta = lat * M_PI / 180;
    double cosTheta = cos(theta);
    return R3Vector(cosTheta * cos(phi), cosTheta * sin(phi), sin(theta));
}
// find bazis in middle of the map
void coordsInMap(double mlat, double mlon, R3Vector &ex, R3Vector &ey)
{
    R3Vector north(0., 0., 1.);
    R3Vector n = radiusVector(mlat, mlon);
    ex = north.vectorProduct(n);
    ex.normalize();
    ey = n.vectorProduct(ex);
}
// find coords on the map
void mapCoords(double mlat, double mlon, double lat, double lon, double &x, double &y)
{
    R3Vector n = radiusVector(mlat, mlon);
    R3Vector ex, ey;
    coordsInMap(mlat, mlon, ex, ey);
    R3Point origin(0., 0., 0.);
    R3Point mapCenter = origin + n * EARTH_RADIUS;
    R3Vector v = radiusVector(lat, lon);
    R3Point p;
    intersectPlaneAndLineMy(mapCenter, n, origin, v, p);
    R3Vector w = p - mapCenter;
    x = w * ex;
    y = w * ey;
}

void earthCoords(const R3Vector &r, double &lat, double &lon)
{
    double phi = atan2(r.y, r.x);
    double theta = M_PI / 2. - r.angle(R3Vector(0., 0., 1.));
    lat = theta * 180. / M_PI;
    lon = phi * 180. / M_PI;
}
bool intersectPlaneAndLineMy(const R3Point &p0, const R3Vector &n, const R3Point &p1, const R3Vector &v, R3Point &p)
{
    double s = n.scalarProduct(v);
    if (fabs(s) <= R3_EPSILON)
        return false;
    // p = p1 + v*t;
    // (p - p0, n) = 0
    // (p1 + v*t - p0, n) = 0
    // (p0 - p1, n) = (v, n)*t
    // t = (p0 - p1, n) / (v, n)
    double t = (p0 - p1).scalarProduct(n) / s;
    p = p1 + v * t;
    return true;
}