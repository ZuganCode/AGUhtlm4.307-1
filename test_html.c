#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../split_html.h" // Assuming split_HTML function is declared in split_html.h

int main() {
    // Run updated tests and provide feedback
    test_split_HTML_large_single_tag();
    test_split_HTML_nested_tags();
    test_split_HTML_empty_file();
    test_split_HTML_plain_text();

    printf("All updated tests passed successfully!\n");

    return 0;
}
