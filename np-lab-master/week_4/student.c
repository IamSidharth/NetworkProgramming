#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

void create_student(struct student *s) {
  s->reg_no = 0;
  strcpy(s->name, "");
  strcpy(s->subject_code, "");
  strcpy(s->address, "");
  strcpy(s->dept, "");
  s->sem = 0;
  strcpy(s->sec, "");
  s->marks = 0;
}

void write_student(struct student *s) {
  FILE *out = fopen("student.dat", "ab");
  int w = fwrite(s, sizeof(*s), 1, out);

  if(w < 1) {
    printf("Didn't write to file\n");
    exit(1);
  }

  fclose(out);
}

int read_student(struct student *s, FILE *in) {
  size_t r = fread(s, sizeof(*s), 1, in);

  if(r < 1) {
    printf("Didn't read from file\n");
    exit(1);
  }

  return r;
}

void get_student(struct student *s){
  printf("Enter student details(reg_no, name, subject code, address, dept, semester, section, marks):\n ");
  scanf("%ld %s %s %s %s %d %s %d", &(s->reg_no), s->name, s->subject_code, s->address, s->dept, &(s->sem), s->sec, &(s->marks));
}

void print_student(struct student *s) {
  printf("Reg No: %ld Name: %s Subject Code: %s\n", s->reg_no, s->name, s->subject_code);
}

struct student *search_reg_no(long reg_no) {
  FILE *in = fopen("student.dat", "rb");
  struct student *s = (struct student *)malloc(sizeof(struct student));
  create_student(s);
  while(read_student(s, in) != EOF) {
    if(s->reg_no == reg_no) {
      fclose(in);
      return s;
    }
  }

  fclose(in);
  return NULL;
}

struct student *search_subject_code(const char *subject_code) {
  FILE *in = fopen("student.dat", "rb");
  struct student *s = (struct student *)malloc(sizeof(struct student));
  create_student(s);
  while(read_student(s, in) != EOF) {
    if(strcmp(s->subject_code, subject_code) == 0) {
      fclose(in);
      return s;
    }
  }

  fclose(in);
  return NULL;
}

struct student *search_name(const char *name) {
  FILE *in = fopen("student.dat", "rb");
  struct student *s = (struct student *)malloc(sizeof(struct student));
  create_student(s);
  while(read_student(s, in) != EOF) {
    if(strcmp(s->name, name) == 0) {
      fclose(in);
      return s;
    }
  }

  fclose(in);
  return NULL;
}
