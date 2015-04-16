#include <mysql/mysql.h>

typedef struct _mysql_pool
{
    MYSQL mysql;    //mysql connect handle
    int used;   // 0: not use; 1: used
    char *sql;  //the sql query
} mysql_pool;



