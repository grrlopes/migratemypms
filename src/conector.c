/**
 * @autor  Gabriel Lopes
 * @email   gabrielrrlopes@gmail.com
 **/
#ifndef _SELETOR_H
#define _SELETOR_H
#include <stdio.h>
#include <mysql/mysql.h>
#include "conector.h"

#define ADDRS "192.168.1.20"
#define USER "root"
#define PASSW "123456"
#define SCHEMA "mypass"

MYSQL *conectar(void){
  MYSQL *cnx = mysql_init(NULL);
  if(mysql_real_connect(cnx, ADDRS, USER, PASSW, SCHEMA, 0, NULL, 0) == NULL){
    encerra_com_erro(cnx);
  }
  if(cnx == NULL){
    fprintf(stderr, "mysql_init() falhou!!!\n");
    exit(1);
  }
  return cnx;
}

void encerra_com_erro(MYSQL *cnx){
  fprintf(stderr, "%s\n", mysql_error(cnx));
  mysql_close(cnx);
  exit(1);
}
#endif /* _SELETOR_H */