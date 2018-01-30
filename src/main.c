/**
 * @autor  Gabriel Lopes
 * @email   gabrielrrlopes@gmail.com
 **/
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <json-c/json.h>
#include "conector.h"
#include "seletor.h"

int main(int argc, char *argv[]){

  MYSQL *cnx = conectar();
  const char *select = ;
  MYSQL_RES *result = seletor(cnx, select);
  int num_fields = mysql_num_fields(result); 
  MYSQL_ROW row;
  while((row = mysql_fetch_row(result))){
    for(int i = 0; i < num_fields; i++){
      printf("%s ", row[i] ? row[i] : "NULL");
    }
    printf("\n");
  }
  mysql_close(cnx);

  return 0;
}