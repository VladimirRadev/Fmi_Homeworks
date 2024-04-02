#include <iostream>

#include <iostream>
#include <cstdlib>

using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    float x;
    float y;
};

struct Square {
    float top_left_x;
    float top_left_y;
    float size;
};

Square findSmallestSquare(const std::vector<Point>& points) {
    float min_x = points[0].x;
    float max_x = points[0].x;
    float min_y = points[0].y;
    float max_y = points[0].y;

    for (const Point& point : points) {
        min_x = std::min(min_x, point.x);
        max_x = std::max(max_x, point.x);
        min_y = std::min(min_y, point.y);
        max_y = std::max(max_y, point.y);
    }

    float size = std::max(max_x - min_x, max_y - min_y);

    // Adjust the top left corner to ensure sides are parallel to coordinate axes
    if (max_x - min_x > max_y - min_y) {
        min_y = max_y - size;
    } else {
        min_x = max_x - size;
    }

    Square square;
    square.top_left_x = min_x;
    square.top_left_y = min_y;
    square.size = size;

    return square;
}

int main() {
    std::vector<Point> points = {{1.0f, 1.0f}, {3.0f, 0.0f}, {1.0f, -1.0f}, {-1.0f, -0.5f}};
    Square smallest_square = findSmallestSquare(points);

    std::cout << "Top left corner: (" << smallest_square.top_left_x << ", " << smallest_square.top_left_y << ")\n";
    std::cout << "Size of the square: " << smallest_square.size << "\n";

    return 0;
}
// int main()
// {
//     int n;
//     std::cin>>n;
//     float* X = new float[n];
//     float* Y = new float[n];

//     for (size_t i = 0; i < n; i++)
//     {
//         float k,l;
//         std::cin>>k>>l;
//         X[i]=k;
//         Y[i]=l;
//     }
//     square(n,X,Y);
    
//     delete[] X,Y;

// }