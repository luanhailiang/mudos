#include "spec.h"

int mg_connect(void);
mixed mg_find_one(int,string,mapping|void,mapping|void);
mixed mg_find(int,string,mapping|void,mapping|void,int|void,int|void,int|void);
int mg_insert(int,string,mapping);
int mg_update(int,string,mapping,mapping,int|void);
int mg_remove(int,string,mapping);
int mg_count (int,string,string,mapping);
int mg_close (int);