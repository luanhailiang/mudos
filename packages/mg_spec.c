#include "spec.h"

mixed mg_connect(string|void,int|void,string|void,string|void,string|void);
mixed mg_run_command(int,string,mapping);
mixed mg_aggregate(int,string,string,mapping*);
mixed mg_find_one(int,string,mapping|void,mapping|void);
mixed mg_find(int,string,mapping|void,mapping|void,int|void,int|void,int|void);
mixed mg_insert(int,string,mapping);
mixed mg_update(int,string,mapping,mapping,int|void);
mixed mg_remove(int,string,mapping);
mixed mg_count (int,string,string,mapping|void);
mixed mg_reconnect (int);
mixed mg_check_connection (int);
mixed mg_close (int);

string mg_get_oid(void);
mixed buf_bson_map(buffer);
mixed map_bson_buf(mapping);
mixed bson_buf_find(buffer,string);
mixed cmd_map_bson_buf(string,mapping);
