#include <stdio.h>
#include <math.h>
#include <string.h>
// #include <windows.h>
using namespace std;

int main() {
    float THETA = 0.0, PHI = 0.0;
    float R = 3, r = 1;
    float pi = acos(-1.0);

    for(float theta = 0.0; theta < 2 * pi; theta += 0.1) {
        for(float phi = 0.0; phi < 2 * pi; phi += 0.1) {
            float x = (R + r * cos(phi)) * cos(theta);
            float y = (R + r * cos(phi)) * sin(theta);
            float z = r * sin(phi);
            // printf("%.2f, %.2f, %.2f\n", x, y, z);
        }
    } 
}