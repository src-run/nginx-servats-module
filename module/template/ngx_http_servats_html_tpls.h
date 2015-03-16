/*
 * module/template/ngx_http_servats_html_tpls.h
 *
 * This file is part of the HTTP Servats Module.
 *
 * For the full copyright and license information, please view the LICENSE.md
 * file that was distributed with this source code.
 *
 */


#ifndef NGX_HTTP_SERVATS_HTML_TPLS_H_
#define NGX_HTTP_SERVATS_HTML_TPLS_H_


/**
 * Start/closing HTML tags
 */
#define  HTML_START             "<!DOCTYPE html>\n" \
                                "<html lang=\"en\">\n"

#define  HTML_CLOSE             "</html>\n"


/**
 * Header template data
 */
#define  HTML_HR_START          "  <head>\n"

#define  HTML_HR_TITLE          "    <title>%s</title>\n"

#define  HTML_HR_JSI_THEME_INT  "    <script src=\"//ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js\"></script>\n" \
                                "    <script src=\"//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/js/bootstrap.min.js\"></script>\n" \
                                "    <script src=\"//cdnjs.cloudflare.com/ajax/libs/Chart.js/1.0.2/Chart.min.js\"></script>\n"

#define  HTML_HR_JSI_THEME_USER "    <script src=\"%s\"></script>\n"

#define  HTML_HR_CSS_THEME_INT  "    <link rel=\"stylesheet\" href=\"//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css\">\n" \
                                "    <link rel=\"stylesheet\" href=\"//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap-theme.min.css\">\n" \
                                "    <link rel=\"stylesheet\" href=\"//fonts.googleapis.com/css?family=Bitter:400,400italic|Source+Sans+Pro:300,400,600,300italic,400italic|Ubuntu+Mono:400,700,400italic|Roboto+Condensed:300italic,400italic,700,300,400\">\n" \
                                "    <style type=\"text/css\">" \
                                "      body {\n" \
                                "       background-color:#eee;\n" \
                                "      }\n" \
                                "      header {\n" \
                                "       background-color:#4E2C50;\n" \
                                "       border-bottom: 4px solid #2D0B2F!important;\n" \
                                "       color:#eee;\n" \
                                "       margin-bottom:20px;\n" \
                                "      }\n" \
                                "      header h1 {\n" \
                                "       font-size:32px;\n" \
                                "       font-family: Lato,\"Helvetica Neue\",Helvetica,Arial,sans-serif;\n" \
                                "       font-weight: 300;\n" \
                                "       margin:20px 0 10px 0;\n" \
                                "      }\n" \
                                "      header h1 small {\n" \
                                "       color: rgba(255, 255, 255, 0.65);\n" \
                                "       text-transform: uppercase;\n" \
                                "      }\n" \
                                "      header dl dd {\n" \
                                "       color:rgba(255,255,255,0.75);\n" \
                                "       margin-left:12px;\n" \
                                "      }\n" \
                                "      section {\n" \
                                "       overflow: hidden;\n" \
                                "       transition: box-shadow 1s ease-out;\n" \
                                "       -webkit-box-shadow: 0 2px 14px #ccc;\n" \
                                "       box-shadow: 0 2px 14px #ccc;\n" \
                                "       margin: 28px 0!important;\n" \
                                "       background-color: rgba(53,77,72,.04)!important;\n" \
                                "       border: 1px solid rgba(44,62,80,.26)!important;\n" \
                                "       padding: 0 0 20px!important;\n" \
                                "       border-radius: 0;\n" \
                                "       font-family: Lato,\"Helvetica Neue\",Helvetica,Arial,sans-serif;\n" \
                                "       font-size: 15px;\n" \
                                "       line-height: 1.42857143;\n" \
                                "       color: #2c3e50;\n" \
                                "       width: 100%;\n" \
                                "      }\n" \
                                "      section h3 {\n" \
                                "       transition: background-color 1s;\n" \
                                "       box-shadow: inset rgba(0,187,255,.05) 0 10px 10px;\n" \
                                "       font-family: \"Roboto Condensed\";\n" \
                                "       text-transform: uppercase;\n" \
                                "       font-weight: 200;\n" \
                                "       font-size: 26px;\n" \
                                "       margin-top: 0;\n" \
                                "       background-color: rgba(53,142,168,1);\n" \
                                "       display: block;\n" \
                                "       padding: 12px;\n" \
                                "       text-align: center;\n" \
                                "       color:#000;\n" \
                                "      }\n" \
                                "      section dl {\n" \
                                "       margin:28px 0 8px 0;\n" \
                                "      }\n" \
                                "      section dd {\n" \
                                "       font-family: \"Ubuntu Mono\", monospace;\n" \
                                "      }\n" \
                                "      #stats-states {\n" \
                                "       overflow:hidden;\n" \
                                "      }\n" \
                                "      .request-operation, .worker-operation {\n" \
                                "       margin: 20px 20px -10px 20px;\n" \
                                "      }\n" \
                                "      .request-return {\n" \
                                "       font-family:Ubuntu Mono;\n" \
                                "      }\n" \
                                "      .has-chart {\n" \
                                "       text-align:center;\n" \
                                "      }\n" \
                                "      .has-chart .chart-wrapper {\n" \
                                "       margin:18px auto 0 auto;\n" \
                                "      }\n" \
                                "      .table-wrapper {\n" \
                                "       margin: 20px 20px -10px 20px;\n" \
                                "      }\n" \
                                "      footer {\n" \
                                "       background-color:rgba(78, 44, 80, 0.19);\n" \
                                "       margin-top:20px;\n" \
                                "       padding:20px 0;\n" \
                                "      }\n" \
                                "      footer p {\n" \
                                "       margin-bottom:0;\n" \
                                "      }\n" \
                                "    </style>\n"

#define  HTML_HR_CSS_THEME_USER "    <link rel=\"stylesheet\" href=\"%s\" type=\"text/css\"/>\n"

#define  HTML_HR_END            "  </head>\n"


/**
 * Start/end body tag
 */
#define  HTML_BD_START          "  <body>\n"

#define  HTML_BD_JSE_INT_START  "    <script>\n"

#define  HTML_BD_JSE_INT_TIME   "        $(window).load(function(){\n" \
                                "            (function () {\n" \
                                "                var date = new Date();\n" \
                                "                function getCurrentDatetimeString() {\n" \
                                "                    return date.toLocaleString();\n" \
                                "                }\n" \
                                "                window.getCurrentDatetimeString = getCurrentDatetimeString;\n" \
                                "            })();\n" \
                                "            $(\"#page-generation-time\").html(getCurrentDatetimeString());\n" \
                                "        });\n" \
                                "        Chart.defaults.global.animation              = false;\n" \
                                "        Chart.defaults.global.responsive             = true;\n" \
                                "        Chart.defaults.global.maintainAspectRatio    = true;\n" \
                                "        Chart.defaults.global.tooltipFontSize        = 11;\n" \
                                "        Chart.defaults.global.tooltipFontFamily      = \"'Roboto Condensed', 'Roboto', Helvetica Neue', 'Helvetica', 'Arial', sans-serif\";\n" \
                                "        Chart.defaults.global.tooltipTitleFontSize   = 11;\n" \
                                "        Chart.defaults.global.tooltipTitleFontFamily = \"'Roboto', 'Helvetica Neue', 'Helvetica', 'Arial', sans-serif\";\n"

#define  HTML_BD_JSE_INT_CHART1 "        var statesChartData = [\n" \
                                "          {\n" \
                                "            value: %uA,\n" \
                                "            color: \"#FDB45C\",\n" \
                                "            highlight: \"#FFC870\",\n" \
                                "            label: \"Reading\"\n" \
                                "          },\n" \
                                "          {\n" \
                                "            value: %uA,\n" \
                                "            color: \"#46BFBD\",\n" \
                                "            highlight: \"#5AD3D1\",\n" \
                                "            label: \"Writing\"\n" \
                                "          },\n" \
                                "          {\n" \
                                "            value: %uA,\n" \
                                "            color: \"#F7464A\",\n" \
                                "            highlight: \"#FF5A5E\",\n" \
                                "            label: \"Waiting\"\n" \
                                "          }\n" \
                                "        ];\n" \
                                "        var statesChartCtx = $(\"#stats-states-chart\").get(0).getContext(\"2d\");\n" \
                                "        var statesChart = new Chart(statesChartCtx).Pie(statesChartData);\n"

#define  HTML_BD_JSE_INT_CHART2 "        var timeChartCtx = $(\"#stats-requests-by-time-chart\").get(0).getContext(\"2d\");\n" \
                                "        var timeChart = new Chart(timeChartCtx).Bar(timeChartData);\n"

#define  HTML_BD_JSE_INT_CLOSE  "        $(window).load(function(){\n" \
                                "            (function () {\n" \
                                "                $('.request-gzipr').each(function(){\n" \
                                "                    el = $(this);\n" \
                                "                    if (el.html() == '-1.00') { el.html('<span class=\"label label-default\">n/a</span>'); }\n" \
                                "                });\n" \
                                "                $('.request-upstream-time').each(function(){\n" \
                                "                    el = $(this);\n" \
                                "                    if (el.html() == '-1') { el.html('<span class=\"label label-default\">n/a</span>'); }\n" \
                                "                });\n" \
                                "                $('.worker-operation span, .request-operation span').each(function(){\n" \
                                "                    el = $(this);\n" \
                                "                    if (el.html() == 'W') {\n" \
                                "                        el.removeClass('label-info'); el.addClass('label-success');\n" \
                                "                        el.attr('title', 'Sending reply');\n" \
                                "                    } else if (el.html() == 'R') {\n" \
                                "                        el.attr('title', 'Reading request');\n" \
                                "                    } else if (el.html() == 'L') {\n" \
                                "                        el.removeClass('label-info'); el.addClass('label-danger');\n" \
                                "                        el.attr('title', 'Logging');\n" \
                                "                    } else if (el.html() == 'I') {\n" \
                                "                        el.removeClass('label-info'); el.addClass('label-warning');\n" \
                                "                        el.attr('title', 'Inactive connection');\n" \
                                "                    } else if (el.html() == '-') {\n" \
                                "                        el.removeClass('label-info'); el.addClass('label-default');\n" \
                                "                        el.attr('title', 'Waiting for request');\n" \
                                "                    }\n" \
                                "                    el.tooltip({placement: 'right'});\n" \
                                "                });\n" \
                                "            })();\n" \
                                "        });\n" \
                                "    </script>\n"

#define  HTML_BD_JSE_THEME_USER "    <script src=\"%s\"></script>\n"

#define  HTML_BD_END            "  </body>\n"


/**
 * Section: Header fragments
 */
#define  HTML_SEC_HR_START      "    <header>\n" \
                                "      <div class=\"container\">\n"

#define  HTML_SEC_HR_HEADING    "      <h1>Nginx Server Status <small>%s</small></h1>\n"

#define  HTML_SEC_HR_VERSION    "      <dl>\n" \
                                "        <dt>Server Version</dt>\n" \
                                "        <dd>Nginx/%s</dd>\n" \
                                "        <dt>Module Version</dt>\n" \
                                "        <dd>%s/%s</dd>\n" \
                                "      </dl>\n"

#define  HTML_SEC_HR_CLOSE      "      </div>\n" \
                                "    </header>\n"


/**
 * Section: Content blocks
 */
#define  HTML_SEC_CONTENT_START "    <div class=\"container\">\n"

#define  HTML_SEC_CONTENT_CLOSE "    </div>\n"

#define  HTML_SEC_BASIC_START   "      <div class=\"row\">\n"

#define  HTML_SEC_BASIC_COL_1   "        <div  class=\"col-md-6\">\n" \
                                "          <section id=\"stats-overview\">\n" \
                                "            <h3>Overview</h3>\n" \
                                "            <dl class=\"dl-horizontal\">\n" \
                                "             <dt>Active Connections</dt>\n" \
                                "               <dd>%uA</dd>\n" \
                                "             <dt>Accepted/Handled</dt>\n" \
                                "               <dd>%uA of %uA</dd>\n" \
                                "             <dt>Total Requests</dt>\n" \
                                "               <dd>%uA</dd>\n" \
                                "            </dl>\n" \
                                "          </section>\n" \
                                "        </div>\n"

#define  HTML_SEC_BASIC_COL_2   "        <div class=\"col-md-6\">\n" \
                                "          <section id=\"stats-states\">\n" \
                                "            <h3>Request States</h3>\n" \
                                "            <div class=\"col-md-6 col-md-offset-0 col-sm-6 col-sm-offset-3\">\n" \
                                "              <dl class=\"dl-horizontal\">\n" \
                                "                <dt>Reading</dt>\n" \
                                "                  <dd>%uA</dd>\n" \
                                "                <dt>Writing</dt>\n" \
                                "                  <dd>%uA</dd>\n" \
                                "                <dt>Waiting</dt>\n" \
                                "                  <dd>%uA</dd>\n" \
                                "              </dl>\n" \
                                "            </div>\n" \
                                "            <div class=\"col-md-4 col-md-offset-1 col-sm-6 col-sm-offset-3 has-chart\">\n" \
                                "              <div class=\"chart-wrapper\">\n" \
                                "                <canvas id=\"stats-states-chart\" width=\"140\" height=\"140\"></canvas>\n" \
                                "              </div>\n" \
                                "            </div>\n" \
                                "          </section>\n" \
                                "        </div>\n"

#define  HTML_SEC_BASIC_CLOSE   "      </div>\n"

#define  HTML_SEC_WAR_START     "      <div class=\"row\">\n"

#define  HTML_SEC_WAR_COL_1_S   "        <div class=\"col-md-6\">\n" \
                                "          <section id=\"stats-workers\">\n" \
                                "            <h3>Workers</h3>\n" \
                                "            <div class=\"table-wrapper\">\n" \
                                "              <table class=\"table table-striped\">\n" \
                                "                <thead>\n" \
                                "                 <tr>\n" \
                                "                   <th>Worker</th>\n" \
                                "                   <th>PID</th>\n" \
                                "                   <th>Requests</th>\n" \
                                "                   <th>Operation</th>\n" \
                                "                   <th>CPU</th>\n" \
                                "                   <th>Megabytes</th>\n" \
                                "                 </tr>\n" \
                                "               </thead>\n" \
                                "               <tbody>\n"

#define  HTML_SEC_WAR_COL_1_ROW "                 <tr>\n" \
                                "                   <td>%4d</td>\n" \
                                "                   <td>%5d</td>\n" \
                                "                   <td>%d</td>\n" \
                                "                   <td class=\"worker-operation\"><span class=\"label label-info\">%c</span></td>\n" \
                                "                   <td>%.2f</td>\n" \
                                "                   <td>%.2f</td>\n" \
                                "                 </tr>\n"

#define  HTML_SEC_WAR_COL_1_C   "               </tbody>\n" \
                                "              </table>\n" \
                                "            </div>\n" \
                                "          </section>\n" \
                                "        </div>\n"

#define  HTML_SEC_WAR_COL_2     "        <div class=\"col-md-6\">\n" \
                                "          <section id=\"stats-requests-by-time\">\n" \
                                "            <h3>Requests Over Time</h3>\n" \
                                "            <div class=\"col-md-6 col-md-offset-0 col-sm-6 col-sm-offset-3\">\n" \
                                "              <dl class=\"dl-horizontal\">\n" \
                                "                <dt>Last %2d Seconds</dt>\n" \
                                "                  <dd>%.02f/sec</dd>\n" \
                                "                <dt>Last %2d Seconds</dt>\n" \
                                "                  <dd>%.02f/sec</dd>\n" \
                                "              </dl>\n" \
                                "            </div>\n" \
                                "            <div class=\"col-md-4 col-md-offset-1 col-sm-6 col-sm-offset-3 has-chart\">\n" \
                                "              <div class=\"chart-wrapper\">\n" \
                                "                <canvas id=\"stats-requests-by-time-chart\" width=\"240\" height=\"280\"></canvas>\n" \
                                "              </div>\n" \
                                "            </div>\n" \
                                "            <script>\n" \
                                "            var timeChartData = {\n" \
                                "              scaleOverride: 100,\n" \
                                "              labels: [\"%% / %2ds\", \"%% / %2ds\"],\n" \
                                "              datasets: [\n" \
                                "                {\n" \
                                "                  fillColor: \"#5AD3D1\",\n" \
                                "                  strokeColor: \"#46BFBD\",\n" \
                                "                  highlightFill: \"#46BFBD\",\n" \
                                "                  highlightStroke: \"#46BFBD\",\n" \
                                "                  data: [%.02f, %.02f]\n" \
                                "                }\n" \
                                "              ]\n" \
                                "            };\n" \
                                "            </script>\n" \
                                "          </section>\n" \
                                "        </div>\n"

#define  HTML_SEC_WAR_CLOSE     "      </div>\n"

#define  HTML_SEC_WC_START      "      <section id=\"stats-request\">\n" \
                                "        <h3>Requests</h3>\n" \
                                "        <div class=\"table-wrapper\">\n" \
                                "          <table class=\"table table-striped\">\n" \
                                "            <thead>\n" \
                                "              <tr>\n" \
                                "                <th>Worker</th>\n" \
                                "                <th>Requests</th>\n" \
                                "                <th>Operation</th>\n" \
                                "                <th>Bytes</th>\n" \
                                "                <th>Client</th>\n" \
                                "                <th>Servername</th>\n" \
                                "                <th>Gzip Ratio</th>\n" \
                                "                <th>Age</th>\n" \
                                "                <th>Status</th>\n" \
                                "                <th>Time</th>\n" \
                                "                <th>Proxy Time</th>\n" \
                                "                <th>Request</th>\n" \
                                "              </tr>\n" \
                                "            </thead>\n" \
                                "            <tbody>\n"

#define  HTML_SEC_WC_ROW        "              <tr>\n" \
                                "                <td>%4d-%04d</td>\n" \
                                "                <td>%d</td>\n" \
                                "                <td class=\"request-operation\"><span class=\"label label-info\">%c</span></td>\n" \
                                "                <td>%d</td>\n" \
                                "                <td>%s</td>\n" \
                                "                <td>%s</td>\n" \
                                "                <td class=\"request-gzipr\">%.02f</td>\n" \
                                "                <td>%d</td>\n" \
                                "                <td class=\"request-return\"><span class=\"label label-warning\">%ui</span></td>\n" \
                                "                <td>%d</td>\n" \
                                "                <td class=\"request-upstream-time\">%d</td>\n" \
                                "                <td>%s</td>\n" \
                                "              </tr>\n"

#define  HTML_SEC_WC_CLOSE      "            </tbody>\n" \
                                "          </table>\n" \
                                "        </div>\n" \
                                "      </section>\n"

/**
 * Section: Footer fragments
 */
#define  HTML_SEC_FT_START      "    <footer>\n" \
                                "      <div class=\"container\">\n"

#define  HTML_SEC_FT_TIME       "        <p>Generated on <span id=\"page-generation-time\"></p>"

#define  HTML_SEC_FT_CLOSE      "      </div>\n" \
                                "    </footer>\n"


#endif /* NGX_HTTP_SERVATS_HTML_TPLS_H_ */


/* EOF */
