#include "iter_target.h"

#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * calculate the distance between two points
 * @param src : point_t
 * @param dest : point_t
 * @returns : double
 */
double distance(point_t src, point_t dest) {
    return (dest.y - src.y) * (dest.y - src.y) + (dest.x - src.x) * (dest.x - src.x);
}


launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets) {
  //STEP 4: write this function
  if (NULL == this_launch) {
    fprintf(stderr, "Invalid input -- invalid launch info\n");
    exit(EXIT_FAILURE);
  }
  if (NULL == planets) {
    fprintf(stderr, "Invalid input -- invalid planets list\n");
    exit(EXIT_FAILURE);
  }
  planet_t* dest_planet = find_planet(planets, this_launch->dest);
  point_t src = get_location_at(find_planet(planets, this_launch->src), this_launch->time);
  point_t dest = get_location_at(dest_planet, this_launch->time);
  double best_duration = DBL_MAX;
  launch_result_t ans = {.theta = 0.0, .duration=INFINITY};
  // don't have to worry about max_iter <= 0 :-)
  //@@@printf("this_launch->max_iterations: %ld\n", this_launch->max_iterations);
  if (this_launch->max_iterations <= 0) {
    return ans;
  }
  for (size_t i = 0; i < this_launch->max_iterations; ++i) {
    double angle = atan2(dest.y - src.y, dest.x - src.x);
    if (angle < 0) angle += 2 * M_PI;
    angle = fmod(angle, 2 * M_PI);
    if (angle == 0) angle += 2 * M_PI;
    if (this_launch->speed == 0) {
      return ans;
    }
    double duration = sqrt(distance(src, dest)) / this_launch->speed;
    // check if close enough
    point_t dest_cur = get_location_at(dest_planet, this_launch->time + duration);
    if (sqrt(distance(dest, dest_cur)) <= this_launch->close_enough) {
      ans.theta = angle;
      ans.duration = duration;
      return ans;
    }
    // check if have a better solution
    double wait_time = when_does_planet_return_to(dest_planet, dest, duration + this_launch->time);
    double total_time = duration + wait_time;
    //@@@printf("wait time: %.4f, total_time: %.4f", wait_time, total_time);
    if (total_time < best_duration) {
      // update best solution
      best_duration = total_time;
      ans.theta = angle;
      ans.duration = duration;
    }
    dest.x = dest_cur.x;
    dest.y = dest_cur.y;
  }
  return ans;
}

