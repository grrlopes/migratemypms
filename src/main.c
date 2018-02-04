/**
 * @autor  Gabriel Lopes
 * @email   gabrielrrlopes@gmail.com
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <json-c/json.h>
#include "conector.h"
#include "seletor.h"

typedef struct main_temp{
  const char *login,
  *addrs,
  *senha,
  *schema;
} main_temp_t;

int main(int argc, char *argv[]){
  char *filess = "config/config.json";
  char *bufferr = NULL;
  int tipo_valor;
  struct json_object *json_objeto, *tmp, *aux_json;

  main_temp_t *temp_crendent = (main_temp_t*) malloc(sizeof(main_temp_t));;

  get_arquivo_ext(filess, &bufferr);

	json_objeto = json_tokener_parse(bufferr);
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
        }else{
          temp_crendent->senha = json_object_get_string(val);
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
  return 0;
}