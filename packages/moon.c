#include <time.h>
#include <openssl/md4.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

#include <time.h>
#ifdef LATTICE
#include "/lpc_incl.h"
#else
#include "../lpc_incl.h"
#endif


#ifdef F_MILLI_CLOCK
void
f_milli_clock PROT((void))
{
	struct timeval tv;
	struct timezone tz;
	time_t msec;
	gettimeofday(&tv, &tz);
	msec = (tv.tv_sec-boot_time)*1000+ (tv.tv_usec / 1000);
    push_number(msec);

}
#endif

#ifdef F_LUAN
void
f_luan PROT((void))
{
    debug_message("%s\n",sp->u.string);
    pop_stack();
}
#endif

#ifdef EPOLL
extern void epoll_status(char *msg);
#ifdef F_EPOLL
void
f_epoll PROT((void))
{
	char msg[256] = {0};
	epoll_status(msg);
	share_and_push_string(msg);
}
#endif
#endif
#ifdef F_HASH

char *hexdump(unsigned char *data, size_t len){
	char *buf = NULL;
	int i;
	int length = 0;
	buf = malloc((len * 2) + 1);
	memset(buf, '\0', (len * 2)+1);
	for (i = 0; i < len; i++){
		length += sprintf(buf+length, "%02x", data[i]);
	}
	return buf;
}

void f_hash(void){
	const char *algo;
	const char *data;
	char *res = NULL;
	algo = (sp - 1)->u.string;
	data = sp->u.string;
	/* MD4 Digest */
	if (strcasecmp(algo, (const char *) "md4") == 0){
		unsigned char md[MD4_DIGEST_LENGTH];
		MD4((unsigned char *) data, strlen(data), md);
		res = hexdump(md, MD4_DIGEST_LENGTH);
	}
	/* MD5 Digest */
	else if (strcasecmp(algo, (const char *) "md5") == 0){
		unsigned char md[MD5_DIGEST_LENGTH];
		MD5((unsigned char *) data, strlen(data), md);
		res = hexdump(md, MD5_DIGEST_LENGTH);
	}
	/* RIPEMD160 Digest */
	else if (strcasecmp(algo, (const char *) "ripemd160") == 0){
		unsigned char md[RIPEMD160_DIGEST_LENGTH];
		RIPEMD160((unsigned char *) data, strlen(data), md);
		res = hexdump(md, RIPEMD160_DIGEST_LENGTH);
	}
	/* SHA1 Digest */
	else if (strcasecmp(algo, (const char *) "sha1") == 0){
		unsigned char md[SHA_DIGEST_LENGTH];
		SHA1((unsigned char *) data, strlen(data), md);
		res = hexdump(md, SHA_DIGEST_LENGTH);
	}else{
		pop_stack();
		res = malloc(29 + strlen(algo));
		sprintf(res, "hash() unknown hash type:%s.\n", algo);
		error(res);
	}
	free_string_svalue(sp--);
	free_string_svalue(sp);
	put_constant_string(res);
	if (res)
		free(res);
}
#endif
