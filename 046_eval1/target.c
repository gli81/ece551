#include "target.h"
#include <stdio.h>

launch_result_t compute_launch_by_info(const launch_input_t * this_launch,
                                       const planet_list_t * planets) {
  //STEP 3: Write this
  
  // check conditions
  if (this_launch == NULL) {
    fprintf(stderr, "Invalid input -- invalid launch input\n");
    exit(EXIT_FAILURE);
  }
  if (planets == NULL) {
    fprintf(stderr, "Invalid input -- invalid planets input\n");
    exit(EXIT_FAILURE);
  }
  // find two planets' position
  point_t src = get_location_at(find_planet(planets, this_launch->src), this_launch->time);
  point_t dest = get_location_at(find_planet(planets, this_launch->dest), this_launch->time);

  // calculate angle
  double delta_y = dest.y - src.y;
  double delta_x = dest.x - src.x;
  double angle = atan2(delta_y, delta_x);
  if (angle < 0) {
    angle += 2 * M_PI;
  }
  angle = fmod(angle, 2 * M_PI);
  // calculate duration
  if (this_launch->speed == 0) {
    launch_result_t ans = {.theta = 0.0, .duration = INFINITY};
    return ans;
    // fprintf(stderr, "Invalid input -- speed can't be 0\n");
    // exit(EXIT_FAILURE);
  }
  double duration = sqrt((delta_y * delta_y + delta_x * delta_x)) / this_launch->speed;
  // construct answer
  launch_result_t ans = {.theta=angle, .duration=duration};
  return ans;
}

double when_does_planet_return_to(const planet_t * planet,
                                  point_t pos,
                                  double start_time) {
  //STEP 3: Write this
  // check conditions
  if (planet == NULL) {
    fprintf(stderr, "Invalid input -- invalid planet input\n");
    exit(EXIT_FAILURE);
  }
  // get planet pos at start_time
  point_t p_cur = get_location_at(planet, start_time);
  // transform (x, y) to radian
  double p_cur_radian = atan2(p_cur.y, p_cur.x);
  double pos_radian = atan2(pos.y, pos.x);
  // calculate time and return
  double wait_rad = pos_radian - p_cur_radian;
  if (wait_rad < 0) {
    wait_rad += 2 * M_PI;
  }
  return start_time + wait_rad / (2 * M_PI / planet->year_len);
}
