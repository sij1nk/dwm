### dwm - dynamic window manager

Official repo: <https://git.suckless.org/dwm/>

This is my heavily patched build of dwm. Most of the patches are publicly
available on the suckless site, but I also had to chip in here and there.

## Key features, not present in the "official" build:
 - Customizable gaps between windows
 - Pango markup for laying out and styling text on the status bar
 - Three column layout with fullgaps support
 - Xresources support and the ability to reload resources on at runtime
 - Send commands to dwm to execute through dwmc ("fake signals")
 - Graphical programs launched from the terminal will temporarily "swallow" the
   inoperable terminal window

My choice of status bar is torrinfail's dwmblocks. It is very lightweight and flexible enough for my modest use cases. My build is pretty much the same as the stock version so it's not included. The statusbar modules can be found in my [dotfiles](https://github.com/anguaive/dotfiles/tree/master/.local/bin/blocks).


## Patches:
 - [Actual fullscreen](https://dwm.suckless.org/patches/actualfullscreen): fullscreens the focused window. I rarely use it because
   most GUI programs already have such functionality.
 - [No title](https://dwm.suckless.org/patches/notitle): removes the window title from the status bar and frees up space for
   my status bar modules.
 - [Full gaps](https://dwm.suckless.org/patches/fullgaps): allows for gaps between windows. Sacrifices practicality for
   looks.
 - [Per tag](https://dwm.suckless.org/patches/pertag): instead of one global layout, each tag keeps track of its own
   layout.
 - [Hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags): frees up more status bar space.
 - [Swallow](https://dwm.suckless.org/patches/swallow): reduces clutter by hiding terminal windows that GUI programs were
   launched from.
 - [Tag other monitor](https://dwm.suckless.org/patches/tagothermonitor): improved relocation of windows between monitors. Doesn't
   see much use.
 - [Dwmc](https://dwm.suckless.org/patches/dwmc): allows me to control dwm through shell scripts. This is what makes the
   filmsy hack which I refer to as "static apps" possible, among other things.
 - [View on tag](https://dwm.suckless.org/patches/viewontag): follow a window to the tag it is being moved to. When moving
   windows around I typically want focus to stay on the window, so this makes
   sense.
 - [Pango](https://dwm.suckless.org/patches/pango): the markup support it offers is more refined and allows for more
   customizability options than the alternatives (like colorbar).
 - [Statuspadding](https://dwm.suckless.org/patches/statuspadding): vertical and horizontal padding for the status bar.
 - [Xresources](https://dwm.suckless.org/patches/resources): adds the ability to grab colors, fonts and other stuff from
   Xresources at startup, defeating the need to recompile dwm every time you
   mess with the config file. With dwmc and a bit of hacking I can signal to dwm
   to reload these resources at runtime.
 - [Attach aside and below](https://dwm.suckless.org/patches/attachasideandbelow): new windows are spawned on the bottom of the stack.
   The stock version of this patch appears to be flawed (?).
 - [Three column layout](https://dwm.suckless.org/patches/three-column): arrange clients in three columns with the middle one
   being the master. This function does not support gaps by default so I had to
   patch that in myself.

## My experiences:
  I was initially very confused about the need for config.def.h and the way I
  was supposed to handle conflicts between patches. I'm still not sure what's
  the best way to remove patches that were introduced in previous patches.

  What I eventually came up with is the following:
   - Keep config.h untracked and make sure patches only change config.def.h, not
     config.h. Only modifying config.def.h makes sure both config files are
     up-to-date and you won't run into trouble and lose your keybinds by
     accidentally deleting config.h or something.
   - For each patch I wanted to apply, I branched off from origin/master and
     applied the patch there. This allowed me to test the patch in isolation.
     If everything was fine then I'd rebase the branch onto my master branch to
     keep the commit history clean.
   - I resolved the merge conflicts by hand, without using any kind of fancy
     merge tool. Dwm patches are relatively small so I never ran into serious
     issues. Having the patch open on another split and taking a glance every
     now and then to see what to keep helps a lot.
   - Afterwards I'd fast forward my master branch to point to the newly
     implemented patch, then test again to make sure the patch doesn't introduce
     any unwanted behavior.
