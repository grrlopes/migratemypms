/**
 * @autor  Gabriel Lopes
 * @email   gabrielrrlopes@gmail.com
 **/
#ifndef _SELETOR_H
#define _SELETOR_H
#include <stdio.h>
#include <mysql/mysql.h>
#include "conector.h"

struct credencial{
  char *login,
  *addrs,
  *senha,
  *schema;
};

Credencial *credencial(char *login,
char *addrs, char *senha, char *schema){
  Credencial *ptr = (Credencial*) malloc(sizeof(Credencial));
  if(ptr != NULL){
    ptr->login = login;
    ptr->addrs = addrs;
    ptr->senha = senha;
    ptr->schema = schema;
  }
  return ptr;
}

MYSQL *conectar(Credencial *ptr){
  MYSQL *cnx = mysql_init(NULL);
  if(mysql_real_connect(cnx, ptr->addrs, ptr->login,
  ptr->senha, ptr->schema, 0, NULL, 0) == NULL){
    encerra_com_erro(cnx);
  }
  if(cnx == NULL){
    fprintf(stderr, "mysql_init() falhou!!!\n");
    exit(EXIT_FAILURE);
  }
  return cnx;
}

void encerra_com_erro(MYSQL *cnx){
  fprintf(stderr, "%s\n", mysql_error(cnx));
  mysql_close(cnx);
  exit(EXIT_FAILURE);
}

int get_arquivo_ext(const char *arq, char **outcache){
  FILE *file = NULL;
  long arq_size;
  const int blocksize = 1;
  size_t ler_size;
  char *arqcache;

  file = fopen(arq, "r");
  if(NULL == file){
    printf("%s Erro ao abrir arquivo json.\n", arq);
    exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_END);
  arq_size = ftell(file);
  rewind(file);

  arqcache = (char*) malloc(sizeof(char) * arq_size);
  *outcache = arqcache;
  if(arqcache == NULL){
    fputs ("Sem espaço na memória!", stderr);
    exit(EXIT_FAILURE);
  }

  ler_size = fread(arqcache, blocksize, arq_size, file);
  if(ler_size != arq_size){
    fputs ("Arquvio não pode ser lido!", stderr);
    exit(EXIT_FAILURE);
  }
  fclose(file);
  return 0;
}
#endif /* _SELETOR_H */