# migratemypms

## Descrição

Migratemypms tem como objetivo, facilitar na migração da base, conforme novas atualizações do sistema mypms.

## Desenvolvimento

migratemypms precisa das seguintes dependências:
  * libmysqlclient-dev
  * libmysqlclient20
  * libmysqld-dev
  * libjson-c-dev
  * libjson-c3

Em sistema baseado em debian, o seguinte comando irá
instalar todas as dependências:
```bash
apt-get install libmysqlclient-dev libmysqlclient20 libjson-c3 libjson-c-dev libmysqld-dev
```

## Compilação

Compilação é feito pelo comando
```bash
  make && sudo make install
```