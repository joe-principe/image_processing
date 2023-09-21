#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

void write_header(FILE *fp, int x, int y)
{
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", x, y);
    fprintf(fp, "255\n");
}

int
main(void)
{
    int i;
    int x, y, n;
    unsigned char *data;
    unsigned char *gs1, *gs2;
    const char *input_filename = "../images/peppers_raw.ppm";
    const char *output_filename1 = "../images/gs1_c.ppm";
    const char *output_filename2 = "../images/gs2_c.ppm";
    FILE *fp = NULL;

    /* Load the image data into data */
    if ((data = stbi_load(input_filename, &x, &y, &n, 0)) == NULL) {
        fprintf(stderr, "Error: %s\n", stbi_failure_reason());
        exit(EXIT_FAILURE);
    } /* if */

    /* Open the output file for weighted grayscaling */
    if ((fp = fopen(output_filename1, "w")) == NULL) {
        fprintf(stderr, "Error: Could not open %s for writing\n",
                output_filename1);
        exit(EXIT_FAILURE);
    } /* if */

    /* Write the header for the output file */
    write_header(fp, x, y);

    /* Allocate enough memory to hold the grayscaled image */
    if ((gs1 = malloc(sizeof(gs1) * x * y * n)) == NULL) {
        fprintf(stderr, "Error: Could not allocate enough memory for gs1\n");
        exit(EXIT_FAILURE);
    }

    /* Calculate the pixel values of the grayscale image and save to file */
    for (i = 0; i < x * y; i++) {
        gs1[i] = (unsigned char)(0.299 * data[3 * i] + 0.587 * data[3 * i + 1]
                               + 0.114 * data[3 * i + 2]);
        gs1[i + 1] = gs1[i + 2] = gs1[i];
        fprintf(fp, "%c%c%c", gs1[i], gs1[i + 1], gs1[i + 2]);
    }

    /* Open the output file for averaged grayscaling */
    if ((fp = freopen(output_filename2, "w", fp)) == NULL) {
        fprintf(stderr, "Error: Could not open %s for writing\n",
                output_filename2);
        exit(EXIT_FAILURE);
    } /* if */

    /* Write the header for the output file */
    write_header(fp, x, y);

    if ((gs2 = malloc(sizeof(gs2) * x * y * n)) == NULL) {
        fprintf(stderr, "Error: Could not allocate enough memory for gs2\n");
        exit(EXIT_FAILURE);
    } /* if */

    /* Calculate the pixel values of the grayscale image and save to file */
    for (i = 0; i < x * y; i++) {
        gs2[i] = (unsigned char)(data[3 * i] / 3 + data[3 * i + 1] / 3
                 + data[3 * i + 2] / 3);
        gs2[i + 1] = gs2[i + 2] = gs2[i];
        fprintf(fp, "%c%c%c", gs2[i], gs2[i + 1], gs2[i + 2]);
    } /* for */

    free(gs1);
    free(gs2);
    stbi_image_free(data);
    return 0;
}
/* EOF */
