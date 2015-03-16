/*
 * module/ngx_http_servats.h
 *
 * This file is part of the HTTP Servats Module.
 *
 * For the full copyright and license information, please view the LICENSE.md
 * file that was distributed with this source code.
 *
 */

#ifndef NGX_HTTP_SERVATS_MODULE_H_
#define NGX_HTTP_SERVATS_MODULE_H_


/**
 * Module version string and logging name
 */
#define  SERVATS_VERSION       	"1.0.0-alpha1"
#define  SERVATS_NAME     		"HTTP Servats Module"
#define  SERVATS_IDENT			"ngx_http_servats"


/**
 * The module initialization and configuration handler functions
 */
static  ngx_int_t  ngx_http_servats_init(ngx_conf_t  *cf);
static  void      *ngx_http_servats_create_loc_conf(ngx_conf_t  *cf);
static  char      *ngx_http_servats_merge_loc_conf(ngx_conf_t  *cf, void  *parent, void  *child);


/**
 * Calculates the length of a NULL-terminated string. It is ugly having to
 * remember to subtract 1 from the size of result.
 */
#define ngx_sizeof_ssz(_s) (sizeof(_s) - 1)


/**
 * Displays our debug log message (no parameters)
 */
#define servats_log_d0(_r, _m) \
		char * _m_p = (char *) malloc(1 + strlen(_m) + strlen(SERVATS_NAME) + strlen(": ")); \
		strcpy(_m_p, SERVATS_NAME); strcat(_m_p, ": "); strcat(_m_p, _m); \
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, _r->connection->log, 0, _m_p)


/**
 * Displays our debug log message (one parameter)
 */
#define servats_log_d1(_r, _m, _p1) \
		char * _m_p = (char *) malloc(1 + strlen(_m) + strlen(SERVATS_NAME) + strlen(": ")); \
		strcpy(_m_p, SERVATS_NAME); strcat(_m_p, ": "); strcat(_m_p, _m); \
        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, _r->connection->log, 0, _m_p, _p1)


/**
 * Displays our debug log message (two parameters)
 */
#define servats_log_d2(_r, _m, _p1, _p2) \
		char * _m_p = (char *) malloc(1 + strlen(_m) + strlen(SERVATS_NAME) + strlen(": ")); \
		strcpy(_m_p, SERVATS_NAME); strcat(_m_p, ": "); strcat(_m_p, _m); \
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, _r->connection->log, 0, _m_p, _p1, _p2)


#endif /* NGX_HTTP_SERVATS_MODULE_H_ */

/* EOF */
