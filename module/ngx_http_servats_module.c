/*
 * module/ngx_http_servats.c
 *
 * This file is part of the Nginx Scribe Server Status Module.
 *
 * For the full copyright and license information, please view the LICENSE.md
 * file that was distributed with this source code.
 *
 */

#include <nginx.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_log.h>

#include <stddef.h>
#include <ctype.h>
#include <assert.h>

#include "ngx_http_servats_module.h"
#include "template/ngx_http_servats_consts.h"
#include "template/ngx_http_servats_html_tpls.h"


/**
 * Include external Nginx variable for use in worker calculations
 */
extern ngx_uint_t ngx_num_workers;


/**
 * Define our configuration structure for the module.
 */
typedef struct {
    ngx_flag_t  enabled;                        /* Module is enabled/disabled (disabled by default) */
    ngx_flag_t  theme_both;                     /* Should them internal theme be enabled *plus* the user theme? */
    ngx_str_t   theme_user_css;                 /* Optional custom theme css (empty by default) */
    ngx_str_t   theme_user_jsi;                 /* Optional custom theme javascript library include (empty by default) */
    ngx_str_t   theme_user_jse;                 /* Optional custom theme javascript executing include (empty by default) */
} ngx_http_servats_loc_conf_t;


/**
 * Define the module configuration, which simply supports being enabled, as well
 * as explicitly disabled.
 */
static  ngx_command_t ngx_http_servats_commands[] =
{
    {
        ngx_string("servats"),
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
        ngx_conf_set_flag_slot,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_servats_loc_conf_t, enabled),
        NULL
    },
    {
        ngx_string("servats_theme_both"),
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
        ngx_conf_set_flag_slot,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_servats_loc_conf_t, theme_both),
        NULL
    },
    {
        ngx_string("servats_theme_href_css"),
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
        ngx_conf_set_str_slot,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_servats_loc_conf_t, theme_user_css),
        NULL
    },
    {
        ngx_string("servats_theme_href_script_lib"),
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
        ngx_conf_set_str_slot,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_servats_loc_conf_t, theme_user_jsi),
        NULL
    },
    {
        ngx_string("servats_theme_href_script"),
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
        ngx_conf_set_str_slot,
        NGX_HTTP_LOC_CONF_OFFSET,
        offsetof(ngx_http_servats_loc_conf_t, theme_user_jse),
        NULL
    },
    ngx_null_command
};


/**
 * We begin by utilizing the standard module structures
 */
static ngx_http_module_t ngx_http_servats_module_ctx = {
    NULL,                                       /* pre-configuration */
    ngx_http_servats_init,                      /* post-configuration */
    NULL,                                       /* create main configuration */
    NULL,                                       /* initialize main configuration */
    NULL,                                       /* create server configuration */
    NULL,                                       /* merge server configuration */
    ngx_http_servats_create_loc_conf,           /* create location configuration */
    ngx_http_servats_merge_loc_conf             /* merge location configuration */
};

ngx_module_t ngx_http_servats_module = {
    NGX_MODULE_V1,
    &ngx_http_servats_module_ctx,               /* module context */
    ngx_http_servats_commands,                  /* module directives */
    NGX_HTTP_MODULE,                            /* module type */
    NULL,                                       /* initialize master */
    NULL,                                       /* initialize module */
    NULL,                                       /* initialize process */
    NULL,                                       /* initialize thread */
    NULL,                                       /* exit thread */
    NULL,                                       /* exit process */
    NULL,                                       /* exit master */
    NGX_MODULE_V1_PADDING
};


/**
 * Location configuration handler allocates memory for our module config struct
 * and sets our enabled config property to unset.
 */
static  void *
ngx_http_servats_create_loc_conf(ngx_conf_t  *cf)
{
    ngx_http_servats_loc_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_servats_loc_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }

    conf->enabled    = NGX_CONF_UNSET;
    conf->theme_both = NGX_CONF_UNSET;

    return conf;
}


/**
 * Merge Nginx configuration attributes by setting the most-specificly-defined
 * configuration value within the Nginx config.
 */
static  char *
ngx_http_servats_merge_loc_conf(ngx_conf_t  *cf, void  *parent, void  *child)
{
    ngx_http_servats_loc_conf_t  *prev = parent;
    ngx_http_servats_loc_conf_t  *conf = child;

    ngx_conf_merge_value(conf->enabled,            prev->enabled,        0);
    ngx_conf_merge_value(conf->theme_both,         prev->theme_both,     1);
    ngx_conf_merge_str_value(conf->theme_user_css, prev->theme_user_css, "");
    ngx_conf_merge_str_value(conf->theme_user_jsi, prev->theme_user_jsi, "");
    ngx_conf_merge_str_value(conf->theme_user_jse, prev->theme_user_jse, "");

    return NGX_CONF_OK;
}


/**
 * Get decending index
 */
static inline ngx_uint_t
get_dec_qps_index(ngx_uint_t index)
{
    return index == 0 ? RECENT_PERIOD - 1 : index - 1;
}


/**
 * Helper to attempt to retrieve the system hostname from Nginx
 */
static  u_char *
get_hostname(ngx_http_request_t  *r)
{
    u_char  *hostname;

    hostname = NULL;
    hostname = ngx_pnalloc(r->pool, ngx_cycle->hostname.len + 1);
    if (hostname == NULL) {
        return NULL;
    }

    ngx_cpystrn(hostname, ngx_cycle->hostname.data, ngx_cycle->hostname.len + 1);

    return hostname;
}


/**
 * Helper to set the header fields, including the content type and optional
 * refresh field
 */
static  void
set_http_header_fields(ngx_http_request_t  *r)
{
    r->headers_out.content_type.len  = ngx_sizeof_ssz(HEADER_CONTENT_TYPE);
    r->headers_out.content_type.data = (u_char *) HEADER_CONTENT_TYPE;
}


/**
 * Start the HTML output with an opening HTML doctype and tag
 */
static  ngx_chain_t *
put_html_root_start(ngx_http_request_t  *r)
{
    ngx_chain_t  *c;
    ngx_buf_t    *b;

    b = ngx_create_temp_buf(r->pool, ngx_sizeof_ssz(HTML_START));
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, ngx_sizeof_ssz(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_START);

    c->buf  = b;
    c->next = NULL;

    return c;
}


/**
 * End the HTML output with a closing tag
 */
static  ngx_chain_t *
put_html_root_close(ngx_http_request_t  *r)
{
    ngx_chain_t  *c;
    ngx_buf_t    *b;

    b = ngx_create_temp_buf(r->pool, ngx_sizeof_ssz(HTML_CLOSE));
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, ngx_sizeof_ssz(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_CLOSE);

    c->buf  = b;
    c->next = NULL;

    return c;
}


/**
 * Start the HTML body output
 */
static  ngx_chain_t *
put_html_body_start(ngx_http_request_t  *r)
{
    ngx_chain_t  *c;
    ngx_buf_t    *b;

    b = ngx_create_temp_buf(r->pool, ngx_sizeof_ssz(HTML_BD_START));
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, ngx_sizeof_ssz(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_BD_START);

    c->buf  = b;
    c->next = NULL;

    return c;
}


/**
 * End the HTML body output, including the executable javascript just prior
 */
static  ngx_chain_t *
put_html_body_close(ngx_http_request_t  *r, ngx_http_servats_loc_conf_t  *alcf)
{
    ngx_chain_t  *c;
    ngx_buf_t    *b;
    ngx_int_t     size;

    size = ngx_sizeof_ssz(HTML_BD_END);

    if (!(alcf->theme_user_jse.len > 0) || alcf->theme_both) {
        size += ngx_sizeof_ssz(HTML_BD_JSE_INT_START) +
            ngx_sizeof_ssz(HTML_BD_JSE_INT_TIME) +
            ngx_sizeof_ssz(HTML_BD_JSE_INT_CHART1) +
            ngx_sizeof_ssz(HTML_BD_JSE_INT_CHART2) +
            ngx_sizeof_ssz(HTML_BD_JSE_INT_CLOSE) +
            (NGX_ATOMIC_T_LEN * 3);
    }

    if (alcf->theme_user_jse.len > 0) {
        servats_log_d1(r, "Using external user javascript file: %s", alcf->theme_user_jse.data);
        size += ngx_sizeof_ssz(HTML_BD_JSE_THEME_USER) + alcf->theme_user_jse.len;
    }

    b = ngx_create_temp_buf(r->pool, size);
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, sizeof(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    if (!(alcf->theme_user_jse.len > 0) || alcf->theme_both) {
        ngx_atomic_int_t  cons_active  = *ngx_stat_active;
        ngx_atomic_int_t  reqs_reading = *ngx_stat_reading;
        ngx_atomic_int_t  reqs_writing = *ngx_stat_writing;

        b->last = ngx_sprintf(b->last, HTML_BD_JSE_INT_START);
        b->last = ngx_sprintf(b->last, HTML_BD_JSE_INT_TIME);
        b->last = ngx_sprintf(b->last, HTML_BD_JSE_INT_CHART1, reqs_reading,
            reqs_writing, (cons_active - (reqs_reading + reqs_writing)));
        b->last = ngx_sprintf(b->last, HTML_BD_JSE_INT_CHART2);
        b->last = ngx_sprintf(b->last, HTML_BD_JSE_INT_CLOSE);
    }

    if (alcf->theme_user_jse.len > 0) {
        b->last = ngx_sprintf(b->last, HTML_BD_JSE_THEME_USER, alcf->theme_user_jse.data);
    }

    b->last = ngx_sprintf(b->last, HTML_BD_END);

    c->buf  = b;
    c->next = NULL;

    return c;
}


/**
 * Put the header output onto the request chain
 */
static  ngx_chain_t *
put_html_head(ngx_http_request_t  *r, ngx_http_servats_loc_conf_t  *alcf)
{
    ngx_chain_t  *c;
    ngx_buf_t    *b;
    ngx_int_t     size;

    size = ngx_sizeof_ssz(HTML_HR_START) +
        ngx_sizeof_ssz(HTML_HR_TITLE) +
        ngx_sizeof_ssz(SERVATS_NAME) +
        ngx_sizeof_ssz(HTML_HR_END);

    if (!(alcf->theme_user_jse.len > 0) || alcf->theme_both) {
        servats_log_d0(r, "Using module provided theme.");
        size += ngx_sizeof_ssz(HTML_HR_CSS_THEME_INT);
    }
    if (alcf->theme_user_css.len > 0) {
        servats_log_d1(r, "Using external user css file: %s", alcf->theme_user_css.data);
        size += ngx_sizeof_ssz(HTML_HR_CSS_THEME_USER) + alcf->theme_user_css.len;
    }

    if (!(alcf->theme_user_jse.len > 0) || alcf->theme_both) {
        size += ngx_sizeof_ssz(HTML_HR_JSI_THEME_INT);
    }
    if (alcf->theme_user_jsi.len > 0) {
        servats_log_d1(r, "Using external user javascript library include: %s", alcf->theme_user_jsi.data);
        size += ngx_sizeof_ssz(HTML_HR_JSI_THEME_USER) + alcf->theme_user_jsi.len;
    }

    b = ngx_create_temp_buf(r->pool, size);
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, sizeof(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_HR_START);
    b->last = ngx_sprintf(b->last, HTML_HR_TITLE, SERVATS_NAME);

    if (!(alcf->theme_user_jse.len > 0) || alcf->theme_both) {
        b->last = ngx_sprintf(b->last, HTML_HR_CSS_THEME_INT);
    }
    if (alcf->theme_user_css.len > 0) {
        b->last = ngx_sprintf(b->last, HTML_HR_CSS_THEME_USER, alcf->theme_user_css.data);
    }

    if (!(alcf->theme_user_jse.len > 0) || alcf->theme_both) {
        b->last = ngx_sprintf(b->last, HTML_HR_JSI_THEME_INT);
    }
    if (alcf->theme_user_jsi.len > 0) {
        b->last = ngx_sprintf(b->last, HTML_HR_JSI_THEME_USER, alcf->theme_user_jsi.data);
    }

    b->last = ngx_sprintf(b->last, HTML_HR_END);

    c->buf  = b;
    c->next = NULL;

    return c;
}


/**
 * Put the server info onto the request chain
 */
static  ngx_chain_t *
put_section_header(ngx_http_request_t  *r)
{
    ngx_chain_t  *c;
    ngx_buf_t    *b;
    u_char       *hostname;
    size_t       size;

    hostname = get_hostname(r);
    if (hostname == NULL) {
        servats_log_d0(r, "Unable to determine the server hostname.");

        return NULL;
    }

    size = ngx_sizeof_ssz(HTML_SEC_HR_START) +
        ngx_sizeof_ssz(HTML_SEC_HR_CLOSE) +
        ngx_sizeof_ssz(HTML_SEC_HR_HEADING) +
        ngx_sizeof_ssz(HTML_SEC_HR_VERSION) +
        ngx_sizeof_ssz(hostname) +
        ngx_sizeof_ssz(NGINX_VERSION) +
        ngx_sizeof_ssz(SERVATS_NAME) +
        ngx_sizeof_ssz(SERVATS_VERSION);

    b = ngx_create_temp_buf(r->pool, size);
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, sizeof(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_SEC_HR_START);
    b->last = ngx_sprintf(b->last, HTML_SEC_HR_HEADING, hostname);
    b->last = ngx_sprintf(b->last, HTML_SEC_HR_VERSION,
        NGINX_VERSION, SERVATS_NAME, SERVATS_VERSION);
    b->last = ngx_sprintf(b->last, HTML_SEC_HR_CLOSE);

    c->buf  = b;
    c->next = NULL;

    return c;
}


static  ngx_chain_t *
put_section_content_start(ngx_http_request_t  *r)
{
    ngx_chain_t  *c;
    ngx_buf_t    *b;

    b = ngx_create_temp_buf(r->pool, ngx_sizeof_ssz(HTML_SEC_CONTENT_START));
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, sizeof(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_SEC_CONTENT_START);

    c->buf  = b;
    c->next = NULL;

    return c;
}


static  ngx_chain_t *
put_section_content_close(ngx_http_request_t  *r)
{
    ngx_chain_t  *c;
    ngx_buf_t    *b;

    b = ngx_create_temp_buf(r->pool, ngx_sizeof_ssz(HTML_SEC_CONTENT_CLOSE));
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, sizeof(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_SEC_CONTENT_CLOSE);

    c->buf  = b;
    c->next = NULL;

    return c;
}


static  ngx_chain_t *
put_section_footer(ngx_http_request_t  *r)
{
    ngx_chain_t  *c;
    ngx_buf_t    *b;
    size_t        size;

    size = ngx_sizeof_ssz(HTML_SEC_FT_START) +
        ngx_sizeof_ssz(HTML_SEC_FT_CLOSE) +
        ngx_sizeof_ssz(HTML_SEC_FT_TIME);

    b = ngx_create_temp_buf(r->pool, size);
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, sizeof(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_SEC_FT_START);
    b->last = ngx_sprintf(b->last, HTML_SEC_FT_TIME);
    b->last = ngx_sprintf(b->last, HTML_SEC_FT_CLOSE);

    c->buf  = b;
    c->next = NULL;

    return c;
}


static  ngx_chain_t *
put_section_row_basic_status(ngx_http_request_t  *r)
{
    ngx_chain_t      *c;
    ngx_buf_t        *b;
    ngx_atomic_int_t  cons_accepted;
    ngx_atomic_int_t  cons_handled;
    ngx_atomic_int_t  cons_active;
    ngx_atomic_int_t  reqs_total;
    ngx_atomic_int_t  reqs_reading;
    ngx_atomic_int_t  reqs_writing;
    size_t            size;

    cons_accepted = *ngx_stat_accepted;
    cons_handled  = *ngx_stat_handled;
    cons_active   = *ngx_stat_active;
    reqs_total    = *ngx_stat_requests;
    reqs_reading  = *ngx_stat_reading;
    reqs_writing  = *ngx_stat_writing;

    size = ngx_sizeof_ssz(HTML_SEC_BASIC_START) +
        ngx_sizeof_ssz(HTML_SEC_BASIC_COL_1) +
        ngx_sizeof_ssz(HTML_SEC_BASIC_COL_2) +
        ngx_sizeof_ssz(HTML_SEC_BASIC_CLOSE) +
        (NGX_ATOMIC_T_LEN * 7);

    b = ngx_create_temp_buf(r->pool, size);
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, sizeof(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_SEC_BASIC_START);

    b->last = ngx_sprintf(b->last, HTML_SEC_BASIC_COL_1, cons_active, cons_accepted, cons_handled, reqs_total);
    b->last = ngx_sprintf(b->last, HTML_SEC_BASIC_COL_2, reqs_reading, reqs_writing, cons_active - (reqs_reading + reqs_writing));

    b->last = ngx_sprintf(b->last, HTML_SEC_BASIC_CLOSE);

    c->buf  = b;
    c->next = NULL;

    return c;
}


static  ngx_chain_t *
put_section_row_war_status(ngx_http_request_t  *r)
{
    worker_score  *ws;
    ngx_time_t    *tp;
    ngx_chain_t   *c;
    ngx_buf_t     *b;
    uint32_t       query_cnt_s;
    uint32_t       query_cnt_l;
    uint32_t       current;
    uint32_t       past;
    uint32_t       index;
    uint32_t       tmp_idx;
    uint32_t       hz;
    uint32_t       i;
    uint32_t       j;
    size_t         size;
    size_t         workerSize;

    if (WORKER_DPLY_PERIOD_L <= WORKER_DPLY_PERIOD_S || RECENT_PERIOD <= WORKER_DPLY_PERIOD_L) {
        return NGX_OK;
    }

    query_cnt_s = 0;
    query_cnt_l = 0;
    hz          = sysconf(_SC_CLK_TCK);
    tp          = ngx_timeofday();
    current     = (uint32_t) tp->sec;
    current    -= 1;
    index       = current & RECENT_MASK;

    workerSize = ngx_sizeof_ssz(HTML_SEC_WAR_COL_1_ROW) +
        4 + 5 + 5 + 1 +
        (NGX_INT64_LEN * 2);

    size = ngx_sizeof_ssz(HTML_SEC_WAR_START) +
        ngx_sizeof_ssz(HTML_SEC_WAR_COL_1_S) +
        (workerSize * ngx_num_workers) +
        ngx_sizeof_ssz(HTML_SEC_WAR_COL_1_C) +
        ngx_sizeof_ssz(HTML_SEC_WAR_COL_2) +
        7 + sizeof(WORKER_DPLY_PERIOD_S) +
        7 + sizeof(WORKER_DPLY_PERIOD_L) +
        7 + sizeof(WORKER_DPLY_PERIOD_S) +
        7 + sizeof(WORKER_DPLY_PERIOD_L) +
        ngx_sizeof_ssz(HTML_SEC_WAR_CLOSE);

    b = ngx_create_temp_buf(r->pool, size);
    if (b == NULL) {
        return NULL;
    }

    c = ngx_pcalloc(r->pool, sizeof(ngx_chain_t));
    if (c == NULL) {
        return NULL;
    }

    b->last = ngx_sprintf(b->last, HTML_SEC_WAR_START);
    b->last = ngx_sprintf(b->last, HTML_SEC_WAR_COL_1_S);

    for (i = 0; i < ngx_num_workers; i++) {
        ws = (worker_score *) ((char *)workers + WORKER_SCORE_LEN * i);

        b->last = ngx_sprintf(b->last, HTML_SEC_WAR_COL_1_ROW, i, ws->pid, ws->access_count, ws->mode,
            ((ws->times.tms_utime + ws->times.tms_stime + ws->times.tms_cutime + ws->times.tms_cstime) / (float) hz),
            ((float) ws->bytes_sent / BYTE2BASE2_MEGABYTE));

        tmp_idx = index;
        past    = current;
        for (j = 0; j < WORKER_DPLY_PERIOD_L; j++) {
            if (past == ws->recent_request_cnt [tmp_idx].time) {
                query_cnt_l += ws->recent_request_cnt [tmp_idx].cnt;

                if (j < WORKER_DPLY_PERIOD_S) {
                    query_cnt_s += ws->recent_request_cnt [tmp_idx].cnt;
                }
            }

            tmp_idx = get_dec_qps_index(tmp_idx);
            past   -= 1;
        }
    }

    b->last = ngx_sprintf(b->last, HTML_SEC_WAR_COL_1_C);
    b->last = ngx_sprintf(b->last, HTML_SEC_WAR_COL_2,
        WORKER_DPLY_PERIOD_S, (float)query_cnt_s / (float)WORKER_DPLY_PERIOD_L,
        WORKER_DPLY_PERIOD_L, (float)query_cnt_l / (float)WORKER_DPLY_PERIOD_L,
        WORKER_DPLY_PERIOD_L, WORKER_DPLY_PERIOD_S,
        (float)query_cnt_l * 100 / (query_cnt_l + query_cnt_s),
        (float)query_cnt_s * 100 / (query_cnt_l + query_cnt_s)
    );
    b->last = ngx_sprintf(b->last, HTML_SEC_WAR_CLOSE);

    c->buf  = b;
    c->next = NULL;

    return c;
}


static inline  ngx_chain_t *
get_last_chain_from_request(ngx_chain_t *c)
{
    ngx_chain_t *last = c;

    assert(last != NULL);

    while (last->next != NULL) {
        last = last->next;
    }

    return last;
}


static inline  off_t
get_chain_length(ngx_chain_t *c)
{
    off_t length = 0;

    while (c != NULL) {
        length += ngx_buf_size(c->buf);
        c = c->next;
    }

    return length;
}


static  ngx_int_t
ngx_http_servats_handler(ngx_http_request_t  *r)
{
    ngx_chain_t                  *fc;
    ngx_chain_t                  *mc;
    ngx_chain_t                  *lc;
    ngx_int_t                     ret;
    ngx_http_servats_loc_conf_t  *alcf;

    if (r->method != NGX_HTTP_GET) {
        servats_log_d0(r, "Declining as http method != GET.");

        return NGX_DECLINED;
    }

    alcf = ngx_http_get_module_loc_conf(r, ngx_http_servats_module);

    if (!alcf->enabled) {
        servats_log_d0(r, "Declining as module is disabled.");

        return NGX_DECLINED;
    }

    servats_log_d0(r, "Module loaded.");

    ret = ngx_http_discard_request_body(r);
    if (ret != NGX_OK) {
        servats_log_d0(r, "Request body could not be disgarded!");

        return ret;
    }

    set_http_header_fields(r);

    fc = put_html_root_start(r);
    if (fc == NULL) {
        servats_log_d0(r, "Could not output opening HTML tags.");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc = get_last_chain_from_request(fc);

    mc = put_html_head(r, alcf);
    if (mc == NULL) {
        servats_log_d0(r, "Could not generate header part of report!");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    mc = put_html_body_start(r);
    if (mc == NULL) {
        servats_log_d0(r, "Could not generate the beginning of the html body!");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    mc = put_section_header(r);
    if (mc == NULL) {
        servats_log_d0(r, "Could not generate header section!");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    mc = put_section_content_start(r);
    if (mc == NULL) {
        servats_log_d0(r, "Could not generate content start block!");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    mc = put_section_row_basic_status(r);
    if (mc == NULL) {
        servats_log_d0(r, "Could not generate basic status content row!");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    mc = put_section_row_war_status(r);
    if (mc == NULL) {
        servats_log_d0(r, "Could not generate worker/request content row!");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    mc = put_section_content_close(r);
    if (mc == NULL) {
        servats_log_d0(r, "Could not generate content close block!");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    mc = put_section_footer(r);
    if (mc == NULL) {
        servats_log_d0(r, "Could not generate footer part of report!");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    mc = put_html_body_close(r, alcf);
    if (mc == NULL) {
        servats_log_d0(r, "Could not executable javascript with closing body tag block.");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    mc = put_html_root_close(r);
    if (mc == NULL) {
        servats_log_d0(r, "Could not output closing HTML tags.");

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    lc->next = mc;
    lc = get_last_chain_from_request(mc);

    lc->buf->last_buf = 1;

    r->headers_out.status           = NGX_HTTP_OK;
    r->headers_out.content_length_n = get_chain_length(fc);

    ret = ngx_http_send_header(r);
    if (NGX_ERROR == ret || NGX_OK < ret || r->header_only) {
        servats_log_d0(r, "Could not send header!");

        return ret;
    }

    return ngx_http_output_filter(r, fc);
}


/**
 * Initialize module; do configuration and set module handler
 */
static  ngx_int_t
ngx_http_servats_init(ngx_conf_t  *cf)
{
    ngx_http_handler_pt        *h;
    ngx_http_core_main_conf_t  *cmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);
    h    = ngx_array_push(&cmcf->phases[NGX_HTTP_CONTENT_PHASE].handlers);

    if (h == NULL) {
        return NGX_ERROR;
    }

    *h = ngx_http_servats_handler;

    return NGX_OK;
}


/* EOF */
