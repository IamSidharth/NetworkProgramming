#include "student.h"

int main() {
  struct student *s = NULL, *s1 = NULL;
  s = (struct student *)malloc(sizeof(struct student));
  s1 = (struct student *)malloc(sizeof(struct student));
  create_student(s);
  create_student(s1);
  get_student(s);
  write_student(s);

  return 0;
}
