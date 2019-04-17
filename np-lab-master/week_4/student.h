#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
  long reg_no;
  char name[30];
  char subject_code[10];
  char address[512];
  char dept[10];
  int sem;
  char sec[2];
  int marks;
};


void create_student(struct student *s);
void write_student(struct student *s);
int read_student(struct student *s, FILE *in);
void get_student(struct student *s);
void print_student(struct student *s);
struct student *search_reg_no(long reg_no);
struct student *search_subject_code(const char *subject_code);
struct student *search_name(const char *name);
