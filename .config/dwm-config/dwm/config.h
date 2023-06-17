/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 20;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace 9:size=9"};
static const char dmenufont[]       = "monospace 9:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#625655";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#513439";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_cyan  },
};



/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

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
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
//#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *web[]  = { "brave", NULL };
static const char *discord[]  = { "discord", NULL };
static const char *pomotroid[]  = { "pomotroid", "--no-sandbox", NULL };
static const char *exitmenu[]  = { "pmenu", NULL };
static const char *rangercmd[]  = { "st", "ranger", NULL };
static const char *redshifton[]  = { "redshift-on", NULL };
static const char *redshiftoff[]  = { "redshift-off", NULL };
static const char *vscode[]  = { "code", NULL };
static const char *filemanager[]  = { "nemo", NULL };
static const char *pavucontrol[]  = { "pavucontrol", NULL };

// AUDIO use pavucontrol GUI / install pipewire-pulse (CHECK xinitrc)
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle",  NULL };
//static const char *upvol[]	 = { "pamixer", "--allow-boost", "-i", "5"};
//static const char *downvol[] = { "pamixer", "--allow-boost", "-d", "5"};
//static const char *mutevol[] = { "pamixer", "-t" };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_e,	   spawn,          {.v = filemanager } },
	{ MODKEY,  	                XK_Delete, spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_Down,   spawn,	   {.v = downvol } },
	{ MODKEY,                       XK_Up,	   spawn,          {.v = upvol   } },
	{ MODKEY,                       XK_r,      spawn,          {.v = rangercmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = web } },
	{ MODKEY,                       XK_d,      spawn,          {.v = discord } },
	{ MODKEY,                       XK_p,      spawn,          {.v = pomotroid } },
	{ MODKEY,                       XK_v,      spawn,          {.v = pavucontrol } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },
	{ MODKEY,			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,			XK_t,      spawn,          {.v = redshifton } },
	{ MODKEY|ShiftMask,	        XK_t,      spawn,          {.v = redshiftoff } },
	{ MODKEY,	        	XK_c,      spawn,          {.v = vscode } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_m,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_m,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             		XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask,           XK_j,      viewtoright,    {0} },
	{ MODKEY|ControlMask,           XK_k,      viewtoleft,     {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_j,      tagtoright,     {0} },
	{ MODKEY|ShiftMask|ControlMask, XK_k,      tagtoleft,      {0} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	// { MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("pmenu") },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = exitmenu } },
	//{ MODKEY|ControlMask,           XK_q,      quit,           {0} }, //replaced above
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