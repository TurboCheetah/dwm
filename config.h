/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {
    "Iosevka Nerd Font Mono:size=10:antialias=true:autohint:true",
    "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"};
static const char dmenufont[] =
    "Iosevka Nerd Font Mono:size=10:antialias=true:autohint:true";
static const char col_gray1[] = "#1d2021";
static const char col_gray2[] = "#3c3836";
static const char col_gray3[] = "#ebdbb2";
static const char col_gray4[] = "#282828";
static const char col_mauve[] = "#fabd2f";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_mauve, col_gray1, col_gray1},
    [SchemeSel] = {col_gray1, col_mauve, col_mauve},
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;

const char *spcmd0[] = {
  "ghostty", "+new-window",
  "--class=ooo.turbo.spterm",
  "--window-width=160", "--window-height=34",
  NULL
};

const char *spcmd1[] = {
  "ghostty", "+new-window",
  "--class=ooo.turbo.spfm",
  "--window-width=184", "--window-height=40",
  "-e", "ranger",
  NULL
};

const char *spcmd2[] = {
  "ghostty", "+new-window",
  "--class=ooo.turbo.spncmpcpp",
  "--window-width=184", "--window-height=40",
  "-e", "ncmpcpp",
  NULL
};

const char *spcmd3[] = {
  "ghostty", "+new-window",
  "--class=ooo.turbo.spjellyfin",
  "--window-width=184", "--window-height=40",
  "-e", "jellyfin-mpv-shim",
  NULL
};

const char *spcmd4[] = {"bitwarden", NULL};

static Sp scratchpads[] = {
  {"spterm", spcmd0}, {"spfm", spcmd1}, {"spncmpcpp", spcmd2},
  {"spjellyfin", spcmd3}, {"bitwarden", spcmd4},
};

/* tagging */
static const char *tags[] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"goofcord", NULL, NULL, 1 << 8, 0, 0},
    {"Element", NULL, NULL, 1 << 0, 0, 1},
    {"mpv", NULL, NULL, 0, 1, -1},
    /* { "ncmpcpp",  NULL,       NULL,       1 << 0,       0,            1 }, */
    {"Signal", NULL, NULL, 1 << 8, 0, 0},
    {"Steam", NULL, NULL, 1 << 1, 0, 0},
    {"steam_app_1172470", NULL, NULL, 0, 0, 0},
    {"scrcpy", NULL, NULL, 0, 1, -1},
    {"ooo.turbo.spterm", NULL, NULL, SPTAG(0), 1, -1},
    {"ooo.turbo.spfm", NULL, NULL, SPTAG(1), 1, -1},
    {"ooo.turbo.spncmpcpp", NULL, NULL, SPTAG(2), 1, -1},
    {"ooo.turbo.spjellyfin", NULL, NULL, SPTAG(3), 1, -1},
    // {"KeePassXC", NULL, NULL, SPTAG(4), 1, -1},
    {"Bitwarden", NULL, NULL, SPTAG(4), 1, -1},
};

/* layout(s) */
static const float mfact = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120; /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                        \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                         \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}}, \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},          \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                       \
  {                                                      \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
  }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",  dmenumon,  "-fn", dmenufont, "-nb", col_gray1, "-nf",
    col_gray3,   "-sb", col_mauve, "-sf", col_gray4, NULL};
static const char *termcmd[] = {"ghostty", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_space, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY | ControlMask, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_y, togglescratch, {.ui = 0}},
    {MODKEY, XK_u, togglescratch, {.ui = 1}},
    {MODKEY, XK_s, togglescratch, {.ui = 2}},
    {MODKEY, XK_o, togglescratch, {.ui = 3}},
    {MODKEY, XK_x, togglescratch, {.ui = 4}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    /* { ClkClientWin,         MODKEY,         Button1,        resizemouse, {0}
       }, */
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
