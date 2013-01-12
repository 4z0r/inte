#include "colors_table.H"
#include "colors_debug.H"
#include <stdlib.h>

void load_colors(struct colt *c)
{

  add_color(c, "black", "0;30m");
  add_color(c, "blue", "0;34m");
  add_color(c, "green", "0;32m");
  add_color(c, "cyan", "0;36m");
  add_color(c, "red", "0;31m");
  add_color(c, "purple", "0;35m");
  add_color(c, "brown", "0;33m");
  add_color(c, "lightgray", "0;37m");  

  add_color(c,  "darkgray", "1;30m");
  add_color(c, "lightblue", "1;34m");
  add_color(c, "lightgreen", "1;32m");
  add_color(c, "lightcyan", "1;36m");
  add_color(c, "lightred", "1;31m");
  add_color(c, "lightpurple", "1;35m");
  add_color(c, "yellow", "1;33m");
  add_color(c, "white", "1;37m");  

}

void add_color(struct colt *l, const char *c, const char *cv)
{
  if(l->color && l->next_color) add_color(l->next_color, c, cv);

  if(l->color && !l->next_color)
    {
        l->next_color =(struct colt*)malloc(sizeof(struct colt));
	l->next_color->color = NULL;
	l->next_color->color_value = NULL;
	l->next_color->next_color = NULL;

	add_color(l->next_color, c, cv);
    }

  if(!l->color)
    {
      l->color = strdup(c);
      l->color_value = strdup(cv);
      l->next_color = NULL;
    }
}

void cleanup_colors_struct(struct colt *l)
{
  if(l->next_color != NULL) 
    {
      cleanup_colors_struct(l->next_color);
      free(l->next_color);
    }

  free(l->color);
  free(l->color_value);
}

void print_available_colors(struct colt *l)
{
  if(l->color)
    {
      printf(" + %s\t\t%s\n", l->color, l->color_value);
    }

  if(l->next_color)
    print_available_colors(l->next_color);
}
