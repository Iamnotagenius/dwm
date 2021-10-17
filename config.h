/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;   	/* 0: systray in the right corner, >0: systray on left of status text */
static unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "iosevka:size=14", "fontawesome:size=14" };
static const char dmenufont[]       = "iosevka:size=14";
static const char dmenulines[]      = "15";
static const char col_bg_dark[]     = "#2d2d2d";
static const char col_bg_light[]    = "#cc99cc";
static const char col_fg_dark[]     = "#2d2d2d";
static const char col_fg_light[]    = "#d3d0c8";


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg_light, col_bg_dark, col_bg_dark },
	[SchemeSel]  = { col_fg_dark, col_bg_light,  col_bg_light  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    	  		instance    title       tags mask     isfloating 	canfocus  monitor */
	{ "Qemu-system-x86_64",     			NULL,       NULL,       1 << 6,       0, 			1,        -1 },
	{ "qutebrowser",		NULL,       NULL,       1 << 8,       0, 			1,        -1 },
	{ "Tor Browser",		NULL,       NULL,       1 << 8,       0,       		1,     	  -1 },
	{ "LibreWolf",			NULL,       NULL,       1 << 8,       0,          	1,		  -1 },
	{ "firefox",  			NULL,       NULL,       1 << 8,       0,			1,        -1 },
	{ "Zathura",  			NULL,       NULL,       1 << 1,       0,			1,        -1 },
	{ "discord",  			NULL,       NULL,       1 << 3,       0,			1,         1 },
	{ "TelegramDesktop",	NULL,       NULL,       1 << 3,       0,			1,         1 },
	{ "Steam",      		NULL,       NULL,       1 << 7,       0,			1,         0 },
	{ "mpv", 	     		NULL,       NULL,       1 << 4,       0,			1,         0 },
	{ "Code", 	     		NULL,       NULL,       1 << 2,       0,			1,        -1 },
	{ "kube", 	     		NULL,       NULL,       1 << 5,       0,			1,        -1 },
	{ "Gnubiff", 	   		NULL,       "Popup",    0, 	      	  1,			0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "< >",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-l", dmenulines, "-fn", dmenufont, "-nb", col_bg_dark, "-nf", col_fg_light, "-sb", col_bg_light, "-sf", col_fg_dark, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *flameshotcmd[]  = { "flameshot", "gui", NULL };
static const char *startgamecmd[]  = { "/home/iamnotagenius/scripts/startgame.sh", NULL };
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,  						XK_g,	   spawn,	   	   {.v = startgamecmd } },
	{ 0,  							XK_Print,  spawn,	   	   {.v = flameshotcmd } },
	{ MODKEY,						XK_p,	   spawn,	   	   {.v = dmenucmd } },
	{ MODKEY,		        		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,  			XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {-1} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_period, shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_slash,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_slash,  tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *dwmfifo = "/tmp/dwm.fifo";
static Command commands[] = {
	{ "dmenu",           spawn,          {.v = dmenucmd} },
	{ "term",            spawn,          {.v = termcmd} },
	{ "quit",            quit,           {0} },
	{ "togglebar",       togglebar,      {0} },
	{ "focusstack+",     focusstack,     {.i = +1} },
	{ "focusstack-",     focusstack,     {.i = -1} },
	{ "incnmaster+",     incnmaster,     {.i = +1} },
	{ "incnmaster-",     incnmaster,     {.i = -1} },
	{ "setmfact+",       setmfact,       {.f = +0.05} },
	{ "setmfact-",       setmfact,       {.f = -0.05} },
	{ "zoom",            zoom,           {0} },
	{ "view",            view,           {0} },
	{ "killclient",      killclient,     {0} },
	{ "setlayout-tiled", setlayout,      {.v = &layouts[0]} },
	{ "setlayout-float", setlayout,      {.v = &layouts[1]} },
	{ "setlayout-mono",  setlayout,      {.v = &layouts[2]} },
	{ "togglelayout",    setlayout,      {0} },
	{ "togglefloating",  togglefloating, {0} },
	{ "togglefullscr",   togglefullscr,  {0} },
	{ "viewall",         view,           {.ui = ~0} },
	{ "tag",             tag,            {.ui = ~0} },
	{ "focusmon+",       focusmon,       {.i = +1} },
	{ "focusmon-",       focusmon,       {.i = -1} },
	{ "tagmon+",         tagmon,         {.i = +1} },
	{ "tagmon-",         tagmon,         {.i = -1} },
	{ "view1",           view,           {.ui = 1 << 0} },
	{ "view2",           view,           {.ui = 1 << 1} },
	{ "view3",           view,           {.ui = 1 << 2} },
	{ "view4",           view,           {.ui = 1 << 3} },
	{ "view5",           view,           {.ui = 1 << 4} },
	{ "view6",           view,           {.ui = 1 << 5} },
	{ "view7",           view,           {.ui = 1 << 6} },
	{ "view8",           view,           {.ui = 1 << 7} },
	{ "view9",           view,           {.ui = 1 << 8} },
	{ "toggleview1",     toggleview,     {.ui = 1 << 0} },
	{ "toggleview2",     toggleview,     {.ui = 1 << 1} },
	{ "toggleview3",     toggleview,     {.ui = 1 << 2} },
	{ "toggleview4",     toggleview,     {.ui = 1 << 3} },
	{ "toggleview5",     toggleview,     {.ui = 1 << 4} },
	{ "toggleview6",     toggleview,     {.ui = 1 << 5} },
	{ "toggleview7",     toggleview,     {.ui = 1 << 6} },
	{ "toggleview8",     toggleview,     {.ui = 1 << 7} },
	{ "toggleview9",     toggleview,     {.ui = 1 << 8} },
	{ "tag1",            tag,            {.ui = 1 << 0} },
	{ "tag2",            tag,            {.ui = 1 << 1} },
	{ "tag3",            tag,            {.ui = 1 << 2} },
	{ "tag4",            tag,            {.ui = 1 << 3} },
	{ "tag5",            tag,            {.ui = 1 << 4} },
	{ "tag6",            tag,            {.ui = 1 << 5} },
	{ "tag7",            tag,            {.ui = 1 << 6} },
	{ "tag8",            tag,            {.ui = 1 << 7} },
	{ "tag9",            tag,            {.ui = 1 << 8} },
	{ "toggletag1",      toggletag,      {.ui = 1 << 0} },
	{ "toggletag2",      toggletag,      {.ui = 1 << 1} },
	{ "toggletag3",      toggletag,      {.ui = 1 << 2} },
	{ "toggletag4",      toggletag,      {.ui = 1 << 3} },
	{ "toggletag5",      toggletag,      {.ui = 1 << 4} },
	{ "toggletag6",      toggletag,      {.ui = 1 << 5} },
	{ "toggletag7",      toggletag,      {.ui = 1 << 6} },
	{ "toggletag8",      toggletag,      {.ui = 1 << 7} },
	{ "toggletag9",      toggletag,      {.ui = 1 << 8} },
};
