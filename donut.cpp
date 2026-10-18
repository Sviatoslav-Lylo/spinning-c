#include <stdio.h>
#include <math.h>
#include <string>
// #include <windows.h>
using namespace std;

int main() {
    float R = 3, r = 1;
    float pi = acos(-1.0);
    // string brightness = ".,-~:;=!*#$@";

    float A = 0.0, B = 0.0;

    while(1) {
        for(float theta = 0.0; theta < 2 * pi; theta += 0.1) {
            for(float phi = 0.0; phi < 2 * pi; phi += 0.1) {

                float x = (R + r * cos(phi)) * cos(theta);
                float y = (R + r * cos(phi)) * sin(theta);
                float z = r * sin(phi);

                // rotation relative to x axes
                float x1 = x;
                float y1 = y * cos(A) - z * sin(A);
                float z1 = y * sin(A) + z * cos(A);

                // rotation relative to z axes
                float x2 = x1 * cos(B) - y1 * sin(B);
                float y2 = x1 * sin(B) + y1 * cos(B);
                float z2 = z1;
            }
        }

        A += 0.1;
        B += 0.1;
    }
    
    return 0;
}