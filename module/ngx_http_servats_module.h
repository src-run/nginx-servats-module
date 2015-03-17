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
#define  SERVATS_VERSION       	"1.0.0-beta2"
#define  SERVATS_NAME     		"HTTP Servats Module"
#define  SERVATS_IDENT			"ngx_http_servats"


/**
 * The module initialization and configuration handler functions
 */
static  ngx_int_t  ngx_http_servats_init(ngx_conf_t  *cf);
static  void      *ngx_http_servats_create_loc_conf(ngx_conf_t  *cf);
static  char      *ngx_http_servats_merge_loc_conf(ngx_conf_t  *cf, void  *parent, void  *child);


#endif /* NGX_HTTP_SERVATS_MODULE_H_ */


/* EOF */
