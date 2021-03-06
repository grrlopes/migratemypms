/**
* conector.h
*
* Author: Gabriel Lopes <gabrielrrlopes@gmail.com>
*
* Date: Fevereiro 2018
*
**/
typedef struct credencial Credencial;

Credencial *credencial(const char *login, const char *addrs, const char *senha, const char *schema);

MYSQL *conectar(Credencial *ptr);

int get_arquivo_ext(const char *arquivo, char **outcache);

void encerra_com_erro(MYSQL *cnx);