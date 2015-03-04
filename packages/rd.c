/*****************************************************************************
****
****    Redis package for the MudOS driver
****
****    History:
****        2015-3-3:luan
****			add redis support for driver
****
****    Notes:
****
****    TODO:
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
#include "../sprintf.h"

#include <stdio.h>
#include <hiredis.h>

#include "./rd.h"

static rd_list_t rd_list = {0};
/* deal with all mongodb connects use handle */

long create_rd_conn PROT((void)){
	int i;
    /* allocate more slots if we need them */
    if (rd_list.alloc == rd_list.used) {
		i = rd_list.alloc;
		rd_list.alloc += 10;
		if (!rd_list.rds) {
		    rd_list.rds = CALLOCATE(rd_list.alloc, rd_t, TAG_DB, "create_rd_conn");
		} else {
		    rd_list.rds = RESIZE(rd_list.rds, rd_list.alloc, rd_t, TAG_DB, "create_rd_conn");
		}
		while (i < rd_list.alloc) {
		    rd_list.rds[i++].flags = RD_FLAG_EMPTY;
		}
    }

    for (i = 0;  i < rd_list.alloc;  i++) {
		if (rd_list.rds[i].flags & RD_FLAG_EMPTY) {
		    rd_list.rds[i].flags = 0;
		    rd_list.used++;
		    return i + 1;
		}
    }
    fatal("rd_list alloc != used, but no empty slots");
}

rd_t* find_rd_conn P1(long, handle){
	if (handle < 1 || handle > rd_list.alloc || 
		rd_list.rds[handle - 1].flags & RD_FLAG_EMPTY){
		return 0;
	}
    return &(rd_list.rds[handle - 1]);
}

void free_rd_conn P1(rd_t *, rd){
    DEBUG_CHECK(rd->flags & RD_FLAG_EMPTY, "Freeing rd connection that is already freed\n");
    DEBUG_CHECK(!rd_list.used, "Freeing rd connection when dbConnUsed == 0\n");
    rd_list.used--;
    rd->flags |= RD_FLAG_EMPTY;
}



INLINE void reply_to_v P2(redisReply *, r, svalue_t *, v){
	int i;
	array_t *av;
    svalue_t *sv;

	switch ( r->type ) {
		case REDIS_REPLY_STATUS:
	    	v->type = T_STRING;
	    	v->subtype = STRING_MALLOC;
	    	v->u.string = string_copy(r->str,"reply_to_v:REDIS_REPLY_STATUS");
	    	break;
		case REDIS_REPLY_STRING:
	    	v->type = T_STRING;
	    	v->subtype = STRING_MALLOC;
	    	v->u.string = string_copy(r->str,"reply_to_v:REDIS_REPLY_STRING");
	    	break;
		case REDIS_REPLY_INTEGER:
		    v->type = T_NUMBER;
			v->u.number = r->integer;
			break;
		case REDIS_REPLY_ARRAY:
    		av = allocate_array(r->elements);
    		sv = av->item;
    		for(i=0;i<r->elements;i++){
    			reply_to_v(r->element[i],sv);
				sv++;
    		}
    		v->type = T_ARRAY;
    		v->u.arr = av;
    		break;
		case REDIS_REPLY_NIL:
			*v =	const0u;
			break;
	}
}


/* int rd_connect(string host, int port) */

#ifdef F_RD_CONNECT
void f_rd_connect(void){	
	rd_t *rd;
	int status;
	long handle;
	
	handle = create_rd_conn();
	if(!handle){
		pop_n_elems(st_num_arg);
		push_number(0);
		return;
	}
	rd = find_rd_conn(handle);


	switch(st_num_arg){
	case 0:
		rd->conn = redisConnect("127.0.0.1", 6379);
		break;
	case 1:
		rd->conn = redisConnect(sp->u.string, 6379);
		break;
	case 2:
		rd->conn = redisConnect((sp-1)->u.string, sp->u.number);
		break;
	default:
		error("Attempt to connect with error argument\n");
  		return;
	}
	if (rd->conn != NULL && rd->conn->err) {
  		pop_n_elems(st_num_arg);
  		copy_and_push_string(rd->conn->errstr);
		free_rd_conn(rd);
  		return;
	}

  	pop_n_elems(st_num_arg);
  	push_number(handle);
}
#endif

/* mapping rd_run_command(int handle, string command) */

#ifdef F_RD_COMMAND
void f_rd_command(void){
	long handle;
	char *cmd;
	redisReply *reply;

	rd_t *rd;
	svalue_t v;

	handle 	= (sp-(st_num_arg-1))->u.number;
	rd = find_rd_conn(handle);
	if (!rd) {
		error("Attempt to command from an invalid redis handle\n");
    }
    if(st_num_arg == 2){
    	cmd = (sp-(st_num_arg-2))->u.string;
    }else{
    	cmd = string_print_formatted((sp - st_num_arg + 2)->u.string,
                               st_num_arg - 2, sp - st_num_arg + 3);
    }
    reply = redisCommand(rd->conn,cmd);
    if(st_num_arg != 2){
    	free_string(cmd);
    }
    reply_to_v(reply,&v);
    freeReplyObject(reply);
	pop_n_elems(st_num_arg-1);
	*sp = v;
}
#endif

/* int rd_close(int handle) */
#ifdef F_RD_CLOSE
void f_rd_close(void){
	long handle;
	rd_t *rd;
	handle 	= sp->u.number;
	rd = find_rd_conn(handle);
	if (!rd) {
		error("Attempt to close from an invalid redis handle\n");
    }
	redisFree( rd->conn );
	free_rd_conn(rd);
	sp->u.number = 1;
}
#endif