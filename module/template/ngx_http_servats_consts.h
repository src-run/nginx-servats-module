/*
 * module/template/ngx_http_servats_consts.h
 *
 * This file is part of the HTTP Servats Module.
 *
 * For the full copyright and license information, please view the LICENSE.md
 * file that was distributed with this source code.
 *
 */


#ifndef NGX_HTTP_SERVATS_CONSTS_H_
#define NGX_HTTP_SERVATS_CONSTS_H_


/**
 * Header content type
 */
#define  HEADER_CONTENT_TYPE 	"text/html; charset=utf8"

/**
 * Base 10 to base 2 size conversions from bytes to k, b, and g
 */
#define  BYTE2BASE2_KILOBYTE    1024.0
#define  BYTE2BASE2_MEGABYTE    1048576.0
#define  BYTE2BASE2_GIGABYTE    1073741824.0


/**
 * Define our multiplier as well as the maximum value for sizes
 * displayed to users before converting to larger size
 */
#define  BYTE2BASE2_MULTIPLIER	1024.0
#define  BYTE2BASE2_CUTOFF      1024.0


/**
 * Default value to show for request millisecond display
 */
#define  DEFAULT_REQ_MS_DPLY    0


/**
 * Minimum and maximum refresh header value in seconds
 */
#define  HDR_REFRESH_MIN_SECS   0
#define  HDR_REFRESH_MAX_SECS   60


/**
 * Short and long periods to display for worker statistics
 */
#define  WORKER_DPLY_PERIOD_S   10
#define  WORKER_DPLY_PERIOD_L   60


#endif /* NGX_HTTP_SERVATS_CONSTS_H_ */


/* EOF */
