#ifndef PACKAGES_MG_H
#define PACKAGES_MG_H

#define MG_FLAG_EMPTY	0x1

typedef struct _mg {
    int flags;
    mongo conn[1];
} mg_t;

typedef struct _mg_list
{
	int alloc;
	int used;
	mg_t *mgs;	
} mg_list_t;


#endif