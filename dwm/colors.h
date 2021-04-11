/* ------------ dracula theme ------------- */
static char norm_fg[]           = "#f8f8f2"; /* text color of unselected tags and modules   (dracula.foreground) */
static char norm_bg[]           = "#282a36"; /* bg color of unselected tags and modules     (dracula.background) */
static char norm_border[]       = "#6272a4"; /* border color of unselected windows          (dracula.comment) */
static char sel_fg[]            = "#8be9fd"; /* text color of selected tag                  (dracula.cyan) */
static char sel_bg[]            = "#44475a"; /* bg color of selected tag                    (dracula.currentline) */
static char sel_border[]        = "#50fa7b"; /* border color of selected window             (dracula.green) */
static char urg_fg[]            = "#8be9fd"; /* text color of urgent tag                    (dracula.cyan) */
static char urg_bg[]            = "#ff5555"; /* bg color of urgent tag                      (dracula.red) */
static char urg_border[]        = "#ff5555"; /* border color of urgent window               (dracula.red) */
static char *colors[][3]        = {
    /*               fg           bg         border         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border },
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
