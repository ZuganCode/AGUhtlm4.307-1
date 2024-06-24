/*A function for splitting an HTML document into fragments.

The <String.h> library is required for the function to work.

The first argument is an html file.
The second argument is the maximum possible file fragment size (number of characters).

Upon successful completion of the task, the function returns 1.*/


int split_HTML(FILE* html, int max_len)