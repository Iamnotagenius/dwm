/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int scalepreview       = 4;        /* tag preview scaling */


static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;   	/* 0: systray in the right corner, >0: systray on left of status text */
static unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int extrabar           = 0;        /* 0 means no extra bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka Nerd Font:size=12:antialias=true" };
static const char dmenufont[]       = "iosevka:size=14";
static const char dmenulines[]      = "15";
static const char col_bg_dark[]     = "#2d2d2d";
static const char col_bg_hover[]    = "#3d383d";
static const char col_bg_light[]    = "#cc99cc";
static const char col_fg_dark[]     = "#2d2d2d";
static const char col_fg_light[]    = "#d3d0c8";


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg_light, col_bg_dark, col_bg_dark },
	[SchemeSel]  = { col_fg_dark, col_bg_light,  col_bg_light  },
	[SchemeTabActive]  = { col_fg_light, col_bg_dark,  col_bg_dark },
	[SchemeTabInactive]  = { col_fg_light,  col_bg_dark,  col_bg_dark },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "磊", "", "", "" };
static const char *defaulttagapps[] = { 
    "alacritty",
    "zathura",
    "code",
    "/opt/discord/Discord",
    "ytplay",
    "start_vm",
    "steam",
    "browsers",
};
/* Bartabgroups properties */
#define BARTAB_BORDERS 0       // 0 = off, 1 = on
#define BARTAB_BOTTOMBORDER 0  // 0 = off, 1 = on
#define BARTAB_TAGSINDICATOR 0 // 0 = off, 1 = on if >1 client/view tag, 2 = always on
#define BARTAB_TAGSPX 7        // # pixels for tag grid boxes
#define BARTAB_TAGSROWS 2      // # rows in tag grid (9 tags, e.g. 3x3)
static void (*bartabmonfns[])(Monitor *) = { monocle /* , customlayoutfn */ };
static void (*bartabfloatfns[])(Monitor *) = { NULL /* , customlayoutfn */ };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class    	  		instance    title           tags mask   isfloating 	canfocus    isterminal  noswallow   monitor */
	{ "Alacritty",    		NULL,       NULL,           0,          0,			1,          1,          0,          -1 },
	{ "Qemu-system-x86_64", NULL,       NULL,           1 << 5,     0, 			1,          0,          0,          -1 },
	{ "qutebrowser",		NULL,       NULL,           1 << 7,     0, 			1,          0,          0,          -1 },
	{ "Chromium",			NULL,       NULL,           1 << 7,     0, 			1,          0,          0,          -1 },
	{ "Tor Browser",		NULL,       NULL,           1 << 7,     0,       	1,          0,          0,    	    -1 },
	{ "LibreWolf",			NULL,       NULL,           1 << 7,     0,         	1,	        0,	        0,          -1 },
	{ "firefox",  			NULL,       NULL,           1 << 7,     0,			1,          0,          0,          -1 },
	{ "Zathura",  			NULL,       NULL,           1 << 1,     0,			1,          0,          0,          -1 },
	{ "Zathura",  			NULL,       NULL,           1 << 1,     0,			1,          0,          0,          -1 },
	{ "discord",  			NULL,       NULL,           1 << 3,     0,			1,          0,          0,           1 },
	{ "TelegramDesktop",	NULL,       NULL,           1 << 3,     0,			1,          0,          0,           1 },
	{ "Steam",      		NULL,       NULL,           1 << 6,     0,			1,          0,          0,           0 },
	{ "mpv", 	     		NULL,       NULL,           0,          0,			1,          0,          0,           0 },
	{ "code-oss",    		NULL,       NULL,           0,          0,			1,          0,          0,          -1 },
	{ NULL,                 NULL,       "Event Tester", 0,          0,          1,          0,          1,          -1 }, /* xev */
	{ "tabbed",             NULL,       NULL,           0,          0,          1,          0,          1,          -1 },
	{ "Dragon-drop",        NULL,       NULL,           1 << 3,     1,          1,          0,          1,          -1 },
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
	{ "|||",      col },
	{ "[D]",      deck },
	{ "DD",       doubledeck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      arg_spawndefault,{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|Mod1Mask,  KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-l", dmenulines, "-fn", dmenufont, "-nb", col_bg_dark, "-nf", col_fg_light, "-sb", col_bg_light, "-sf", col_fg_dark, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *layoutmenu_cmd = "layoutmenu";
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,						XK_p,	   spawn,	   	   {.v = dmenucmd } },
	{ MODKEY,		        		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		        XK_c,      killfocused,    {0} },
	{ MODKEY,                       XK_s,      spawndefault,   {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_b,      toggleextrabar, {0} },
    { MODKEY|ShiftMask,             XK_b,      toggleextrabar, {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_n,      focusmaster,    {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,  			XK_Return, zoomfocused,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[9]} },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkLtSymbol,          MODKEY,         Button1,        incnmaster,     { .i = +1 } },
    { ClkLtSymbol,          MODKEY,         Button3,        incnmaster,     { .i = -1 } },
    { ClkLtSymbol,          MODKEY,         Button2,        setnmaster,     { .i = 1 } },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button2,        arg_spawndefault,{0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* Bar tab click events */
static void(*bartabfuncs[])(Monitor *, Client *, int, int, int, int) = {
    [Button1] = bartabclick, /* left click */
    [Button2] = bartabkill, /* middle click */
    [Button3] = bartabzoom /* right click */
};

