#include <iostream>
#include "../header/unique_points.h" // Use correct relative or absolute path
#include "../header/Point.h" // Assuming Point class is in the same directory or correct path
#include <fstream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

find_unique::find_unique()
{
}

find_unique::~find_unique()
{
}

bool find_unique::pointExistsInVector(Point point, vector<Point>& vector) {
    for (Point existingPoint : vector) {
        if (existingPoint.x() == point.x() && existingPoint.y() == point.y() && existingPoint.z() == point.z()) {
            return true;
        }
    }
    return false;
}

vector<Point> find_unique::removeDuplicates(vector<Point>& originalVector) {
    vector<Point> uniqueVector;

    for (Point point : originalVector) {
        bool isDuplicate = false;

        for (Point existingPoint : uniqueVector) {
            // Use a tolerance value (e.g., 1e-6) to compare floating-point values
            if (abs(existingPoint.x() - point.x()) < 1e-6 &&
                abs(existingPoint.y() - point.y()) < 1e-6 &&
                abs(existingPoint.z() - point.z()) < 1e-6) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            uniqueVector.push_back(point);
        }
    }

    return uniqueVector;
}


void find_unique::unique_points_finder(string filename)
{
    ofstream write{ "D:\\Projects\\STL_GNUPLOT\\output\\unique_point.txt" };

    ifstream dataFile;
    dataFile.open("../output/unique_points.txt");

    string line;
    vector<Point> points;
    vector<Point> pointx;

    while (getline(dataFile, line)) {
        istringstream iss(line);
        float x, y, z;
        iss >> x >> y >> z;

        Point point(x, y, z);
        points.push_back(point);
    }

    pointx = removeDuplicates(points);

    for (Point p : pointx) {
        std::cout<<p.x()<<endl;
        write << p.x() << " " << p.y() << " " << p.z() << endl;
    }

    write.close();
    dataFile.close();
}