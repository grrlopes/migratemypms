/**
* main.c
*
* Author: Gabriel Lopes <gabrielrrlopes@gmail.com>
*
* Date: Fevereiro 2018
*
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <json-c/json.h>
#include "conector.h"
#include "seletor.h"

typedef struct st_credent_t{
  const char *login,
  *addrs,
  *senha,
  *schema;
} credent_temp_t;

const struct option opcoes[] = {
  {"help",  no_argument, 0, 'h'},
  {"nome",  required_argument, 0, 'n'},
  {"senha", no_argument, 0, 's'},
  {0, 0,  0,  0},
};

void mostra_ajuda(void);

int main(int argc, char *argv[]){
  char *files = "config/config.json",
  *buffer = NULL,
  *login = NULL;
  int tipo_valor, index = 0, opt;
  struct json_object *json_objeto, *tmp, *aux_json;

  credent_temp_t *temp_crendent = (credent_temp_t*) malloc(sizeof(credent_temp_t));

  if(argc < 2) mostra_ajuda();
  while((opt = getopt_long_only(argc, argv, "", opcoes, &index)) != -1 ){
    switch(opt){
      case 'h':
        mostra_ajuda();
        break;
      case 'n':
        login = optarg;
        printf("%s", login);
        break;
      case 's':
        temp_crendent->senha=\
        getpass("Digite senha: ");
        break;
      default:
        fprintf(stderr, "Opcao invalida ou faltando argumento: %c'\n", optopt) ;
      return -1;
    }
  }

  get_arquivo_ext(files, &buffer);

	json_objeto = json_tokener_parse(buffer);
  printf("json_objeto:\n---\n%s\n---\n",
  json_object_to_json_string_ext(json_objeto, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));

	json_object_object_get_ex(json_objeto, "dados", &aux_json);

	for(int i = 0; i < json_object_array_length(aux_json); i++){
		tmp = json_object_array_get_idx(aux_json, i);
		printf("chave[%d] = %s\n", i, json_object_to_json_string(tmp));
	}

	json_object_object_foreach(json_objeto, key, val){
    tipo_valor = json_object_get_type(val);
    switch(tipo_valor){
      case json_type_string:
        if(strcmp("user", key) == 0){
          temp_crendent->login = json_object_get_string(val);
        }else if(strcmp("ip", key) == 0){
          temp_crendent->addrs = json_object_get_string(val);
        }else if(strcmp("banco", key) == 0){
          temp_crendent->schema = json_object_get_string(val);
        }
        break;
      case json_type_array:
        printf("array\n");
    }
	}

  Credencial *credent = credencial(temp_crendent->login,
    temp_crendent->addrs, temp_crendent->senha, temp_crendent->schema);
  free(temp_crendent);
  MYSQL *cnx = conectar(credent);
  const char *select = "select * from home limit 1";
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

  free(credent);
  free(buffer);
  return 0;
}

void mostra_ajuda(void){
  fprintf(stderr, "\
    [USE] <Opcoes>\n\
    -h, --help          Mostra essa tela e sai.\n\
    -n, --nome=NOME     Seta o seu nome.\n\
    -s, --senha=SENHA   Informe a senha do banco de dados.\n");
  exit(-1) ;
}