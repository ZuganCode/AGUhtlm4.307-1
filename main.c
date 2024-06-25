#include <stdio.h>   // Standard input/output library
#include <stdlib.h>  // Standard library for utility functions
#include "split_HTML.h" // Custom header for split_HTML function

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc < 3) {
        // Print usage message and exit if not enough arguments
        printf("Usage: %s --max-len=<max_len> <html_file>\n", argv[0]);
        return -1;
    }

    int max_len;
    // Parse the max length from the first argument
    sscanf(argv[1], "--max-len=%d", &max_len);

    // Validate the max length
    if (max_len < 0 || max_len > 4096) {
        puts("incorrect size");
        return -1;
    }

    // Get the HTML file name from the second argument
    char* htmlName = argv[2];
    printf("%s\n", htmlName);

    // Open the HTML file in read mode
    FILE* html = fopen(htmlName, "r");
    if (html == NULL) {
        perror("Error opening file");
        return -1;
    }

    // Close the file as it's not used after this point
    fclose(html);

    // Call the split_HTML function
    split_HTML(htmlName, max_len);

    return 0;
}
