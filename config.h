/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static int smartgaps      	    = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "Jetbrains Mono:size=11" };
static const char dmenufont[]       = "Jetbrains Mono:size=11";

#include "/home/aymeric/.cache/wal/colors-wal-dwm.h"

//static const char col_gray1[]       = "#222222";
//static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#bd93f9"; my ancient color for bar
//static const char col_gray3[]       = "#007abd"; //new color for bar
//static const char col_gray4[]       = "#888888";
//static const char col_cyan[]        = "#222222";
static const unsigned int baralpha = 0xd0;
//static const unsigned int baralpha = OPAQUE;
static const unsigned int borderalpha = 0xd0;

//static const char *colors[][3]      = {
	/*               fg         bg         border   */
//	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
//};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6"/*, "7", "8", "9" */};
static const char *tags[] = { "α", "β", "γ", "δ", "ε", "ζ"/*, "η", "θ", "ι"*/};
static const char *alttags[] = { "α.", "β.", "γ.", "δ.", "ε.", "ζ." };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define XF86AudioRaiseVolume 0x1008ff13
#define XF86AudioLowerVolume 0x1008ff11
#define XF86AudioMute 0x1008ff12
#define XF86MonBrightnessUp 0x1008ff02
#define XF86MonBrightnessDown 0x1008ff03
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = {"dmenu_run", "-fn",dmenufont , "-nb", "$color0", "-nf", "$color15", "-sb", "$color1", "-sf", "$color15"};
static const char *roficmd[] = {"rofi", "-no-lazy-grab", "-show", "run", "-modi", "run,drun,window", "-theme", "/home/aymeric/.config/rofi/rofi.rasi"};
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *dmenustart[] = { "/home/aymeric/scripts/dmen.sh", NULL };
static const char *slockcmd[] = { "/home/aymeric/scripts/powermenu.sh", NULL };
static const char *search[] = { "search", NULL };
static const char *google[] = { "google", NULL };
//static const char *screenshotcmd[] = { "scrot", "-q", "100", "~/Screenshots", NULL };
static const char *screenshotzonecmd[] = { "screenshot", NULL };

static const char *brightnessupcmd[] = { "brightnessctl", "set", "5%+", NULL };
static const char *brightnessdowncmd[] = { "brightnessctl", "set", "5%-", NULL };
static const char *volumeraisecmd[] = { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char *volumelowercmd[] = { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *volumetogglecmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
//	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY,             					XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,             					XK_m,	     spawn,          {.v = browsercmd } },
	{ MODKEY,             					XK_s,	     spawn,          {.v = search } },
	{ MODKEY,             					XK_g,	     spawn,          {.v = google } },
	{ MODKEY|ShiftMask,             XK_l,	     spawn,          {.v = slockcmd } },
	//{ MODKEY,             					XK_s,	     spawn,          {.v = screenshotcmd } },
	{ MODKEY|ShiftMask,             XK_s,	     spawn,          {.v = screenshotzonecmd } },

	{ 0,                         XF86MonBrightnessUp,  spawn,  {.v = brightnessupcmd } },
	{ 0,                     XF86MonBrightnessDown,    spawn,  {.v = brightnessdowncmd } },
	{ 0,                       XF86AudioRaiseVolume,   spawn,  {.v = volumeraisecmd } },
	{ 0,                       XF86AudioLowerVolume,   spawn,  {.v = volumelowercmd } },
	{ 0,                           	  XF86AudioMute,   spawn,  {.v = volumetogglecmd } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod1Mask,              XK_Return, zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              0x2d,      incrihgaps,     {.i = +1 } }, //6 for azerty
	{ MODKEY|Mod1Mask|ShiftMask,    0x2d,      incrihgaps,     {.i = -1 } }, //6 for azerty
	{ MODKEY|Mod1Mask,              0xe8,      incrivgaps,     {.i = +1 } }, //7 for azerty
	{ MODKEY|Mod1Mask|ShiftMask,    0xe8,      incrivgaps,     {.i = -1 } }, //7 for azerty
	{ MODKEY|Mod1Mask,              0x5f,      incrohgaps,     {.i = +1 } }, //8 for azerty
	{ MODKEY|Mod1Mask|ShiftMask,    0x5f,      incrohgaps,     {.i = -1 } }, //8 for azerty
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              0xe0,      togglegaps,     {0} }, //0 for azerty
	{ MODKEY|Mod1Mask|ShiftMask,    0xe0,      defaultgaps,    {0} }, //0 for azerty
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,             					XK_f,      togglefullscr,  {0} },
	{ Mod1Mask,                     0x26,      setlayout,      {.v = &layouts[0]} },
	{ Mod1Mask,      	    			    0xe9,      setlayout,      {.v = &layouts[1]} },
	{ Mod1Mask,         	          0x22,      setlayout,      {.v = &layouts[2]} },
	{ Mod1Mask,											0x27,	  	 setlayout,	   {.v = &layouts[11]} },
	{ Mod1Mask,											0x28,	   	 setlayout,	   {.v = &layouts[4]} },
	{ Mod1Mask,											0x2d,	   	 setlayout,	   {.v = &layouts[5]} },
	{ Mod1Mask,											0xe8,	  	 setlayout,	   {.v = &layouts[6]} },
	{ Mod1Mask,											0x5f,		   setlayout,	   {.v = &layouts[7]} },
	{ Mod1Mask,											0xe7,	   	 setlayout,	   {.v = &layouts[8]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        0x26,                      0)
	TAGKEYS(                        0xe9,                      1)
	TAGKEYS(                        0x22,                      2)
	TAGKEYS(                        0x27,                      3)
	TAGKEYS(                        0x28,                      4)
	TAGKEYS(                        0x2d,                      5)
	TAGKEYS(                        0xe8,                      6)
	TAGKEYS(                        0x5f,                      7)
	TAGKEYS(                        0xe7,                      8)
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
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

