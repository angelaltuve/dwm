/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "librewolf"
#define STATUSBAR "dwmblocks"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int swterminheritfs    = 1;        /* 1 terminal inherits fullscreen on unswallow, 0 otherwise */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 10;        /* horizontal padding for statusbar */
static const int vertpadbar         = 10;        /* vertical padding for statusbar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = {  "JetBrainsMono Nerd Font:size=10:antialias=true:autohint=true" };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
		[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
		[SchemeSel]  = { selbgcolor,  selfgcolor,  selbordercolor  },
		/* for bar --> {text, background, null} */
		[SchemeStatus]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* status R */
		[SchemeTagsSel]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* tag L selected */
		[SchemeTagsNorm]  = { selbordercolor, normbgcolor,  normbgcolor  }, /* tag L unselected */
		[SchemeInfoSel]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* info M selected */
		[SchemeInfoNorm]  = { normfgcolor, normbgcolor,  normbgcolor  }, /* info M unselected */
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "100x25", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "eva", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ BROWSER,    NULL,       NULL,          1 << 2,      0,           0,         -1,         -1 },
	{ TERMCLASS,  NULL,       NULL,       	 0,           0,           1,          0,         -1 },
	{ NULL,       NULL,       "Event Tester", 0,          0,           0,          1,         -1 },
	{ TERMCLASS,  "floatterm", NULL,       	 0,           1,           1,          0,         -1 },
  { TERMCLASS,  "spterm",    NULL,       	 SPTAG(0),    1,           1,          0,         -1 },
  { TERMCLASS,  "spcalc",    NULL,       	 SPTAG(1),    1,           1,          0,         -1 },
  { "Telegram",    NULL,     NULL,         1 << 3,      0,           0,          0,         -1 },
  { "Chromium",    NULL,     NULL,         1 << 7,      0,           0,          0,         -1 },
  { "calibre",     NULL,     NULL,         1 << 8,      0,           0,          0,         -1 },
  { "libreoffice",  NULL,    NULL,         1 << 6,      0,           0,          0,         -1 },
  { "Gimp",        NULL,     NULL,         1 << 8,      0,           0,          0,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_v,     ACTION##stack, {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include "bulkill.c"
#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run -p Run: ") },
  { MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("passmenu -p Pass: ") },
	{ MODKEY,                       XK_Return, spawn,          SHCMD(TERMINAL) },
  { MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },
  { MODKEY|ShiftMask,             XK_Return,     togglescratch,          {.ui = 0} },
  { MODKEY,                       XK_apostrophe, togglescratch,          {.ui = 1} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_Left,   shiftview,      {.i = -1 } },
  { MODKEY,                       XK_Right,  shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } }, /* all */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } }, /* inner */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } }, /* outer */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } }, /* inner horiz */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } }, /* inner vert */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } }, /* outer horiz */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } }, /* outer vert */
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
  { MODKEY|ControlMask,           XK_q,      bulkill,        {.ui = 1} },  // kill unselect
  { MODKEY|ShiftMask|ControlMask, XK_q,      bulkill,        {.ui = 2} },  // killall
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,		        XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,            			XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_x,	   togglescratch,  {.ui = 2 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,        {0} },
  { MODKEY|ShiftMask,             XK_r,      quit,           {1} },
  #define WPCTL(cmd, arg) SHCMD("wpctl " cmd " @DEFAULT_AUDIO_SINK@ " arg "; kill -44 $(pidof dwmblocks)")
	{ 0,                            XF86XK_AudioMute,          spawn,       WPCTL("set-mute", "toggle") },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,       WPCTL("set-volume --limit=1.0", "3%+") },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,       WPCTL("set-volume --limit=1.0", "3%-") },
	{ 0,				                    XF86XK_MonBrightnessUp,    spawn,	      SHCMD("xbacklight -inc 15")},
	{ 0,				                    XF86XK_MonBrightnessDown,  spawn,	      SHCMD("xbacklight -dec 15")},
  { MODKEY|ShiftMask,             XK_p,                      spawn,       SHCMD("mpc pause; pauseallmpv") },
  { 0,                            XF86XK_AudioPrev,          spawn,       SHCMD("mpc prev") },
	{ 0,                            XF86XK_AudioNext,          spawn,       SHCMD("mpc next") },
	{ 0,                            XF86XK_AudioPause,         spawn,       SHCMD("mpc pause") },
	{ 0,                            XF86XK_AudioPlay,          spawn,       SHCMD("mpc play") },
	{ 0,                            XF86XK_AudioStop,          spawn,       SHCMD("mpc stop") },
  { 0,                            XF86XK_TouchpadToggle,     spawn,       SHCMD("touchpad_toggle") },
  { MODKEY|ShiftMask,		          XK_n,                      spawn,       SHCMD(TERMINAL " -e newsraft")},
	{ MODKEY,			                  XK_m,                      spawn,       SHCMD(TERMINAL " -e ncmpcpp") },
  { MODKEY|ShiftMask,             XK_w,                      spawn,       SHCMD(TERMINAL " -e nmtui; kill -38 $(pidof dwmblocks)")       },
  { MODKEY,			                  XK_e,                      spawn,       SHCMD(TERMINAL " -e neomutt; kill -46 $(pidof dwmblocks)") },
  { MODKEY|ShiftMask,			        XK_e,                      spawn,       SHCMD(TERMINAL " -e profanity") },
  { MODKEY,			                  XK_r,                      spawn,       SHCMD(TERMINAL " -e tmux new-session -s yazi yazi") },
  { MODKEY|ShiftMask,	XK_h,                                  spawn,       {.v = (const char*[]){ "st", "-e", "htop", NULL } } },
  { MODKEY,				                XK_v,                      spawn,       {.v = (const char*[]){ "cliphist", "sel", NULL } } },
	{ MODKEY,				                XK_c,                      spawn,       {.v = (const char*[]){ "cliphist", "add", NULL } } },
  { MODKEY|ShiftMask,		          XK_F8,                     spawn,       SHCMD("slock loginctl suspend -i") },
  { MODKEY,                       XK_n,                      spawn,       SHCMD("dmenu-noter") },
  { MODKEY,			                  XK_grave,                  spawn,	      SHCMD("dmenuunicode") },
  { MODKEY,			                  XK_F1,                     spawn,       SHCMD("otp") },
	{ MODKEY,			                  XK_F2,                     spawn,       SHCMD("wallpapermenu") },
  { MODKEY,			                  XK_F3,                     spawn,       SHCMD("displayselect") },
  { MODKEY,			                  XK_F4,                     spawn,       SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
  { MODKEY,                       XK_F5,                     xrdb,        {.v = NULL } },
  { MODKEY,			                  XK_F6,                     spawn,       SHCMD("torwrap") },
	{ MODKEY,			                  XK_F7,                     spawn,       SHCMD("td-toggle") },
	{ MODKEY,			                  XK_F8,                     spawn,       SHCMD("mailsync") },
	{ MODKEY,			                  XK_F9,                     spawn,       SHCMD("mounter") },
	{ MODKEY,			                  XK_F10,                    spawn,       SHCMD("unmounter") },
  { MODKEY,			                  XK_F11,                    spawn,       SHCMD(TERMINAL " -e htop") },
  { MODKEY,			                  XK_F12,                    spawn,       SHCMD("remaps") },
	{ 0,				                    XK_Print,                  spawn,       SHCMD("maimpick") },
	{ MODKEY,			                  XK_Print,                  spawn,       SHCMD("dmenurecord") },
	{ MODKEY,			                  XK_Delete,                 spawn,       SHCMD("dmenurecord kill") },
  { MODKEY,			                  XK_Insert,                 spawn,       SHCMD("bookmarks") },
  { MODKEY,			                  XK_p,                      spawn,       SHCMD("mpc toggle") },
	{ MODKEY|ShiftMask,		          XK_p,                      spawn,       SHCMD("mpc pause; pauseallmpv") },
	{ MODKEY,			                  XK_bracketleft,            spawn,       SHCMD("mpc seek -10") },
	{ MODKEY|ShiftMask,		          XK_bracketleft,            spawn,       SHCMD("mpc seek -60") },
	{ MODKEY,			                  XK_bracketright,           spawn,       SHCMD("mpc seek +10") },
	{ MODKEY|ShiftMask,		          XK_bracketright,           spawn,       SHCMD("mpc seek +60") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
  { ClkStatusText,        ShiftMask,      Button1,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/suckless/dwmblocks/config.h") },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        defaultgaps,    {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkClientWin,		      MODKEY,		      Button4,	      incrgaps,       {.i = +1} },
	{ ClkClientWin,		      MODKEY,		      Button5,	      incrgaps,       {.i = -1} },
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = -1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = +1 } },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
  { ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		        0,		          Button4,	      shiftview,      {.i = -1} },
	{ ClkTagBar,		        0,		          Button5,	      shiftview,      {.i = 1} },
	{ ClkRootWin,		        0,		          Button2,	      togglebar,      {0} },
};

