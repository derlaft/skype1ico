skype1ico
=========

Skype icon wrapper for linux.

A very simple LD_PRELOAD wrapper that replaces original skype icons with your own ones.

Feel free to commit new icon themes!

Usage
=====

Just run skype from included .desktop file. Otherwise you can run it manually:

    LD_PRELOAD=/usr/lib/libskype1ico.so skype

Themes
=====

By default, skype1ico checks the following directories for themes:

  * ``$HOME/.local/share/skype1ico/``
  * ``/usr/share/skype1ico/``
  * ``/usr/local/share/skype1ico``

Theme name is set up in this priority:

  * ``SKYPE1ICO_THEME`` variable
  * system icon theme name
  * ``default``

If no theme can be accessed, skype will fall back to default icons. For futher informating about themes please check out ``KFaenza/themerc`` theme configuration file.
