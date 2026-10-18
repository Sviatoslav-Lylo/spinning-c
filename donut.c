#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    float R = 3, r = 1;
    float pi = acos(-1.0);
    // string brightness = ".,-~:;=!*#$@";

    float A = 0.0, B = 0.0;
    int width = 80, height = 24;
    float cameraDist = 8, scale = 30;

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

                // projection coordinates
                float D = 1 / (z2 + cameraDist); // perspective coeficient
                float xs = width / 2 + scale * D * x2;
                float ys = height / 2 - scale * D * y2;

            }
        }

        A += 0.1;
        B += 0.1;
    }
    
    return 0;
}