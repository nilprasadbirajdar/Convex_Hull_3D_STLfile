#pragma once
#include <iostream>
#include <vector>
#include "./Point.h"
using namespace std;
class find_unique
{
public:
    find_unique();
    ~find_unique();
    void unique_points_finder(string filename);
    bool pointExistsInVector(Point point, vector<Point>& vector);
    vector<Point> removeDuplicates(vector<Point>& originalVector);
};