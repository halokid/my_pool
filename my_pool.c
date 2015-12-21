#include <stdio.h>
#include <stdlib.h>
#include "my_pool.h"

// #define MAX 10  //the max mysql pool number


/**
这个连接池方式有两种：
1： 事先建好N个连接，然后有需要就调用连接，用完就改变连接的标志，供下一个使用者使用

2：
规定了最多能建立的连接的数量，然后每一次都是重新连接数据库，但是限制了使用者连接数据库的数量

**/


void get_query(MYSQL mysql, char *query)
// void get_query()
{
    // MYSQL   mysql;
    MYSQL_RES   *result;
    MYSQL_ROW   row;
    //initialize   MYSQL   structure
    mysql_init(&mysql);
    //connect   to   database
    mysql_real_connect(&mysql,"localhost","root","testxx","mysql",0,NULL,0);

    //execute   query
    printf("%s\n", query);

    // mysql_query(&mysql,"select user, password from user");
    mysql_query(&mysql, query);
    
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



int handle_pool(mysql_pool my_pool[10], char *sql, int max)
{
    
    printf("sql is: %s\n", sql);

    int i;
    int k;
    

    if( sql != NULL )
    {
        // sql = argv[1];
        // printf("the sql is: %s\n", sql);
        
        //check the pool is used or not
        for(i=0; i<max; i++)
        {
            //not used
            if( my_pool[i].used == 0)
            {
                k = i;
                break;
            }
        }
        printf("%d  -   %s\n", k, sql);
        // char *sql;
        // sql = "select user, password from user";
        
        // get_query(my_pool[k].mysql, "select user, password from mysql");
        // get_query(my_pool[k].mysql);
        get_query(my_pool[k].mysql, sql);
        // get_query();
    }
    else
    {
        printf("need sql_query\n");
        exit(0);
    }
    // break;
    // printf("++++++++++++++++++++++++++++\n", k, sql);
    // }
    return 0;
}





















