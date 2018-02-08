/**
* seletor.h
*
* Author: Gabriel Lopes <gabrielrrlopes@gmail.com>
*
* Date: Fevereiro 2018
*
**/
typedef struct valores Valor;

MYSQL_RES *seletor(MYSQL *cnx, const char *select);
