# Description

Avisynth plugin. Load a font file (.ttf/.otf/.ttc) for further use, such as TextSub Subtitle etc.

# Usage

```
LoadPlugin("LajiLoadFont.dll")
LajiLoadFont("SomeFonts.ttc")

# Font loaded

TextSub("mdzz.ass")
Subtitle("mdzz", font="SomeFonts-Bold")

```
