#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 30
#define TYP "VARCHAR(20)"

char *ConnStr(char *buf, size_t bufsize);
char *ConnHtml(char *buf, size_t bufsize, char *baza);
void liczKolumny(FILE *fp);
void insertCsv(char *buff, char **atr, char *nazwa);
void insert(char *tabela);
void createTableCSV(char *buff, char *nazwa);
void importCSV(char *nazwa);
void doSQL(PGconn *conn,char *command);
void makeHTML(int argc,char *arg[]);

//global variables
int ILE_KOLUMN;
char **atrybut;
PGconn *myconnection;

int main(int argc, char *argv[]){
  char plik[30]={'\0'};
  char tabela[30]={'\0'};
  char wybor;
  char strConnect[100];

  //normalne wykonanie programu
  if(argc<3){
    ConnStr(strConnect,sizeof(strConnect));
    //try to connect
    myconnection = PQconnectdb(strConnect);
    // check the status
    if(PQstatus(myconnection) == CONNECTION_OK){
      printf("\nConnection made\n");
        do{
          getchar();
          printf("[1]Wczytaj z pliku csv do bazy\n[2]Dodaj nowy rekord do tabeli\n[3]Koniec\n>>");
          scanf("%c",&wybor);
          // system("clear");
          switch (wybor) {
            case '1':
              printf("Podaj nazwe pliku z rozszerzeniem: ");
              scanf("%s",plik);
              importCSV(plik);
              break;
            case '2':
              printf("Podaj nazwe tabeli: ");
              scanf("%s",tabela);
              insert(tabela);
              break;
            default:
              printf("Do zobaczenia!\n");
          }
        }while(wybor=='1' || wybor=='2');
    } else {
      printf("\nConnection failed: %s\n", PQerrorMessage(myconnection));
    }

  }else { // wykonanie z 3 argumentami
    int saved_stdout,temporary;


    saved_stdout=dup(1);
    dup2(temporary,1);
    ConnHtml(strConnect,sizeof(strConnect),argv[1]);
    myconnection = PQconnectdb(strConnect);

    dup2(saved_stdout,1);
    close(saved_stdout);
    makeHTML(argc,argv);
    dup2(temporary,1);
    if(PQstatus(myconnection) == CONNECTION_OK){
      printf("\nUdalo sie utworzyc strone :)\n");
    } else printf("\nPolaczenie z baza danych nie zostalo nawiazane, strona jest pusta\n");
  }
  //oczyszczenie pamieci
  PQfinish(myconnection);
  return EXIT_SUCCESS;
}

char *ConnStr(char *buf, size_t bufsize){
  int i, ch;
  char baza[50],user[50], pass[50];
  printf("Podaj nazwe bazy: ");
  scanf("%s", baza);
  printf("Podaj nazwe użytkownika: ");
  scanf("%s", user);
  printf("Podaj haslo: ");

  //wylaczanie echa
  system("stty -echo");
  scanf("%s", pass);
  system("stty echo");

  snprintf(buf,bufsize, "host = localhost port=5432 dbname=%s user=%s password=%s",baza, user, pass);
  return buf;
}

char *ConnHtml(char *buf, size_t bufsize,char *baza){
  int i, ch;
  char user[50], pass[50];
  printf("Podaj nazwe użytkownika: ");
  scanf("%s", user);
  printf("Podaj haslo: ");

  //wylaczanie echa
  system("stty -echo");
  scanf("%s", pass);
  system("stty echo");

  snprintf(buf,bufsize, "host = localhost port=5432 dbname=%s user=%s password=%s",baza, user, pass);
  return buf;
}

void liczKolumny(FILE *fp){
  char b[1024];
  fgets(b,1024,fp);

  char *token = strtok(b,";");
  ILE_KOLUMN = 0;
  while( token != NULL){
    ILE_KOLUMN++;
    token = strtok(NULL,";");
  }
  rewind(fp);
}

void insertCsv(char buff[], char **atr, char *nazwa){
  int i,len;
  char insert[1024];
  strcpy(insert,"insert into ");
  strcat(insert,nazwa);
  strcat(insert, " (");
  for(i = 0; i<ILE_KOLUMN;i++){
    strcat(insert,atr[i]);
    if(i != ILE_KOLUMN-1) strcat(insert,",");
  }
  i=0;
  strcat(insert, ") VALUES (");

  char *token;

  for (token = strtok(buff, ";\r\n"); token && i<ILE_KOLUMN ; token = strtok(0, ";\r\n")){
    strcat(insert,"'");
    strcat(insert,token);
    strcat(insert,"'");
    strcat(insert,",");
    len = (int)(strlen(token));
    if(len>20){
      char *alter;
      char liczba[6];
      snprintf(liczba,6,"%d",len); //konwersja liczby do stringa
      strcpy(alter, "ALTER TABLE ");
      strcat(alter, nazwa);
      strcat(alter, " ALTER COLUMN ");
      strcat(alter, atrybut[i]);
      strcat(alter, " TYPE VARCHAR(");
      strcat(alter, liczba);
      strcat(alter, ");");
      doSQL(myconnection,alter);
    }
    i++;
  }


  while(i!=ILE_KOLUMN){
    strcat(insert,"NULL,");
    i++;
  }

  insert[strlen(insert)-1] = 0;
  strcat(insert,");");


  doSQL(myconnection,insert);
}

void insert(char *tabela){
  int ile,i,j,len;
  char nazwa[30],insertStr[2024],value[500],pom[1000];
  strcpy(nazwa,tabela);
  strcat(nazwa,".csv");
  FILE *plik;

  if((plik=fopen(nazwa,"r"))==NULL) {
    printf("Nie moge otworzyc pliku\n");
    exit(1);
  }

  liczKolumny(plik);
  //alokacja pamieci dla tablicy
  atrybut = malloc(ILE_KOLUMN*sizeof(char*));
  for(i=0;i<ILE_KOLUMN;i++) atrybut[i] = malloc((MAX_LEN+1) * sizeof(char));
  i = 0;
  char buff[1024];
  //wczytanie naglowkow tabeli do tabeli atrybut
  fgets(buff,1024,plik);
  char *token = strtok(buff,"; \r\n");
  //wypelnianie tabelii nazwami atrybutow
  while(token != NULL){
    strcpy(atrybut[i], token);
    i++;
    token = strtok(NULL,"; \r\n");
  }

  strcpy(pom,"INSERT INTO ");
  strcat(pom,tabela);
  strcat(pom,"(");
  for(i = 0; i<ILE_KOLUMN;i++){
    strcat(pom,atrybut[i]);
    if(i != ILE_KOLUMN-1) strcat(pom,",");
  }
  strcat(pom, ") VALUES (");


  printf("Ile rekordow chcesz dodac?\n>> ");
  scanf("%d",&ile);


  for(i = 0; i<ile; i++){
    strcpy(insertStr,pom);
    getchar();
    for(j=0;j<ILE_KOLUMN;j++){
      printf("%s: ",atrybut[j]);
      fgets (value, 300, stdin);
      value[strlen(value)-1]='\0'; // zlikwidowanie \n
      // scanf("%[^\n]s",value);
      strcat(insertStr,"'");
      strcat(insertStr,value);
      strcat(insertStr,"'");
      strcat(insertStr,",");
      if(j==ILE_KOLUMN-1){
        insertStr[strlen(insertStr)-1]='\0';
      }

      len = (int)(strlen(value));
      printf("STRLEN:%d\n", len);
      if(len>20){
        char alter[300];
        char liczba[6];
        snprintf(liczba,6,"%d",len); //konwersja liczby do stringa
        strcpy(alter, "ALTER TABLE ");
        strcat(alter, tabela);
        strcat(alter, " ALTER COLUMN ");
        strcat(alter, atrybut[j]);
        strcat(alter, " TYPE VARCHAR(");
        strcat(alter, liczba);
        strcat(alter, ");");
        doSQL(myconnection,alter);
      }
    }
    strcat(insertStr,");");
    doSQL(myconnection,insertStr);
  }


  free(atrybut);
  fclose(plik);
}

void createTableCSV(char *buff,char *nazwa){
  int i = 0;
  char *token = strtok(buff,"; \r\n");
  //wypelnianie tabelii nazwami atrybutow
  while(token != NULL){
    strcpy(atrybut[i], token);
    i++;
    token = strtok(NULL,"; \r\n");
  }

  char create[1024];
  strcpy(create, "CREATE TABLE ");
  strcat(create, nazwa);
  strcat(create, " (");
  strcat(create, atrybut[0]);
  strcat(create, " ");
  strcat(create,TYP);
  strcat(create, " UNIQUE,");
  for(i = 1; i<ILE_KOLUMN;i++){
      strcat(create, atrybut[i]);
      strcat(create, " ");
      strcat(create, TYP);
      strcat(create,",");
  }

  create[strlen(create)-1] = 0;
  strcat(create, ");");
  char drop[100];
  strcpy(drop,"DROP TABLE IF EXISTS ");
  strcat(drop,nazwa);
  strcat(drop,";");

  doSQL(myconnection,drop);
  doSQL(myconnection,create);
}

void importCSV(char *nazwa){
  char tab[30];
  int i;
  FILE *plik;
  if((plik=fopen(nazwa,"r"))==NULL) {
    printf("Nie moge otworzyc pliku\n");
    exit(1);
  }

  liczKolumny(plik);
  //alokacja pamieci dla tablicy
  atrybut = malloc(ILE_KOLUMN*sizeof(char*));
  for(i=0;i<ILE_KOLUMN;i++) atrybut[i] = malloc((MAX_LEN+1) * sizeof(char));
  //bufor na linijki
  char buff[1024];

  strcpy(tab,nazwa);
  tab[strlen(tab)-4]='\0';

  //wczytanie naglowkow tabeli do tabeli atrybut
  fgets(buff,1024,plik);
  createTableCSV(buff,tab);

  //wypelnianie tabeli
  while(fgets(buff,1024,plik) != NULL){
      insertCsv(buff,atrybut,tab);
  }

  free(atrybut);
  fclose(plik);
}

void doSQL(PGconn *conn, char *command){
  PGresult *result;

  printf("%s\n", command);

  result = PQexec(conn, command);
  printf("status is     : %s\n", PQresStatus(PQresultStatus(result)));
  printf("#rows affected: %s\n", PQcmdTuples(result));
  printf("result message: %s\n", PQresultErrorMessage(result));

  switch(PQresultStatus(result)) {
  case PGRES_TUPLES_OK:
    {
      int n = 0, m = 0;
      int nrows   = PQntuples(result);
      int nfields = PQnfields(result);
      printf("number of rows returned   = %d\n", nrows);
      printf("number of fields returned = %d\n", nfields);
      for(m = 0; m < nrows; m++) {
	for(n = 0; n < nfields; n++)
	  printf(" %s = %s", PQfname(result, n),PQgetvalue(result,m,n));
	printf("\n");
      }
    }
  }
  PQclear(result);
}

void makeHTML(int argc,char *arg[]){
  int i;
  PGresult *query;
  char *messg;
  char sql[200];
  printf("<!DOCTYPE html>\n<html>\n<head>\n<style>\ntable {background-color: #E0E0E0;border-collapse: collapse;width: 100%%;}\ntd {border: 2px solid #EBEBEB;padding: 0.5rem;font-family: Lato,sans-serif;font-size: 14px;}\nth {text-align: left;padding: 0.5rem;background-color: darkblue;font-size: 17px;font-style: bold;font-family: Lato,sans-serif;color:#EBEBEB;}\nh2 {font-style:bold;font-family: Lato,sans-serif;color:darkblue;}\n</style>\n<meta charset=\"utf-8\">\n<title>Baza</title>\n</head>\n<body>\n");

  for(i=2;i<argc;i++){
    strcpy(sql,"SELECT * FROM ");
    strcat(sql,arg[i]);strcat(sql,";");

    query=PQexec(myconnection,sql);
    messg = PQresultErrorMessage(query);

    // wystapil plad
    if(strlen(messg)>0) printf("<div>BŁĄD: %s</div>\n",messg);

    if(PQresultStatus(query) == PGRES_TUPLES_OK){
      int n,m;
      int NoRows = PQntuples(query);
      int NoFields = PQnfields(query);
      printf("<h2>%s</h2>\n",arg[i]);
      printf("<table>\n");
      printf("<tr>\n");
      for(n = 0; n < NoFields; n++){
        printf("<th>%s</th>", PQfname(query,n));
      }
      printf("</tr>\n");

      for(m = 0; m < NoRows; m++){
        printf("<tr>\n");
        for(n = 0; n < NoFields; n++){
          printf("<td>%s</td>\n", PQgetvalue(query,m,n));
        }
        printf("</tr>\n");
      }
      printf("</table>\n");
    }
    PQclear(query);
  }//end of for

  printf("</body>\n</html>\n");
}//end of function
