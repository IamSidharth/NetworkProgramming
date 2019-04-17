#include "helpers.h"

char *decrypt(const char *str, int key) {
  int str_len = strlen(str);
  char *plain_text = (char *)malloc(str_len);

  int i;
  for(i = 0; i < str_len; i++) 
    plain_text[i] = ((tolower(str[i]) - 97) - key) % 26 + 97;

  return plain_text;
}

char *encrypt(const char *str, int key) {
  int str_len = strlen(str);
  char *cipher_text = (char *)malloc(str_len);

  int i;
  for(i = 0; i < str_len; i++) 
    cipher_text[i] = ((tolower(str[i]) - 97) + key) % 26 + 97;

  return cipher_text;
}

int get_balance(const char *uname, const char *password) {
  FILE *f = fopen("records.txt", "r");
  
  if(f == NULL) {
    exit(EXIT_FAILURE);
  }
  
  char line_buff[512], rec_uname[50], rec_password[50];
  int balance;

  while(fgets(line_buff, sizeof(line_buff), f) != NULL) {

    sscanf(line_buff, "%[^,],%[^,],%d\n", rec_uname, rec_password, &balance);

    if(strcmp(uname, rec_uname) == 0 && strcmp(password, rec_password) == 0) {
      fclose(f);
      return balance;
    }
  }

  fclose(f);
  return 0;
}

int check_user(const char *uname, const char *password) {
  FILE *f = fopen("records.txt", "r");
  
  if(f == NULL) {
    exit(EXIT_FAILURE);
  }
  
  char line_buff[512], rec_uname[50], rec_password[50];
  int balance;

  while(fgets(line_buff, sizeof(line_buff), f) != NULL) {

    sscanf(line_buff, "%[^,],%[^,],%d", rec_uname, rec_password, &balance);

    if(strcmp(uname, rec_uname) == 0 && strcmp(password, rec_password) == 0) { //user found
      fclose(f);
      return 1;
    }
    if(strcmp(uname, rec_uname) == 0 && strcmp(password, rec_password) != 0) { //incorrect password
      fclose(f);
      return -1;
    }
  }

  fclose(f);
  return -2; //user not found

}

void update_balance(const char *uname, const char *password, int amount) {
  FILE *f = fopen("records.txt", "r");
  FILE *f_temp = fopen("temp_records.txt", "w");

  if(f == NULL || f_temp == NULL) {
    exit(EXIT_FAILURE);
  }

  char line_buff[512], rec_uname[50], rec_password[50];
  int balance;

  while(fgets(line_buff, sizeof(line_buff), f) != NULL) {

    sscanf(line_buff, "%[^,],%[^,],%d\n", rec_uname, rec_password, &balance);

    if(strcmp(uname, rec_uname) == 0 && strcmp(password, rec_password) == 0) {
      balance = balance + amount;
      
      memset(line_buff, 0, sizeof(line_buff));
      sprintf(line_buff, "%s,%s,%d\n", uname, password, balance);

      fputs(line_buff, f_temp);
    }
    else {
      fputs(line_buff, f_temp);
    }
  }

  fclose(f);
  fclose(f_temp);

  remove("records.txt");
  rename("temp_records.txt", "records.txt");
}
