#include <stdio.h>
#include "myinput.h"
#include <ctype.h>

// will use strchr instead
//char* readUntilColumn(char* start) {
//  char* ans = start;
//  while (*ans != '\0' && *ans != '\n') {
//    if (*ans == ':') {
//      return ans;
//    }
//    ans++;
//  }
//  return NULL;
//}

/* convert string to double
 * @param str : char*
 * @param len : size_t
 * @returns : double
 */
double strToPosDouble(char* str, size_t len) {
  // return 0.0 if empty string
  if (len == 0) {
    return 0.0;
  }
  if (len == 1 && *(str) == '.') {
    return -1.0;
  }
  unsigned long int_part = 0;
  size_t i = 0;
  if (*str == '+') {
    i++;
  } else if (*str == ' ') {
    while (i < len && *(str+i) == ' ') {
      i++;
    }
  }
  while (i < len) {
    char cur = *(str + i);
    if (isdigit(cur)) {
      int_part *= 10;
      int_part += cur - '0';
      i++;
    } else if (cur == '.') {
      i++;
      break;
    } else {
      return -1.0;
    }
  }
  // ??? is 12. valid ??? yes it is
  double float_part = 0.0;
  unsigned ct = 1;
  while (i < len) {
    char cur = *(str + i);
    if (isdigit(cur)) {
      float_part *= 10;
      float_part += cur - '0';
      ct *= 10;
      i++;
    } else {
      return -1.0;
    }
  }
  float_part /= ct;
  float_part += int_part;
  return float_part;
}

void parse_planet_info(planet_t * planet, char * line) {
  //STEP 1: Write this
  // ??? is line guarenteed to be \0 terminated ???
  if (NULL == line) {
    fprintf(stderr, "Invalid input\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  /* ##################################################
   * ### read until first ':'
   * ##################################################
   */
  char* first_end = strchr(line, ':');
  //@@@printf("after first ':' '%s'\n", first_end+1);
  if (first_end == NULL) {
    fprintf(stderr, "Invalid input -- no ':' found\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  size_t name_len = first_end - line;
  if (name_len > 31) {
    // name too long
    fprintf(stderr, "Invalid input -- name exceeds 31 characters\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  //printf("%ld\n", name_len);
  /* ??? can name be 0 length ??? README didn't specify
   *pregrader and Drew says yes it can be, FINE 
   */
  //if (name_len == 0) {
  //  // name too short
  //  fprintf(stderr, "Invalid input -- no name specified\n\t\t===\n%s\n\t\t===\n", line);
  //  exit(EXIT_FAILURE);
  //}
  // valid input, set planet->name
  strncpy(planet->name, line, name_len);
  // put \0 at the end
  planet->name[name_len] = '\0';
  //for (size_t i = 0; i < 32; ++i) {
  //  if (planet->name[i] == '\0') printf("\\0\t");
  //  else printf("%c\t", planet->name[i]);
  //  if (i % 6 == 5 || i == 31) {
  //    printf("\n");
  //  }
  //}
  /* ##################################################
   * ### read until second ':'
   * ##################################################
   */
  char* sec_end = strchr(first_end+1, ':');
  if (NULL == sec_end) {
    fprintf(stderr, "Invalid input -- only one ':' found\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  //@@@printf("after second ':' '%s'\n", sec_end+1);
  size_t radius_len = sec_end - first_end - 1;
  // for (size_t i = 0; i < radius_len; ++i) {
  //   printf("%c", *(first_end + 1 + i));
  //   if (i == radius_len - 1) printf("\n");
  // }
  if (radius_len == 0) {
    // radius too short
    fprintf(stderr, "Invalid input -- no radius specified\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  double orbital_rad = strToPosDouble(first_end + 1, radius_len);
  if (orbital_rad == -1.0) {
    // invalid double
    fprintf(stderr, "Invalid input -- invalid double\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  // valid orbital_radius
  //printf("%.f\n", orbital_rad);
  planet->orbital_radius = orbital_rad;
  /* ##################################################
   * ### read until third ':'
   * ##################################################
   */
  first_end = strchr(sec_end+1, ':');
  if (NULL == first_end) {
    fprintf(stderr, "Invalid input -- only two ':' found\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  //@@@printf("after third ':' '%s'\n", first_end+1);
  size_t period_len = first_end - sec_end - 1;
  if (period_len == 0) {
    // period too short
    fprintf(stderr, "Invalid input -- no period specified\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  double period = strToPosDouble(sec_end + 1, period_len);
  if (period == -1.0) {
    fprintf(stderr, "Invalid input -- invalid double\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  // valid period
  planet->year_len = period;

  /* ##################################################
   * ### read until end
   * ##################################################
   */
  char* cur = first_end + 1;
  //@@@printf("cur = '%s'\n", cur);
  size_t init_pos_len = 0;
  // ??? Is .05 valid input ??? it is.
  while (*cur != '\0') {
    if (isdigit(*cur) || *cur == '.') {
      init_pos_len++;
    } else if (*cur == ':') {
      fprintf(stderr, "Invalid input -- too many fields\n\t\t===\n%s\n\t\t===\n", line);
      exit(EXIT_FAILURE);
    } else if (*cur == '\n') {
      if (*(cur+1) == '\0') {
        cur++;
        continue;
      } else {
        fprintf(stderr, "Invalid input -- too many fields\n\t\t===\n%s\n\t\t===\n", line);
        exit(EXIT_FAILURE);
      }
    } else {
      fprintf(stderr, "Invalid input -- invalid double\n\t\t===\n%s\n\t\t===\n", line);
      exit(EXIT_FAILURE);
    }
    cur++;
  }
  // pregrader says it can be empty
  // assume 0.0
  //if (init_pos_len == 0) {
  //  fprintf(stderr, "Invalid input -- no initial position specified\n\t\t===\n%s\n\t\t===\n", line);
  //  exit(EXIT_FAILURE);
  //}
  double init_pos = strToPosDouble(first_end+1, init_pos_len);
  if (init_pos == -1.0) {
    fprintf(stderr, "Invalid input -- invalid double\n\t\t===\n%s\n\t\t===\n", line);
    exit(EXIT_FAILURE);
  }
  planet->init_pos = init_pos * M_PI / 180.0; // in radians
  //@@@printf("----------Completed processing %s----------\n", planet->name);
}

// int main() {
//   printf("%.20f\n", strToPosDouble("12.3", 4));
//   printf("%.20f\n", strToPosDouble("-12.3", 5));
//   printf("%.20f\n", strToPosDouble("12.3.", 5));
//   printf("%.20f\n", strToPosDouble("12.38923942", 11));
//   printf("%.20f\n", strToPosDouble("12.38abc942", 11));
//   printf("%.20f\n", strToPosDouble("12abc.38942", 11));
//   return EXIT_SUCCESS;
// }

