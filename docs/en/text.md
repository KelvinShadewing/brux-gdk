# <center>**Brux Scripting Reference Manual**</center>
## <center>Text</center>



&nbsp;

* <a name="drawtext"></a>**`drawText( font, x, y, text )`**

  Draws a string to the current render target using the selected `font`.

* <a name="newFont"></a>**`newFont( sprite, firstchar, threshold, monospace, kerning )`**

  Creates a bitmap font from a sprite. `firstchar` is usually best set to 33 when using a full ascii sheet. `threshold` is the alpha value used for determining the width of a character for fonts using partial transparency. `monospace` is whether or not the font is monospace, and is currently locked true by default. `kerning` is the space between images, and can be negative to make them closer together.

* <a name="chint"></a>**`chint( char )`**

  Returns the integer equivalent of `char`. Not to be confused with Squirrel's `string.tointeger()`, which attempts to turn a string with a number written out in it into an actual integer.

## Color Codes

Brux supports colorized text using its escape character, `~`. If you wish to render a tilde in your text, you should double it like so: `~~`. Color rendering is done by modulating the font sprite by a certain color. The supported color codes are as follows:

|||
|----|----|
| `~0` **<span style="color:white">█</span> White** | `~1` **<span style="color:#0000a8">█</span> Dark Blue** |
| `~2` **<span style="color:#00a800">█</span> Dark Green** | `~3` **<span style="color:#a80000">█</span> Dark Red** |
| `~4` **<span style="color:#006060">█</span> Shadewing Teal** | `~5` **<span style="color:#a800a8">█</span> Dark Purple** |
| `~6` **<span style="color:#f8a800">█</span> Gold** | `~7` **<span style="color:#808080">█</span> Gray** |
| `~8` **<span style="color:#505050">█</span> Dark Gray** | `~9` **<span style="color:#0000f8">█</span> Blue** |
| `~a` **<span style="color:#00f800">█</span> Green** | `~b` **<span style="color:#00f8f8">█</span> Aqua** |
| `~c` **<span style="color:#f80000">█</span> Red** | `~d` **<span style="color:#f800f8">█</span> Purple** |
| `~e` **<span style="color:#f8f800">█</span> Yellow** | `~f` **<span style="color:#000000">█</span> Black** |
| `~g` **<span style="color:#a8a8a8">█</span> Light Gray** | `~h` **<span style="color:#f88080">█</span> Light Red** |
| `~i` **<span style="color:#80f880">█</span> Light Green** | `~j` **<span style="color:#b0b0f8">█</span> Light Blue** |
| `~k` **<span style="color:#00d0d0">█</span> Light Teal** | `~l` **<span style="color:#f880f8">█</span> Light Purple** |
| `~m` **<span style="color:#f8f8a8">█</span> Light Yellow** | `~n` **<span style="color:#f8c870">█</span> Tan** |
| `~o` **<span style="color:#805010">█</span> Brown** | `~p` **<span style="color:#f868b0">█</span> Pink** |
| `~q` **<span style="color:#f8b8d0">█</span> Light Pink** | `~r` **<span style="color:#f84068">█</span> Dark Pink** |
| `~s` **<span style="color:#4880b8">█</span> Steel Blue** | `~t` **<span style="color:#00a0a0">█</span> Teal** |
| `~u` **<span style="color:#303030">█</span> Charcoal** | `~v` **<span style="color:#f0f0e0">█</span> Eggshell** |
| `~w` **<span style="color:#8080a0">█</span> Slate** | `~x` **<span style="color:#704838">█</span> Coffee** |
| `~y` **<span style="color:#80a080">█</span> Olive** | `~z` **<span style="color:#b02050">█</span> Rose** |

These color codes are case-insensitive. 