#ifndef _colors_table_h
#define _colors_table_h

/*
  Colors:

  Black       0;30     Dark Gray     1;30
  Blue        0;34     Light Blue    1;34
  Green       0;32     Light Green   1;32
  Cyan        0;36     Light Cyan    1;36
  Red         0;31     Light Red     1;31
  Purple      0;35     Light Purple  1;35
  Brown       0;33     Yellow        1;33
  Light Gray  0;37     White         1;37
*/

/*
  struct colt:
  a linked list to hold all the colors
*/
struct colt {
  char *color;
  char *color_value;
  struct colt *next_color;
};


void load_colors(struct colt*);
void add_color(struct colt*, const char*, const char*);
void cleanup_colors_struct(struct colt*);
void print_available_colors(struct colt*);

#endif /*colors_table.h*/
