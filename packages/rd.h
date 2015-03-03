#ifndef PACKAGES_RD_H
#define PACKAGES_RD_H

#define RD_FLAG_EMPTY	0x1

typedef struct _rd {
    int flags;
    redisContext *conn;
} rd_t;

typedef struct _rd_list
{
	int alloc;
	int used;
	rd_t *rds;	
} rd_list_t;


#endif