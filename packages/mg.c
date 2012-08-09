/*****************************************************************************
****
****    Mongodb package for the MudOS driver
****
****    History:
****        2012-7-12:luan
****			add mongodb support for driver
****
****    Notes:
****      . add fun transform lpc var to bson and bson to lpc var
****
****    TODO:
****      . insert,remove,update effect row
****	  . add host port user passwd
****	  . io break reconnect
****
******************************************************************************/

#include "../std.h"
#include "../md.h"
#include "../lpc_incl.h"
#include "../mapping.h"
#include "../comm.h"
#include "../file_incl.h"
#include "../file.h"
#include "../object.h"
#include "../eoperators.h"
#include "../backend.h"
#include "../swap.h"
#include "../hash.h"
#include "../master.h"

#include <stdio.h>
#include <mongo.h>

#include "./mg.h"

mongo mg_conn[1];

static mg_list_t mg_list = {0};

INLINE void bson_to_array P2(const char *, data, svalue_t *, v);
INLINE void bson_to_mapping P2(const char *, data, svalue_t *, v);

/*  deal with lpc var and bson exchange */

INLINE void v_to_bson P3(bson *, out, char *, k, svalue_t *, v)
{
    switch(v->type) {
    case T_STRING:
    {
    	if(!strcmp(k,"_id") && strlen(v->u.string) == 24){
    		bson_oid_t oid[1];
    		bson_oid_from_string(oid,v->u.string);
    		bson_append_oid(out,k,oid);
    	}else{
    		bson_append_string(out,k,v->u.string);
    	}
	    return;
	}
    case T_CLASS:
    {
    	bson_append_string(out,k,"CLASS");
	    return;
	}
    case T_NUMBER:
    {
		bson_append_long(out,k,v->u.number);
	    return;
	}
    case T_REAL:
    {
		bson_append_double(out,k,v->u.real);
	    return;
	}
    case T_ARRAY:
	{
		int i;
		int size;
		char buf[20];
	    size = v->u.arr->size;
	    svalue_t *sv = v->u.arr->item;
	    bson_append_start_array(out, k);
	    for(i=0; i<size; i++) {
	    	sprintf(buf,"%d",i);
	    	v_to_bson(out,buf,sv++);
	    }
	    bson_append_finish_array( out );
	    return;
	}
    case T_MAPPING:
	{
	    int j = v->u.map->table_size;
	    mapping_node_t **a = v->u.map->table, *elt;
	    bson_append_start_object(out, k);
	    do {
		for (elt = a[j]; elt; elt = elt = elt->next) {
			if(elt->values->type != T_STRING){
				continue;
			}
			v_to_bson(out,elt->values->u.string,elt->values+1);
		}
	    } while (j--);
	    bson_append_finish_object( out );
	    return;
	}
    }
}

INLINE void map_to_bson P2(svalue_t *, v, bson *, out){
    int j = v->u.map->table_size;
    mapping_node_t **a = v->u.map->table, *elt;
    bson_init( out );
    do {
	for (elt = a[j]; elt; elt = elt = elt->next) {
		if(elt->values->type != T_STRING){
			continue;
		}
		v_to_bson(out,elt->values->u.string,elt->values+1);
	}
    } while (j--);
    bson_finish( out );
    return;
}

INLINE void bson_to_v P2(bson_iterator *, i, svalue_t *, v){
	int temp;   
	const char *cp;
    char oidhex[25];
    bson scope;
    bson_type t;
    bson_timestamp_t ts;
    t = bson_iterator_type( i );
    switch ( t ) {
    case BSON_DOUBLE:
    	v->type = T_REAL;
		v->u.real = bson_iterator_double( i );
        break;
    case BSON_STRING:
    	cp = bson_iterator_string( i );
    	v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
    	v->u.string = string_copy(cp,"bson_to_v:1");
        break;
    case BSON_SYMBOL:
       	v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
    	v->u.string = string_copy("SYMBOL","bson_to_v:2");
        break;
    case BSON_OID:
        bson_oid_to_string( bson_iterator_oid( i ), oidhex );
        v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
    	v->u.string = string_copy(oidhex,"bson_to_v:3");
        break;
    case BSON_BOOL:
    	v->type = T_NUMBER;
		v->u.number = ( long )bson_iterator_bool( i );
        break;
    case BSON_DATE:
        v->type = T_NUMBER;
		v->u.number = ( long )bson_iterator_date( i );
        break;
    case BSON_BINDATA:
    	v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
    	v->u.string = string_copy("BSON_BINDATA","bson_to_v:4");
        break;
    case BSON_UNDEFINED:
    	v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
    	v->u.string = string_copy("BSON_UNDEFINED","bson_to_v:5");
        break;
    case BSON_NULL:
    	v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
        v->u.string = string_copy("BSON_NULL","bson_to_v:6");
        break;
    case BSON_REGEX:
        v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
    	v->u.string = string_copy("BSON_REGEX","bson_to_v:7");
        break;
    case BSON_CODE:
        v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
    	v->u.string = string_copy("BSON_CODE","bson_to_v:8");
        break;
    case BSON_CODEWSCOPE:
        v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
    	v->u.string = string_copy("BSON_CODEWSCOPE","bson_to_v:9");
        break;
    case BSON_INT:
        v->type = T_NUMBER;
		v->u.number = ( long )bson_iterator_int( i );
        break;
    case BSON_LONG:
    	v->type = T_NUMBER;
		v->u.number = ( long )bson_iterator_long( i );
        break;
    case BSON_TIMESTAMP:
        ts = bson_iterator_timestamp( i );
        v->type = T_NUMBER;
		v->u.number = ( long )ts.t;
        break;
    case BSON_OBJECT:
    	bson_to_mapping( bson_iterator_value( i ) , v);
    	break;
    case BSON_ARRAY:
        bson_to_array( bson_iterator_value( i ) , v);
        break;
    default:
    	v->type = T_STRING;
    	v->subtype = STRING_MALLOC;
    	v->u.string = string_copy("UNKOWN_TYPE","bson_to_v:10");
    	break;
    }
}

INLINE int sizeof_bson P1(const char *, data){
	int size = 0;
	bson_iterator i;
	bson_iterator_from_buffer( &i, data );
	while(bson_iterator_next( &i )){
		size++;
	}
	return size;
}

INLINE void bson_to_mapping P2(const char *, data, svalue_t *, v){
	int id;
	int oi;
	int mask;
	int size;
	int count = 0;
	const char *key_c;
	bson_iterator i;
	mapping_t *m;
	svalue_t key, value;
	mapping_node_t **a, *elt, *elt2;

	size = sizeof_bson(data);
	if (!size) {
		v->type = T_MAPPING;
		v->u.map = allocate_mapping(0);
		return;
    }
    m = allocate_mapping(size);
    a = m->table;                    
    mask = m->table_size;
	bson_iterator_from_buffer( &i, data );
	while(bson_iterator_next( &i )){
		key_c = bson_iterator_key( &i );
		key.u.string = make_shared_string(key_c);
    	key.type = T_STRING;
    	key.subtype = STRING_SHARED;
		bson_to_v(&i,&value);
		oi = MAP_POINTER_HASH(key.u.number);
		id = oi & mask;
		if ((elt2 = elt = a[id])) {
		    do {
			/* This should never happen, but don't bail on it */
				if (msameval(&key, elt->values)) {
				    free_svalue(&key, "bson_to_map: duplicate key");
				    free_svalue(elt->values+1, "bson_to_map: replaced value");
				    *(elt->values+1) = value;
				    break;
				}
		    } while ((elt = elt->next));
		    if (elt)
				continue;
		} else if (!(--m->unfilled)) {
		    if (growMap(m)) {
				a = m->table;
				if (oi & ++mask) 
					elt2 = a[id |= mask];
				mask <<= 1;
				mask--;
		    } else {
				add_map_stats(m, count);
				free_mapping(m);
				free_svalue(&key, "bson_to_map: out of memory");
				free_svalue(&value, "bson_to_map: out of memory");
				error("Out of memory\n");
		    }
		}
	
		if (++count > MAX_MAPPING_SIZE) {
		    add_map_stats(m, count -1);
		    free_mapping(m);
		    free_svalue(&key, "bson_to_map: mapping too large");
		    free_svalue(&value, "bson_to_map: mapping too large");
		    mapping_too_large();
		}
		elt = new_map_node();
		*elt->values = key;
		*(elt->values + 1) = value;
		(a[id] = elt)->next = elt2;
	}
	add_map_stats(m, count);
    v->type = T_MAPPING;
    v->u.map = m;
}

INLINE void bson_to_array P2(const char *, data, svalue_t *, v){
	int size;
    array_t *av;
    svalue_t *sv;
    bson_iterator i;

    size = sizeof_bson(data);
    av = allocate_array(size);
    sv = av->item;
    bson_iterator_from_buffer( &i, data );
    while(bson_iterator_next( &i ) && size--){
		bson_to_v(&i,sv);
		sv++;
    }
    v->type = T_ARRAY;
    v->u.arr = av;
    
}

INLINE void bson_to_map P2(const bson *, b, svalue_t *, v){
	bson_to_mapping(b->data, v);
}



/* deal with all mongodb connects use handle */

long create_mg_conn PROT((void)){
	int i;
    /* allocate more slots if we need them */
    if (mg_list.alloc == mg_list.used) {
		i = mg_list.alloc;
		mg_list.alloc += 10;
		if (!mg_list.mgs) {
		    mg_list.mgs = CALLOCATE(mg_list.alloc, mg_t, TAG_DB, "create_mg_conn");
		} else {
		    mg_list.mgs = RESIZE(mg_list.mgs, mg_list.alloc, mg_t, TAG_DB, "create_mg_conn");
		}
		while (i < mg_list.alloc) {
		    mg_list.mgs[i++].flags = MG_FLAG_EMPTY;
		}
    }

    for (i = 0;  i < mg_list.alloc;  i++) {
		if (mg_list.mgs[i].flags & MG_FLAG_EMPTY) {
		    mg_list.mgs[i].flags = 0;
		    mg_list.used++;
		    return i + 1;
		}
    }
    fatal("mg_list alloc != used, but no empty slots");
}

mg_t* find_mg_conn P1(long, handle){
	if (handle < 1 || handle > mg_list.alloc || 
		mg_list.mgs[handle - 1].flags & MG_FLAG_EMPTY){
		return 0;
	}
    return &(mg_list.mgs[handle - 1]);
}

void free_mg_conn P1(mg_t *, mg){
    DEBUG_CHECK(mg->flags & MG_FLAG_EMPTY, "Freeing MG connection that is already freed\n");
    DEBUG_CHECK(!mg_list.used, "Freeing MG connection when dbConnUsed == 0\n");
    mg_list.used--;
    mg->flags |= MG_FLAG_EMPTY;
}



/* int mg_connect(void) */

#ifdef F_MG_CONNECT
void f_mg_connect(void){	
	mg_t *mg;
	int status;
	long handle;
	
	handle = create_mg_conn();
	if(!handle){
		pop_n_elems(st_num_arg);
		push_number(0);
		return;
	}
	mg = find_mg_conn(handle);
  	status = mongo_connect( mg->conn, "127.0.0.1", 27017 );
  	if( status != MONGO_OK ) {
		push_number(-(mg->conn->err));
		free_mg_conn(mg);
  		return;
  	}
  	push_number(handle);
}
#endif

/* mapping mg_find_one(int handle, string ns, mapping query, mapping fields) */

#ifdef F_MG_FIND_ONE
void f_mg_find_one(void){
	long handle;
	char *ns;
	bson query[1];
	bson fields[1];

	int args = 0;
	bson out[1];
	mg_t *mg;
	svalue_t v;

	handle 	= (sp-(st_num_arg-1))->u.number;
	mg = find_mg_conn(handle);
	if (!mg) {
		error("Attempt to find_one from an invalid mongo handle\n");
    }
	bson_empty(query);
	bson_empty(fields);
	switch(st_num_arg){
		case 4: map_to_bson(sp - (args++), fields);
		case 3: map_to_bson(sp - (args++), query);
		case 2: ns 		= (sp - (args++))->u.string;
	}
	if(mongo_find_one(mg->conn,ns,query,fields,out) == MONGO_ERROR ){
		pop_n_elems(st_num_arg);
		push_number(-(mg->conn->err));
		goto free_bson;
	} 
	bson_to_map(out,&v);
	pop_n_elems(st_num_arg-1);
	*sp = v;
	bson_destroy( out );
free_bson:
	switch(st_num_arg){
		case 4: bson_destroy( fields );
		case 3: bson_destroy( query );
	}
}
#endif

/* array mg_find(int handle, string ns, mapping query, mapping fields,
			int limit, int skip, int options) */

#ifdef F_MG_FIND
void f_mg_find(void){
	long handle;
	char *ns;
	bson query[1];
	bson fields[1];
	int limit = 0;
	int skip = 0;
	int options = 0;

	mg_t *mg;
	int num, size;
	int args = 0;

	mongo_cursor* cursor;
	array_t *v;
	svalue_t *sv;

	handle 	= (sp-(st_num_arg-1))->u.number;
	mg = find_mg_conn(handle);
	if (!mg) {
		error("Attempt to find from an invalid mongo handle\n");
    }
	bson_empty(query);
	bson_empty(fields);
	switch(st_num_arg){
		case 7: options = (sp - (args++))->u.number;
		case 6: skip  	= (sp - (args++))->u.number;
		case 5: limit 	= (sp - (args++))->u.number;
		case 4: map_to_bson(sp - (args++), fields);
		case 3: map_to_bson(sp - (args++), query);
		case 2: ns 		= (sp - (args++))->u.string;
	}
	cursor = mongo_find(mg->conn,ns,query,fields,limit,skip,options);
	if(cursor == NULL){
		pop_n_elems(st_num_arg);
		push_number(-(mg->conn->err));
		goto free_bson;
	} 
	num = size = cursor->reply->fields.num;
	if(!size){
		pop_n_elems(st_num_arg);
		push_number(0);
		goto free_mongo;
	}
	v = allocate_empty_array(size);
	sv = v->item;
	while( mongo_cursor_next( cursor ) == MONGO_OK ){
		if(!num--){
			num = cursor->reply->fields.num;
			v = resize_array(v,(size+num));
			sv = v->item+size;
			size += num;
			num--;
		}
		bson_to_map(mongo_cursor_bson( cursor ),sv);
		sv++;
	}
	pop_n_elems(st_num_arg);
	push_array(v);
free_mongo:
	bson_free(cursor);
free_bson:
	switch(st_num_arg){
		case 7: case 6: case 5:
		case 4: bson_destroy( fields );
		case 3: bson_destroy( query );
	}
}
#endif

/* int mg_insert(int handle, string ns, mapping data) */

#ifdef F_MG_INSERT
void f_mg_insert(void){
	long handle;
	char *ns;
	bson data[1];

	mg_t *mg;

	handle 	= (sp-(st_num_arg-1))->u.number;
	mg = find_mg_conn(handle);
	if (!mg) {
		error("Attempt to insert from an invalid mongo handle\n");
    }
    ns = (sp-(st_num_arg-2))->u.string;
    map_to_bson(sp, data);
	if(mongo_insert( mg->conn, ns, data, NULL) == MONGO_ERROR ){
		pop_n_elems(st_num_arg);
		push_number(-(mg->conn->err));
		goto free_bson;
	}
	pop_n_elems(st_num_arg);
	push_number(0);
free_bson:
	bson_destroy( data );
}
#endif

/* int mg_update(int handle, string ns, mapping cond, mapping op, int flags) */

#ifdef F_MG_UPDATE
void f_mg_update(void){
	long handle;
	char *ns;
	bson cond[1];
	bson op[1];
	int flags;

	mg_t *mg;
	int args = 0;

	handle 	= (sp-(st_num_arg-1))->u.number;
	mg = find_mg_conn(handle);
	if (!mg) {
		error("Attempt to update from an invalid mongo handle\n");
    }
    flags = MONGO_UPDATE_MULTI;
	switch(st_num_arg){
		case 5: flags 	= (sp - (args++))->u.number;
		case 4: map_to_bson(sp - (args++), op);
		case 3: map_to_bson(sp - (args++), cond);
		case 2: ns 		= (sp - (args++))->u.string;
	}
	if( mongo_update( mg->conn, ns, cond, op, flags ,NULL) == MONGO_ERROR ) {
		pop_n_elems(st_num_arg);
		push_number(-(mg->conn->err));
		goto free_bson;
    }
    pop_n_elems(st_num_arg);
	push_number(0);
free_bson:
	bson_destroy( cond );
	bson_destroy( op );
}
#endif

/* int mg_remove(int handle, string ns, mapping cond) */

#ifdef F_MG_REMOVE
void f_mg_remove(void){
	long handle;
	char *ns;
	bson cond[1];

	mg_t *mg;

	handle 	= (sp-(st_num_arg-1))->u.number;
	mg = find_mg_conn(handle);
	if (!mg) {
		error("Attempt to remove from an invalid mongo handle\n");
    }
    ns = (sp-(st_num_arg-2))->u.string;
    map_to_bson(sp, cond);

	if(mongo_remove(mg->conn, ns, cond, NULL) == MONGO_ERROR ){
		pop_n_elems(st_num_arg);
		push_number(-(mg->conn->err));
		goto free_bson;
	}
	pop_n_elems(st_num_arg);
	push_number(0);
free_bson:
	bson_destroy( cond );
}
#endif

/* int mg_count(int handle, string ns, mapping cond) */

#ifdef F_MG_COUNT
void f_mg_count(void){
	long handle;
	char *db;
	char *ns;
	bson cond[1];

	mg_t *mg;
	long count;

	handle 	= (sp-(st_num_arg-1))->u.number;
	mg = find_mg_conn(handle);
	if (!mg) {
		error("Attempt to count from an invalid mongo handle\n");
    }
    db = (sp-(st_num_arg-2))->u.string;
    ns = (sp-(st_num_arg-3))->u.string;
    map_to_bson(sp, cond);
	count = mongo_count(mg->conn, db, ns, cond);
	pop_n_elems(st_num_arg);
	push_number(count);
	bson_destroy( cond );
}
#endif

/* int mg_close(int handle) */

#ifdef F_MG_CLOSE
void f_mg_close(void){
	long handle;
	mg_t *mg;
	handle 	= sp->u.number;
	mg = find_mg_conn(handle);
	if (!mg) {
		error("Attempt to close from an invalid mongo handle\n");
    }
	mongo_destroy( mg->conn );
	free_mg_conn(mg);
	sp->u.number = 1;
}
#endif

