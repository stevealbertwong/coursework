/*
https://www.youtube.com/watch?v=uk0Ytomv0wY&t=260s
sort point(x,y) according to its distance

g++ -std=c++11 lambda_sort.cc -o lambda_sort
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point{
	double x, y;
	Point(){
		x = (rand() % 10000) - 5000;
		y = (rand() % 10000) - 5000;
	}	
};

int main(int argc, char const *argv[])
{
	std::vector<Point> points;
	for (int i = 0; i < 100; ++i)
	{
		points.push_back(Point());
	}

	// sort's 3rd arg expect a bool comparison function
	sort(points.begin(), points.end(), 
		[](Point a, Point b) -> bool{
			return (a.x)*(a.x) + (a.y)*(a.y) < (b.x)*(b.x) + (b.y)*(b.y);}
	);

	// for (Point point : points)
	for (auto&& point : points)
	{
		cout << point.x << " " << point.y << endl;
	}

	return 0;
}