#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    float R = 3, r = 1;
    float pi = acos(-1.0);
    const char *brightness = ".,-~:;=!*#$@";

    float A = 0.0, B = 0.0;
    int width = 80, height = 40;
    float cameraDist = 8, scale = 30;

    float zbuffer[width * height];
    char buffer[width * height];

    printf("\033[?25l"); // Hide the terminal cursor during animation.
    while(1) {
        memset(buffer, ' ', sizeof(buffer));

        for (int i = 0; i < width * height; i++) {
            zbuffer[i] = 0;
        }

        for(float theta = 0.0; theta < 2 * pi; theta += 0.1) {
            for(float phi = 0.0; phi < 2 * pi; phi += 0.1) {

                float x = (R + r * cos(phi)) * cos(theta);
                float y = (R + r * cos(phi)) * sin(theta);
                float z = r * sin(phi);

                // Rotate about the x-axis.
                float x1 = x;
                float y1 = y * cos(A) - z * sin(A);
                float z1 = y * sin(A) + z * cos(A);

                // Rotate about the z-axis.
                float x2 = x1 * cos(B) - y1 * sin(B);
                float y2 = x1 * sin(B) + y1 * cos(B);
                float z2 = z1;

                // Project the rotated point using perspective.
                float D = 1 / (z2 + cameraDist); // Reciprocal depth.
                float xs = width / 2 + scale * D * x2;
                float ys = height / 2 - scale * 0.5 * D * y2;

                int ix = (int)xs;
                int iy = (int)ys;

                if(ix >= 0 && ix < width && iy >= 0 && iy < height) {
                    int idx = ix + width * iy;
                    
                    // Larger reciprocal depth means the sample is closer.
                    if(D > zbuffer[idx]) {
                        zbuffer[idx] = D;
                        buffer[idx] = '*';
                    }
                }

            }
        }

        printf("\033[H"); // Return to the top-left before redrawing.

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                putchar(buffer[y * width + x]);
            }
        
            if (y < height - 1) {
                putchar('\n');
            }
        }

        A += 0.1;
        B += 0.1;
    }
    
    
    return 0;
}