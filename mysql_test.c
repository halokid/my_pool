#include<stdio.h>
#include<mysql/mysql.h>
 
int main()
{
/*declare   structures   and   variables   */
MYSQL   mysql;
MYSQL_RES   *result;
MYSQL_ROW   row;
//initialize   MYSQL   structure
mysql_init(&mysql);
//connect   to   database
mysql_real_connect(&mysql,"localhost","root","456123ooxx","mysql",0,NULL,0);

//execute   query

char *query = "select user, password from user";
mysql_query(&mysql, query);
// mysql_query(&mysql,"select user, password from user");
//get   result   set
result=mysql_store_result(&mysql);
//process   result   set
while((row=mysql_fetch_row(result)))
{
   fprintf(stdout,"%s   -   %s\n",row[0],row[1]);
}
//mysql_query(&mysql,"insert into test values(3,'a')");
//clean   up
mysql_free_result(result);
mysql_close(&mysql);
}