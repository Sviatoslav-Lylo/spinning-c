#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>

int main() {
    const char *trident[] = {
    ".......................................",
    ".......................................",
    "...................#...................",
    "..................###..................",
    ".................#####.................",
    ".................#####.................",
    "...#.............#####.............#...",
    "...###...........#####...........###...",
    "...####..........#####..........####...",
    "...#####.........#####.........#####...",
    "...######........#####........######...",
    "...#######.......#####.......#######...",
    "...#######.......#####.......#######...",
    "...###.####......#####......####.###...",
    "...###.####......#####......####.###...",
    "...###..####.....#####.....####..###...",
    "...###..####.....#####.....####..###...",
    "...###...###......###......###...###...",
    "...###...###......###......###...###...",
    "...###...###......###......###...###...",
    "...###...####.....###.....####...###...",
    "...###...####.....###.....####...###...",
    "...###...####.....###.....####...###...",
    "...###...####.....###.....####...###...",
    "...###....###.....###.....###....###...",
    "...###....###....#####....###....###...",
    "...###....###....#####....###....###...",
    "...###....###....#####....###....###...",
    "...###...####....#####....####...###...",
    "...###..#####...#######...#####..###...",
    "...###.######...#######...######.###...",
    "...###.####.....###.###.....####.###...",
    "...#######.....####.####.....#######...",
    "...#######.....###...###.....#######...",
    "...########...####...####...########...",
    "...###.######.###.....###.######.###...",
    "...###..#########.....#########..###...",
    "...###...##########.##########...###...",
    "...###.....#################.....###...",
    "...###......###.#######.###......###...",
    "...###.....####..#####..####.....###...",
    "...###.....####...###...####.....###...",
    "...#################################...",
    "...#################################...",
    "...#################################...",
    "............###...###...###............",
    "............####..###..####............",
    "............####..###..####............",
    ".............####.###.####.............",
    ".............####.###.####.............",
    "..............###########..............",
    "...............#########...............",
    "...............#########...............",
    "................#######................",
    ".................#####.................",
    "..................###..................",
    "...................#...................",
    ".......................................",
    "......................................."
};

    float pi = acos(-1.0);
    const char *brightness = ".,-~:;=!*#$@";

    float cameraDist = 38, scale = 40;
    int width = 80, height = 40;


    int maskHeight = sizeof(trident) / sizeof(trident[0]);
    int maskWidth = strlen(trident[0]);
    int cx = (maskWidth - 1) / 2;
    int cy = (maskHeight - 1) / 2;
    int depth = 6;

    

    float zbuffer[width * height];
    char buffer[width * height];

    printf("\033[?25l"); // Hide the terminal cursor during animation.
    float A = 0.0, B = 0.0; // Rotation angles about the x- and z-axes

    // light direction used for shading the donut.    
    float lx = 0.0f;
    float ly = 0.5f;
    float lz = -1.0;

    // light direction normalized for the dot product.
    float invLen = 1.0f / sqrtf(lx * lx + ly * ly + lz * lz);
    lx *= invLen;
    ly *= invLen;
    lz *= invLen;
    
    while(1) {
        memset(buffer, ' ', sizeof(buffer));

        for (int i = 0; i < width * height; i++) {
            zbuffer[i] = 0;
        }

        for (int y = 0; y < maskHeight; y++) {
            for (int x = 0; x < maskWidth; x++) {
                if (trident[y][x] == '#') {
                    
                    // Center the mask x and y coordinates around the trident's origin.
                    int px = x - cx;
                    int py = cy - y;

                    for(int z = 0; z < depth; z++) {
                        
                        // Compute the surface normal for lighting effects
                        // and check if the point is on the surface of the trident,
                        // otherwise continue.
                        float nx = 0, ny = 0, nz = 0;
                        int is_surface = 0;
                        if (z == 0) { nz = -1; is_surface = 1; } 
                        else if (z == depth - 1) { nz = 1; is_surface = 1; }
                        else if (x == 0 || trident[y][x-1] == '.') { nx = -1; is_surface = 1; }
                        else if (x == maskWidth - 1 || trident[y][x+1] == '.') { nx = 1; is_surface = 1; }
                        else if (y == 0 || trident[y-1][x] == '.') { ny = 1; is_surface = 1; }
                        else if (y == maskHeight - 1 || trident[y+1][x] == '.') { ny = -1; is_surface = 1; }

                        if (!is_surface) continue;

                        // Rotate the surface normal about the x-axis.
                        float nx1 = nx;
                        float ny1 = ny * cos(A) - nz * sin(A);
                        float nz1 = ny * sin(A) + nz * cos(A);

                        // Rotate the surface normal about the z-axis.
                        float nx2 = nx1 * cos(B) - ny1 * sin(B);
                        float ny2 = nx1 * sin(B) + ny1 * cos(B);
                        float nz2 = nz1;

                        // Depth offset centered on the trident's thickness.
                        float pz = z - (depth - 1) / 2.0f;

                        // Rotate about the x-axis.
                        float x1 = px;
                        float y1 = py * cos(A) - pz * sin(A);
                        float z1 = py * sin(A) + pz * cos(A);

                        // Rotate about the z-axis.
                        float x2 = x1 * cos(B) - y1 * sin(B);
                        float y2 = x1 * sin(B) + y1 * cos(B);
                        float z2 = z1;

                        float L = nx2 * lx + ny2 * ly + nz2 * lz;

                        if (L < 0) L = 0;
                        if (L > 1) L = 1;

                        int brightnessIndex = (int)(L * 11);
                        char pixel = brightness[brightnessIndex];

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
                                buffer[idx] = pixel;
                            }
                        }
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
        Sleep(20);
    }
    
    
    return 0;
}