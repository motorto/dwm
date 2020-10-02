/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 5; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"Iosevka:size=10"};
static const char dmenufont[] = "Iosevka:size=10";
static const char bg0[] = "#1d2021";
static const char bg1[] = "#282828";
static const char bg2[] = "#3c3836";
static const char fg0[] = "#ebdbb2";
static const char fg1[] = "#fbf1c7";
static const char black[] = "#000000";
static const char accent[] = "#689d6a";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {fg0, bg1, bg0},
    [SchemeSel] = {fg0, black, accent},
};

/* tagging */
static const char *tags[] = {"PRG", "WEB", "FILES", "COM", "MISC"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Firefox", NULL, NULL, 1 << 1, 0, -1},
    {"Firefox", "Toolkit", "Picture-in-Picture", 1 << 1, 1, -1},
    {NULL, NULL, "LibreOffice", 1 << 2, 0, -1},
    {NULL, "libreoffice", NULL, 1 << 2, 0, -1},
    {"zoom", "zoom", NULL, 1 << 3, 1, -1},
    {"Slack", NULL, NULL, 1 << 3, 0, -1},
    {"XTerm", "xterm", "newsboat", 1 << 3, 0, -1},
    {"XTerm", "xterm", "neomutt", 1 << 3, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon, "-i", "-fn", dmenufont,
                                 "-nb",       bg0,   "-nf",    fg0,   "-sb",
                                 accent,      "-sf", bg1,      NULL};
static const char *termcmd[] = {"xterm", NULL};
static const char *browser[] = {"firefox", NULL};
static const char *mail[] = {"xterm", "-e", "neomutt", NULL};
static const char *rss[] = {"xterm", "-e", "newsboat", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_space, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    //{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    //{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY | ShiftMask, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY | ShiftMask, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4)
    // My keys
    {MODKEY, XK_w, spawn, {.v = browser}},
    {MODKEY, XK_e, spawn, {.v = mail}},
    {MODKEY, XK_r, spawn, {.v = rss}},

    {0, XK_Print, spawn,
     SHCMD("maim -s /home/cerqueira/pic/print/$(date +%s).png")},

    {0, 0x1008ff12, spawn, SHCMD("pamixer -t")},
    {0, 0x1008ff13, spawn, SHCMD("pamixer -i 5")},
    {0, 0x1008ff11, spawn, SHCMD("pamixer -d 5")},
    {0, 0x1008ff02, spawn, SHCMD("light -A 5")},
    {0, 0x1008ff03, spawn, SHCMD("light -U 5")},
    {0, 0x1008ff14, spawn, SHCMD("playerctl play-pause")},
    {0, 0x1008ff15, spawn, SHCMD("playerctl stop")},
    {0, 0x1008ff16, spawn, SHCMD("playerctl previous")},
    {0, 0x1008ff17, spawn, SHCMD("playerctl next")},
    {MODKEY, XK_F12, spawn, SHCMD("powermenu.sh")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
