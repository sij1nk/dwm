/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "Alacritty",   NULL, NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define Super Mod4Mask
#define Alt   Mod1Mask
#define Shift ShiftMask
#define Ctrl  ControlMask
#define TAGKEYS(KEY,TAG) \
	{ Super,            KEY,      view,           {.ui = 1 << TAG} }, \
	{ Super|Ctrl,       KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Super|Shift,      KEY,      tag,            {.ui = 1 << TAG} }, \
	{ Super|Ctrl|Shift, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ Super|Alt,        KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ Super|Alt|Shift,  KEY,      tagprevmon,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ Super,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ Super,                       XK_space,  spawn,          {.v = termcmd } },
	{ Super,                       XK_b,      togglebar,      {0} },
	{ Alt,                         XK_Tab,    focusstack,     {.i = +1 } },
	{ Alt|Shift,                   XK_Tab,    focusstack,     {.i = -1 } },
	{ Super,                       XK_i,      incnmaster,     {.i = +1 } },
	{ Super,                       XK_d,      incnmaster,     {.i = -1 } },
	{ Super,                       XK_h,      setmfact,       {.f = -0.05} },
	{ Super,                       XK_l,      setmfact,       {.f = +0.05} },
	{ Super,                       XK_Return, zoom,           {0} },
	{ Super,                       XK_Tab,    view,           {0} },
	{ Super,                       XK_q,      killclient,     {0} },
	{ Super|Ctrl,                  XK_t,      setlayout,      {.v = &layouts[0]} },
	{ Super|Ctrl,                  XK_f,      setlayout,      {.v = &layouts[1]} },
	{ Super|Ctrl,                  XK_m,      setlayout,      {.v = &layouts[2]} },
	{ Super|Ctrl,                  XK_space,  setlayout,      {0} },
	{ Super|Shift,                 XK_space,  togglefloating, {0} },
	{ Super|Shift,                 XK_f,      togglefullscr,  {0} },
	{ Super,                       XK_0,      view,           {.ui = ~0 } },
	{ Super|Shift,                 XK_0,      tag,            {.ui = ~0 } },
	{ Super,                       XK_comma,  focusmon,       {.i = -1 } },
	{ Super,                       XK_period, focusmon,       {.i = +1 } },
	{ Super|Shift,                 XK_comma,  tagmon,         {.i = -1 } },
	{ Super|Shift,                 XK_period, tagmon,         {.i = +1 } },
	{ Super,                       XK_minus,  setgaps,        {.i = -5 } },
	{ Super,                       XK_equal,  setgaps,        {.i = +5 } },
	{ Super|Shift,                 XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ Super|Shift,                 XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                       XK_1,                      0)
	TAGKEYS(                       XK_2,                      1)
	TAGKEYS(                       XK_3,                      2)
	TAGKEYS(                       XK_4,                      3)
	TAGKEYS(                       XK_5,                      4)
	TAGKEYS(                       XK_6,                      5)
	TAGKEYS(                       XK_7,                      6)
	TAGKEYS(                       XK_8,                      7)
	TAGKEYS(                       XK_9,                      8)
	{ Super|Shift,                 XK_Escape,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask     button          function        argument */
	{ ClkLtSymbol,          0,             Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,             Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,             Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         Super,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         Super,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         Super,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,             Button1,        view,           {0} },
	{ ClkTagBar,            0,             Button3,        toggleview,     {0} },
	{ ClkTagBar,            Super,         Button1,        tag,            {0} },
	{ ClkTagBar,            Super,         Button3,        toggletag,      {0} },
};
