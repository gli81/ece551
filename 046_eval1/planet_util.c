#include "planet_util.h"

#include <stdio.h>
#include <string.h>

#include "provided.h"

point_t get_location_at(const planet_t * p, double time) {
  // Step 2: WRITE THIS
  /* ##################################################
   * ### check conditions
   * ##################################################
   */
  if (time < 0) {
    fprintf(stderr, "Invalid input -- time can't be negative\n");
    exit(EXIT_FAILURE);
  }
  if (NULL == p) {
    fprintf(stderr, "Invalid input -- invalid planet info\n");
    exit(EXIT_FAILURE);
  }
  /* ##################################################
   * ### calculate current position
   * ##################################################
   */
   double delta = (2 * M_PI / p->year_len) * time;
   double cur_pos = p->init_pos + delta;
   //cur_pos = cur_pos % 2*M_PI;
   //@@@printf("CUR POS = %.20f\n", cur_pos);
   point_t ans = {.x = p->orbital_radius * cos(cur_pos), .y = p->orbital_radius * sin(cur_pos)};
   return ans;
}

planet_t * find_planet(const planet_list_t * lst, const char * name) {
  //Step 2: WRITE THIS
  if (NULL == lst) {
    fprintf(stderr, "Invalid input -- invalid list\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < lst->num_planets; ++i) {
    if (strcmp(lst->planets[i]->name, name) == 0) {
      return lst->planets[i];
    }
  }
  fprintf(stderr, "No such planet found\n");
  exit(EXIT_FAILURE);
}
