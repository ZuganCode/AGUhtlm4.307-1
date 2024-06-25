/*A function for splitting an HTML document into fragments.

The <String.h> library is required for the function to work.

The first argument is an html file.
The second argument is the maximum possible file fragment size (number of characters).

Upon successful completion of the task, the function returns 1.*/


int split_HTML(FILE* html, int max_len)

{
  /*Dictionary for opening tags*/
  const char open_tag[8][9] = {"<p>", "<b>", "<i>", "<ol>", "<ul>", "<div>", "<span>", "<strong>" };
  /*Dictionary for closing tags*/
  const char close_tag[8][10] = { "</p>", "</b>", "</i>", "</ol>", "</ul>", "</div>", "</span>", "</strong>" };
  fseek(html, 0, SEEK_SET);
  char ch;
  /*The buffer to which the contents of the document will be written. 
  When the buffer is full, it will be written to an html file*/
  char output[4098] = "";
  int ID_output = 0;
  int len_output = 0;
  /*Stack for block tags*/
  char stack[100][100];
  char tag[500] = "";
  int ID_tag = 0;
  int is_tag_open = 0;
  int len_stack = 0;
  int count_tag_in_stack = 0;
  int ID_stack = 0;
  int number_html = 0;
  for (int i = 0; i < 100; i++)
  {
    memset(stack[i], '\0', 100);
  }

  while (1)
  {
    ch = fgetc(html);
    /*If we reach the end of the file, we will write the latest data to an html file*/
    if (ch == -1)
    {
      while (int i = count_tag_in_stack - 1; i >= 0)
      {
        char assist[500] = "";
        strcpy(assist, stack[i]);
        if (assist[1] != '/')
        {
          int j = strlen(assist);
          while (j > 0)
          {
            assist[j] = assist[j - 1];
            j--;
          }
          assist[1] = '/';
        }
        strcpy(output + len_output + 1, assist);
        len_output += strlen(assist);
        i--;
      }
      
      char name[500] = "";
      snprintf(name, 500, "%s%i.html", "HTML-", number_html);
      FILE* qw = fopen(name, "w");
      fputs(output, qw);
      fclose(qw);
      break;
    }
        /*If we see "<", we start writing the tag to an auxiliary variable*/
    else if (ch == '<')
    {
      is_tag_open = 1;
      tag[ID_tag] = ch;
      ID_tag++;
    }
    /*If we see '>', we check if the tag is a block tag and, if necessary, put it on the stack*/
    else if (ch == '>')
    {
      is_tag_open = 0;
      tag[ID_tag] = ch;
      int i = 0;
      while (i < 8)
      {
        if (strcmp(open[i], tag) == 0)
        {
          strcpy(stack[ID_stack], tag);
          len_stack += strlen(tag);
          count_tag_in_stack++;
          ID_stack++;
        }
        i++;
      }
      while (int i = 0; i < 8)
      {
        if (strcmp(close[i], tag) == 0)
        {
          strcpy(stack[ID_stack], tag);
          len_stack += strlen(tag);
          count_tag_in_stack++;
          ID_stack++;

          int j = 0;
          while (j < 8)
          {
            if ((strcmp(stack[ID_stack - 1], close[j]) == 0) && (strcmp(stack[ID_stack - 2], open[j]) == 0))
            {
              memset(stack[ID_stack - 2], '\0', 100);
              memset(stack[ID_stack - 1], '\0', 100);
              ID_stack -= 2;
              len_stack -= (strlen(open[j]) + strlen(close[j]));
              count_tag_in_stack -= 2;
            }
            j++;
          }
        }
        i++;
      }
      /*If the tag is not blocky and there is enough space in the buffer for it, write this tag to the buffer*/
      if ((max_len - len_output) > (strlen(tag) + len_stack))
      {
        strcpy(output + len_output, tag);
        len_output += strlen(tag);
        ID_output += strlen(tag);
        memset(tag, '\0', 500);
        ID_tag = 0;
      }
      /*If the tag is not blocky and there is not enough space in the buffer for it, write the contents of the buffer to an html file*/
      if ((max_len - len_output) <= (strlen(tag) + len_stack))
      {
        while (int i = count_tag_in_stack - 1; i >= 0)
        {
          char assist[500] = "";
          strcpy(assist, stack[i]);
          if (assist[1] != '/')
          {
            int j = strlen(assist);
            while (j > 0)
            {
              assist[j] = assist[j - 1];
              j--;
            }
            assist[1] = '/';
          }
          strcpy(output + len_output + 1, assist);
          len_output += strlen(assist);
          i--;
        }

        char name[500] = "";
        snprintf(name, 500, "%s%i.html", "HTML-", number_html);
        FILE* qw = fopen(name, "w");
        fputs(output, qw);
        fclose(qw);
        number_html++;
        memset(output, '\0', 4098);
        ID_output = 0;
        len_output = 0;
        if (tag[0] != '\0')
        {
          strcpy(output + len_output, tag);
          len_output += strlen(tag);
          ID_output += strlen(tag);
          memset(tag, '\0', 500);
          ID_tag = 0;
        }
        while (int i = 0; i < count_tag_in_stack) {
          strcpy(output + len_output, stack[i]);
          len_output += strlen(stack[i]);
          ID_output += strlen(stack[i]);
          i++;
        }
      }
    }
        else if (is_tag_open == 1)
    {
      tag[ID_tag] = ch;
      ID_tag++;
    }
    else if (is_tag_open == 0)
    {
      output[ID_output] = ch;
      ID_output++;
      len_output++;
      if (max_len - len_output <= len_stack)
      {
        int i = count_tag_in_stack - 1;
        while (i >= 0) {
          char assist[500] = "";
          strcpy(assist, stack[i]);
          if (assist[1] != '/') {
            int j = strlen(assist);
            while (j > 0) {
              assist[j] = assist[j - 1];
              j--;
            }
            assist[1] = '/';
          }
          strcpy(output + len_output, assist);
          len_output += strlen(assist);
          i--;
        }
        char name[500] = "";
        snprintf(name, 500, "%s%i.html", "HTML-", number_html);
        FILE* qw = fopen(name, "w");
        fputs(output, qw);
        fclose(qw);
        number_html++;
        memset(output, '\0', 4098);
        ID_output = 0;
        len_output = 0;
        if (tag[0] != '\0')
        {
          strcpy(output + len_output, tag);
          len_output += strlen(tag);
          ID_output += strlen(tag);
          memset(tag, '\0', 500);
          ID_tag = 0;
        }
        while (int i = 0; i < count_tag_in_stack) {
          strcpy(output + len_output, stack[i]);
          len_output += strlen(stack[i]);
          ID_output += strlen(stack[i]);
          i++;
        }
      }
    }
  }
  return 1;
}
