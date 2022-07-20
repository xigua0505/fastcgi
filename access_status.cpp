#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <sqlite3.h>
#include "fcgi_stdio.h"

using namespace std;

int sum = 0;
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   char *aa[4] = {"(Page View) ", "(Unique Visitor) ", "(XSWITCH-FREE DOWNLOADS) ", "" };

   fprintf(stderr, "%s: ", (const char*)data);
   printf(
      "\r\n"
      "<h2>%s %s:  %s\n</h2>",
      azColName[3], aa[3], argv[3]);

   for(i=0; i<3; i++){
      printf(
        "\r\n"
        "<div style='color:#FF9966'>%s %s:  %s\n</div>",
        azColName[i], aa[i], argv[i]);
   }

      // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

   return 0;
}

static int callback2(void *data, int argc, char **argv, char **azColName){
   int a;
   fprintf(stderr, "%s: ", (const char*)data);

   stringstream ss;
   ss << argv[0];
   ss >> a;
   sum += a;

   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql[2];
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("data.db", &db);

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */


   while (FCGI_Accept() >= 0) {
      sql[0] = "SELECT PV, UV, DOWNLOADS, DATE from DAILY ORDER BY ID DESC LIMIT 5 OFFSET 0";
      sql[1] = "SELECT DOWNLOADS from DAILY";

      printf("Content-type: text/html\r\n"
        "\r\n"
         "<meta charset='utf-8'/>"
         "<title> FastCGI </title>"
         "<h1> 最近五天访问量 </h1>");

      /* Execute SQL statement */
      rc = sqlite3_exec(db, sql[0], callback, (void*)data, &zErrMsg);
      rc = sqlite3_exec(db, sql[1], callback2, (void*)data, &zErrMsg);
            printf(
         "\r\n"
         "<h1>XSWITCH-FREE DOWNLOADS TOTAL:  %d\n</h1>", sum);
      sum = 0;
      if( rc != SQLITE_OK ){
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
         sqlite3_free(zErrMsg);
      }else{
         fprintf(stdout, "\n");
      }


   }

   sqlite3_close(db);
   return 0;
}