#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

// there are some errors with these
// #define STBI_MALLOC
// #define STBI_REALLOC
// #define STBI_FREE

#define STBI_FAILURE_USERMSG

#include "stb_image.h"
#include "stb_image_write.h"

#define RED   0
#define GREEN 1
#define BLUE  2


//-----------------------------------
// compilation: 
//      gcc im_read_write.c -lm
// 
//      -lm option is required to link <math.h> object file
// ----------------------------------


//------------------------
// image:
//      cols = x * chanels
//      rows = y
//
// rgb rgb rgb ... rgb rgb
// rgb rgb rgb ... rgb rgb
// ... ... ... ... ... ... 
// rgb rgb rgb ... rgb rgb
// 
//------------------------


int main() {
    printf("All libraries loaded\n");

    int x, y, n;
    const char *img_path = "img/pickachu.jpeg";
    const char *output_name = "img/output.jpg";
    // const char *img_path = "non_existing_img";

    printf("Try to get image info...\n");
    if (stbi_info(img_path, &x, &y, &n) == 0) {
        fprintf(stderr, "Error, while getting image info!\n");

        stbi_failure_reason();

        return 1;
    }

    printf("\nImage read!\n");

    printf("Image width: %d\n", x);
    printf("Image height: %d\n", y);
    printf("Image chanels: %d\n", n);


    unsigned char *data = stbi_load(img_path, &x, &y, &n, 0);


    printf("\nTry to load image...\n");
    if (data == NULL) {
        fprintf(stderr, "Unable to read image: %s\n", img_path);

        stbi_failure_reason();

        return 2;
    }
    printf("Image loaded successful!\n");

    
    // turn off red and blue channels, to leave only green component
    for (int j = 0; j < y; ++j) {
        for (int i = 0; i < x * n; ++i) {
            if (i % n == RED || i % n == BLUE) {
                data[j * (x * n) + i] = 0;
            }
        }
    }


    printf("\nTry to write image...\n");
    // last argument is quality of picture to store (between 0 and 100)
    if (stbi_write_jpg(output_name, x, y, n, data, 80) == 0) {
        fprintf(stderr, "Unable to write output image!\n");

        stbi_failure_reason();

        return 3;
    }
    printf("Image wrote successful!\n");


    printf("\nTry to free image...\n");
    if (data != NULL) {
        stbi_image_free(data);
        printf("Image was freed successful!\n");
    } else {
        fprintf(stderr, "Unable to free image! Image pointer is NULL!\n");
    }


    printf("\nOk\n");

    return 0;
}