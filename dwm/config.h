/* See LICENSE file for copyright and license details. */


/* -------------- appearance ------------- */
#include "colors.h"                             /* colorscheme */
static const char *fonts[]          = { "CascadiaCodePL:size=10", "JoyPixels:pixelsize=10" /*"monospace:size=10"*/ };
static const char dmenufont[] 	    = "CascadiaCodePL:size=10";
static unsigned int borderpx        = 1;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */

static int smartgaps                = 1;        /* 1 means no outer gap when there is only one window */
static const unsigned int gappih    = 3;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 3;        /* vert inner gap between windows */
static const unsigned int gappoh    = 3;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 3;        /* vert outer gap between windows and screen edge */

static const int viewontag          = 1;        /* Switch view on tag switch */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static int barheight                = 0;        /* 0 means that dwm will calculate bar height */
static int hidetags                 = 0;        /* 1 means hide vacant tags; 0 means show all tags */


/* ---------------- systray -------------- */
static const int showsystray             = 1;   /* 0 means no systray */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/


/* --------------- autostart ------------- */
static const char autostartsh[]         = "autostart.sh";
static const char autostartblocksh[]    = "autostart_blocking.sh";
static const char dwmdir[]              = "dwm";     /* parent dir of autostart(_blocking).sh */
static const char pathfromhome[]        = ".config"; /* custom dir from $HOME if $XDG_CONFIG_HOME was not set; don't add leading & trailing '/' */


/* ----------- sticky indicator ---------- */
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,4}, {2,3}, {0,4}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,4};    /* defines the bottom right corner of the bounding box of the polygon (origin is always 0,0) */
#define STICKYICONSH boxw + (boxw * 6 / 7) 	/* defines the height of the final, scaled polygon as it will be drawn. boxw is equal to the width of the shape */


/* ----------------- tags ---------------- */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


/* ----------------- rules --------------- */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};


/* ---------------- layouts -------------- */
static float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol   arrange function */
 	{ "[T]",	tile },			    /* Default: Master on left, Slaves on right */
	{ "|B|",	bstack },		    /* Master on top, Slaves on bottom */
	{ "[G]",	grid },                     /* Grid layout */
	{ "|G|",	gaplessgrid },              /* Grid layout but without gaps */
	{ "[C]",	centeredmaster },	    /* Master in middle, Slaves on sides */
	{ "|C|",	centeredfloatingmaster },   /* Same as centeredmaster but Master floats */
 	{ "[M]",	monocle },		    /* All windows on top of each other */
	{ "|M|",	deck },			    /* Master on left, Slaves in monocle-like mode on right */
	{ "[@]",	spiral },		    /* Fibonacci spiral */
	{ "|@|",	dwindle },		    /* Decreasing in size right and leftward */
	{ "[-]",	NULL },			    /* No layout function means floating behavior */
	{ NULL,		NULL },
	/* { "###",    nrowgrid }, */
	/* { "---",    horizgrid }, */
	/* { "===",    bstackhoriz }, */
};


/* --------------- Xresources ------------ */
ResourcePref resources[] = {
		{ "color0",             STRING,  &norm_bg },
		{ "color8",             STRING,  &norm_border },
		{ "color15",            STRING,  &norm_fg },
		{ "color2",             STRING,  &sel_bg },
		{ "color15",            STRING,  &sel_border },
		{ "color15",            STRING,  &sel_fg },
		{ "color1",             STRING,  &urg_bg },
		{ "color1",             STRING,  &urg_border },
		{ "color15",            STRING,  &urg_fg },
		{ "barheight",          INTEGER, &barheight },
		{ "hidetags",           INTEGER, &hidetags },
};


/* ----------- key definitions ----------- */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* ------------- default apps ------------ */
/*#define APP_BROWSER "microsoft-edge-dev"*/
#define APP_RUN_LAUNCHER "dmenu"
#define APP_TERMINAL "kitty"


/* --------------- commands -------------- */
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
static const char *termcmd[]  = { APP_TERMINAL, NULL };
/*static const char *roficmd[] = { APP_RUN_LAUNCHER, "-modi", "drun", "-show", "drun", "-show-icons", NULL };*/
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg, "-sf", sel_fg, NULL };

/* Volume keys */
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+1%", NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-1%", NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute", "0", "toggle", NULL };

/* backlight */
static const char *brightnessup[]   = { "sudo", "xbacklight", "-inc", "2", NULL };
static const char *brightnessdown[] = { "sudo", "xbacklight", "-dec", "2", NULL };

/* media keys (audacious) */
/*static const char *toggle[] = { "/usr/bin/audacious", "-t", NULL };
static const char *prev[]   = { "/usr/bin/audacious", "-r", NULL };
static const char *next[]   = { "/usr/bin/audacious", "-f", NULL };*/

/* media keys (cmus-remote) */
static const char *toggle[] = { "/usr/bin/cmus-remote", "-u", NULL };
static const char *prev[] = { "/usr/bin/cmus-remote", "-r", NULL };
static const char *next[] = { "/usr/bin/cmus-remote", "-n", NULL };

/* launch pcmanfm */
static const char *pcmanfm[] = { "/usr/bin/pcmanfm", NULL };

/* launch microsoft-edge-dev */
static const char *edge[] = { "/usr/bin/microsoft-edge-dev", NULL };

/* capture region with xfce4-screenshooter */
static const char *ss_region[] = { "/usr/bin/xfce4-screenshooter", "-r", NULL };

/* take screenshot with scrot */
static const char *ss_normal[] = { "/usr/bin/scrot", "-z", "-e", "mv $f $~/Pictures/Screenshots/", NULL };
static const char *ss_window[] = { "/usr/bin/scrot", "-z", "-s", "-e", "mv $f $~/Pictures/Screenshots/", NULL };

/* launch synapse */
static const char *synapse[] = { "/usr/bin/synapse", NULL };

/* suspend and lock */
static const char *suspend[] = { "/usr/bin/betterlockscreen", "-s", NULL };

/* lock */
static const char *lock[] = { "/usr/bin/betterlockscreen", "-l", NULL };

#include <X11/XF86keysym.h>
/*static const char vol_up[]    =  "pactl set-sink-volume 0 +5%; kill -44 $(pidof dwmblocks)" ;
static const char vol_down[]  =  "pactl set-sink-volume 0 -5%; kill -44 $(pidof dwmblocks)" ;
static const char vol_mute[]  =  "pactl set-sink-mute 0 toggle; kill -44 $(pidof dwmblocks)";*/


/* -------------- key bindngs ------------ */
static Key keys[] = {
	/* modifier                     key        function        argument */

    /* ---------------- basic ---------------- */
	{ MODKEY,                       XK_d,       spawn,           {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,  spawn,           {.v = termcmd } },

    /* --------------- layouts --------------- */
	{ MODKEY,			 XK_t,		setlayout,	    {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		 XK_t,		setlayout,	    {.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			 XK_y,		setlayout,	    {.v = &layouts[2]} }, /* grid */
	{ MODKEY|ShiftMask,		 XK_y,		setlayout,	    {.v = &layouts[3]} }, /* gaplessgrid */
	{ MODKEY,			 XK_u,		setlayout,	    {.v = &layouts[4]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		 XK_u,		setlayout,	    {.v = &layouts[5]} }, /* centeredfloatingmaster */
	{ MODKEY,			 XK_i,		setlayout,	    {.v = &layouts[6]} }, /* monocle */
	{ MODKEY|ShiftMask,		 XK_i,		setlayout,	    {.v = &layouts[7]} }, /* deck */
	/* { MODKEY,		         XK_o,		setlayout,	    {.v = &layouts[8]} }, /1* spiral *1/ */
	/* { MODKEY|ShiftMask,		 XK_o,		setlayout,	    {.v = &layouts[9]} }, /1* dwindle *1/ */
	{ MODKEY,                       XK_Tab,     cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Tab,     cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,   setlayout,      {0} },

    /* ---------------- gaps ----------------- */
	{ MODKEY,		        XK_a,	    togglegaps,	    {0} },
	{ MODKEY|ShiftMask,	        XK_a,	    defaultgaps,    {0} },
	{ MODKEY,                       XK_z,       incrogaps,      {.i = +1 } }, /* inc out gaps */
	{ MODKEY|ShiftMask,             XK_z,       incrogaps,      {.i = -1 } }, /* dec out gaps */
	{ MODKEY,                       XK_x,       incrigaps,      {.i = +1 } }, /* inc inr gaps */
	{ MODKEY|ShiftMask,             XK_x,       incrigaps,      {.i = -1 } }, /* dec inr gaps */
	{ MODKEY|ControlMask,		XK_z,	    incrgaps,	    {.i = +1 } }, /* inc all gaps */
	{ MODKEY|ControlMask,	        XK_x,	    incrgaps,	    {.i = -1 } }, /* dec all gaps */

    /* --------------- stack ----------------- */
	{ MODKEY,             		XK_q,       killclient,     {0} },
	{ MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,       rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,       rotatestack,    {.i = -1 } },
	{ MODKEY,			XK_m,	    incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_m,	    incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_e,       focusurgent,    {0} },
	{ MODKEY,		        XK_g,	    shifttag,	    { .i = +1 } },
	{ MODKEY|ShiftMask,		XK_g,	    shifttag,	    { .i = -1 } },
	/*{ MODKEY,			XK_s,	    togglesticky,	{0} },*/

    /* ----------------- tag ----------------- */
	{ Mod1Mask,                     XK_Tab,     shiftviewclients, { .i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_Tab,     shiftviewclients, { .i = -1 } },
	{ MODKEY,                       XK_r,       reorganizetags, {0} },

    /* ----------------- bar ----------------- */
	{ MODKEY|ShiftMask,                       XK_b,       togglebar,      {0} },

    /* ------------- focus monitor ----------- */
	{ MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },

    /* --------------- reszie ---------------- */
	{ MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,   togglefloating, {0} },
	{ MODKEY,                       XK_f,       togglefullscreen, {0} },
	{ MODKEY|ShiftMask,             XK_f,       togglefakefullscreen, {0} },

    	/* volume keys */
    	{ 0,            		XF86XK_AudioLowerVolume,    spawn,          {.v = downvol} },
	{ 0,            		XF86XK_AudioRaiseVolume,    spawn,          {.v = upvol}  },
	{ 0,            		XF86XK_AudioMute,           spawn,          {.v = mutevol} },

	/* backlight */
	{ 0,				XF86XK_MonBrightnessUp,     spawn,	    {.v = brightnessup} },
	{ 0, 				XF86XK_MonBrightnessDown,   spawn,          {.v = brightnessdown} },

	/* media keys */
	{ 0, 				XF86XK_AudioPrev,	    spawn,	    {.v = prev} },
	{ 0,				XF86XK_AudioNext,	    spawn,	    {.v = next} },
	{ 0,				XF86XK_AudioPlay,	    spawn,	    {.v = toggle} },

	/* pcmanfm */
	{ MODKEY,			XK_e,			    spawn,	    {.v = pcmanfm} },

	/* edge */
	{ MODKEY,			XK_b,			    spawn,	    {.v = edge} },

	/* screenshot (region) */
	{ MODKEY|ShiftMask,		XK_s,			    spawn,	    {.v = ss_region} },

	/* screenshot (window) */
	{ ShiftMask,			XK_Print,		    spawn,	    {.v = ss_window} },

	/* screenshot (normal) */
	{ 0,				XK_Print,		    spawn,	    {.v = ss_normal} },

	/* lock */
	{ MODKEY,			XK_c,			    spawn,	    {.v = lock} },

	/* lock and suspend */
	{ MODKEY|ShiftMask,		XK_c,			    spawn,	    {.v = suspend} },

	/* synapse */
	{ MODKEY,			XK_s,			    spawn,	    {.v = synapse} },

    /* ---------------- other ---------------- */
	{ MODKEY,                       XK_0,       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
	// { MODKEY,                       XK_Tab,     view,           {0} },
	// { MODKEY,                       XK_Return,  zoom,           {0} },

    /* -------------- tag keys  -------------- */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

    /* -------------- quit dwm  -------------- */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
};


/* ---------- button definitions --------- */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY|ControlMask, Button1,    placemouse,     {.i = 2} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      dragmfact,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
