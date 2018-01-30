/**
 * @autor  Gabriel Lopes
 * @email   gabrielrrlopes@gmail.com
 **/
#include <stdio.h>
#include <mysql/mysql.h>
#include "conector.h"
#include "seletor.h"

struct valores{
   MYSQL_RES *resultado;
};

MYSQL_RES *seletor(MYSQL *cnx, const char *select){
  
  if(mysql_query(cnx, select)){
    encerra_com_erro(cnx);
  }
  
  MYSQL_RES *result;
  result = mysql_store_result(cnx);
  if(result == NULL){
    encerra_com_erro(cnx);
  }
  
  return result;
}