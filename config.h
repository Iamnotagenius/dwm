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
static const char *default_keymap   = "us,ru";
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
    /* class    	  		instance    title           tags mask   isfloating 	canfocus    isterminal  noswallow   monitor layout */
    { "Alacritty",    		NULL,       NULL,           0,          0,			1,          1,          0,          -1,     "us,ru" },
    { NULL,     		    NULL,       "Calc",         0,          1,			1,          0,          0,          -1,     "us,ru" },
    { "neovide",    		NULL,       NULL,           0,          0,			1,          0,          0,          -1,     "us,ru" },
    { "Qemu-system-x86_64", NULL,       NULL,           1 << 5,     0, 			1,          0,          0,          -1,     NULL },
    { "qutebrowser",		NULL,       NULL,           1 << 7,     0, 			1,          0,          0,          -1,     NULL },
    { "Chromium",			NULL,       NULL,           1 << 7,     0, 			1,          0,          0,          -1,     NULL },
    { "Brave-browser",		NULL,       NULL,           1 << 7,     0, 			1,          0,          0,          -1,     NULL },
    { "Tor Browser",		NULL,       NULL,           1 << 7,     0,       	1,          0,          0,    	    -1,     NULL },
    { "LibreWolf",			NULL,       NULL,           1 << 7,     0,         	1,	        0,	        0,          -1,     NULL },
    { "firefox",  			NULL,       NULL,           1 << 7,     0,			1,          0,          0,          -1,     NULL },
    { "Zathura",  			NULL,       NULL,           1 << 1,     0,			1,          0,          0,          -1,     NULL },
    { "Zathura",  			NULL,       NULL,           1 << 1,     0,			1,          0,          0,          -1,     NULL },
    { "discord",  			NULL,       NULL,           1 << 3,     0,			1,          0,          0,           1,     "ru,us" },
    { "TelegramDesktop",	NULL,       NULL,           1 << 3,     0,			1,          0,          0,           1,     "ru,us" },
    { "Steam",      		NULL,       NULL,           1 << 6,     0,			1,          0,          0,           0,     NULL },
    { "mpv", 	     		NULL,       NULL,           0,          0,			1,          0,          0,           0,     NULL },
    { "code-oss",    		NULL,       NULL,           0,          0,			1,          0,          0,          -1,     NULL },
    { NULL,                 NULL,       "Event Tester", 0,          0,          1,          0,          1,          -1,     NULL }, /* xev */
    { "tabbed",             NULL,       NULL,           0,          0,          1,          0,          1,          -1,     NULL },
    { "Dragon-drop",        NULL,       NULL,           1 << 3,     1,          1,          0,          1,          -1,     NULL },
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
static const char *dmenucmd[] = {
    "dmenu_run",
    "-m",
    dmenumon,
    "-l",
    dmenulines,
    "-fn",
    dmenufont,
    "-nb",
    col_bg_dark,
    "-nf",
    col_fg_light,
    "-sb",
    col_bg_light,
    "-sf",
    col_fg_dark,
    NULL
};
static const char *termcmd[]  = { "alacritty", NULL };
static const char *layoutmenu_cmd = "layoutmenu";
static Key keys[] = {
    /* modifier                     key             function        argument */
    { MODKEY,						33, /* p */	    spawn,	   	    {.v = dmenucmd } },
    { MODKEY,		        		36, /* Enter */ spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,		        54, /* c */     killfocused,    {0} },
    { MODKEY,                       39, /* s */     spawndefault,   {0} },
    { MODKEY,                       56, /* b */     togglebar,      {0} },
    { MODKEY,                       56,             toggleextrabar, {0} },
    { MODKEY|ShiftMask,             56,             toggleextrabar, {0} },
    { MODKEY,                       44, /* j */     focusstack,     {.i = +1 } },
    { MODKEY,                       45, /* k */     focusstack,     {.i = -1 } },
    { MODKEY,                       57, /* n */     focusmaster,    {0} },
    { MODKEY,                       31, /* i */     incnmaster,     {.i = +1 } },
    { MODKEY,                       40, /* d */     incnmaster,     {.i = -1 } },
    { MODKEY,                       43, /* h */     setmfact,       {.f = -0.05} },
    { MODKEY,                       46, /* l */     setmfact,       {.f = +0.05} },
    { MODKEY|ControlMask,  			36, /* Enter */ zoomfocused,    {0} },
    { MODKEY,                       23, /* Tab */   view,           {0} },
    { MODKEY,                       28, /* t */     setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       41, /* f */     setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       58, /* m */     setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       30, /* u */     setlayout,      {.v = &layouts[3]} },
    { MODKEY|ShiftMask,             30,             setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       54,             setlayout,      {.v = &layouts[5]} },
    { MODKEY,                       27, /* r */     setlayout,      {.v = &layouts[6]} },
    { MODKEY|ShiftMask,             27,             setlayout,      {.v = &layouts[7]} },
    { MODKEY,                       29, /* y */     setlayout,      {.v = &layouts[8]} },
    { MODKEY|ShiftMask,             29,             setlayout,      {.v = &layouts[9]} },
    { MODKEY,                       65, /* Space */ setlayout,      {0} },
    { MODKEY|ShiftMask,             65,             togglefloating, {-1} },
    { MODKEY|ShiftMask,             41,             togglefullscr,  {0} },
    { MODKEY,                       19, /* 0 */     view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             19,             tag,            {.ui = ~0 } },
    { MODKEY,                       59, /* , */     shiftview,      {.i = -1 } },
    { MODKEY,                       60, /* . */     shiftview,      {.i = +1 } },
    { MODKEY,                       61, /* / */     focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             61, /* / */     tagmon,         {.i = +1 } },
    TAGKEYS(                        10, /* 1 */                     0)
    TAGKEYS(                        11, /* 2 */                     1)
    TAGKEYS(                        12, /* 3 */                     2)
    TAGKEYS(                        13, /* 4 */                     3)
    TAGKEYS(                        14, /* 5 */                     4)
    TAGKEYS(                        15, /* 6 */                     5)
    TAGKEYS(                        16, /* 7 */                     6)
    TAGKEYS(                        17, /* 8 */                     7)
    { MODKEY|ShiftMask,             24, /* q */     quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function            argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,          {0} },
    { ClkLtSymbol,          0,              Button3,        layoutmenu,         {0} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,          {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating,     {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,        {0} },
    { ClkLtSymbol,          MODKEY,         Button1,        incnmaster,         { .i = +1 } },
    { ClkLtSymbol,          MODKEY,         Button3,        incnmaster,         { .i = -1 } },
    { ClkLtSymbol,          MODKEY,         Button2,        setnmaster,         { .i = 1 } },
    { ClkTagBar,            0,              Button1,        view,               {0} },
    { ClkTagBar,            0,              Button2,        arg_spawndefault,   {0} },
    { ClkTagBar,            0,              Button3,        toggleview,         {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,                {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,          {0} },
};

/* Bar tab click events */
static void(*bartabfuncs[])(Monitor *, Client *, int, int, int, int) = {
    [Button1] = bartabclick, /* left click */
    [Button2] = bartabkill, /* middle click */
    [Button3] = bartabzoom /* right click */
};

