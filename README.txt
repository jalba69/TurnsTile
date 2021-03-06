

  --TurnsTile 0.3.2--

      A mosaic and palette effects plugin for Avisynth 2.5.

    http://www.gyroshot.com/turnstile.htm
    robert.martens@gmail.com
    @ItEndsWithTens


  --Usage--

    TurnsTile(clip c, clip "tilesheet", int "tilew", int "tileh", int "res",
              int "mode", string "levels", int "lotile", int "hitile",
              bool "interlaced")

    c   clip

        The input clip, which can be RGB32, RGB24, YUY2, or YV12.

    tilesheet   clip

        Optional; if supplied, tiles will be pulled from this clip, which must
      be in the same colorspace as 'c'. Your tilesheet can be a still image or a
      video. In the latter case, tiles for a given frame of 'c' will be clipped
      from the corresponding frame of 'tilesheet'.

        The tiles are numbered left to right, then top to bottom. Using the
      sheets I've provided as examples, with 16x16 pixel tiles in a 256x256
      pixel image, the top left tile is number 0, top right is 15, bottom left
      is 240, and bottom right is 255. Design your own custom images
      accordingly, with dark tones at the top left fading up to lighter ones at
      the bottom right (first left to right across a row, then top to bottom one
      row at a time).

    tilew, tileh    int, default largest size <= 16x16 that fits your input

        If your tiles aren't sixteen by sixteen, define your custom values here.
      Each must be a factor of the respective clip dimension.

        For reference, the tiles in Dwarf Fortress' modified CP437, my personal
      favorite tileset, are 10x12 (that's for curses_800x600, the game also
      comes with a 16x16 version). Download from http://www.bay12games.com

    res   int, default 8

        This acts as the effective bit depth of your output. The range of
      possible output values is broken up into 2 ** res steps, and each tile
      index or pixel component is rounded accordingly. This is quite an
      effective technique for RGB footage, but thanks to the way color is
      represented in YUV spaces, you won't be able to lower this too much with
      YUY2 or YV12 input before things begin to look strange.

    mode    integer, default 0

        Only works when tilesheet is supplied. This option chooses the component
      that will serve as the tile index for a given tile. The possible values
      are as follows:

        0:
          RGB:   Average of red, green, and blue values
          YUY2:  Average of Y1 and Y2 in the current pixel pair
          YV12:  Average of all four Y values in the 2x2 block

        1:
          RGB:   Blue
          YUY2:  Y1
          YV12:  Top left

        2:
          RGB:   Green
          YUY2:  U
          YV12:  Top right

        3:
          RGB:   Red
          YUY2:  Y2
          YV12:  Bottom left

        4:
          RGB32: Alpha
          RGB24: N/A
          YUY2:  V
          YV12:  Bottom right

        5:
          RGB32: N/A
          RGB24: N/A
          YUY2:  N/A
          YV12:  U

        6:
          RGB32: N/A
          RGB24: N/A
          YUY2:  N/A
          YV12:  V

    levels    string, "pc" or "tv", default "pc"

        In order to scale the tile index or pixel component, I first need to
      know the range of input values. Technically TV levels still fall within
      the possible range of 0-255, but if you'd like to map TV black and white
      to the lowest and highest tiles in your tilesheet, respectively, use "tv"
      instead.

    lotile, hitile    default 0 and tilecount - 1

        A quick way to limit the tile selection to a given portion of your
      tilesheet; if you have a sheet with an odd number of tiles, for example,
      and some spaces are blank, or if you just want to use a smaller range of
      values without having to rebuild your tilesheet by hand, use these. If you
      don't use a tilesheet, these will instead control the maximum and minimum
      component values.

    interlaced    bool, default false

        Enable for interlaced input. For those unaware, "interlaced" and "field
      based" are not the same thing. If a clip is field based, it's more than
      likely interlaced, but the reverse isn't true, and there's currently no
      completely fool proof way to auto-detect interlaced input. The simplest
      way for me to properly process such footage is to rely on user knowledge,
      so I'm sorry to say you'll need to turn this on if it applies to you.

        If your input is already field based, and you turn this on, it'll be
      weaved on the way out, so be aware.

    ----

    CLUTer(clip c, clip palette, int "paletteframe", bool "interlaced")

    c    clip
    
        No special restrictions, beyond ensuring that this clip's colorspace
      matches that of your palette. RGB32, RGB24, YUY2, and YV12 are supported.

    palette    clip

        Must be same colorspace as input clip. Progressive chroma siting is
      assumed for YV12 palettes; although 'c' will be treated as interlaced if
      the appropriate option is enabled, the palette itself will always be read
      as if progressive.

        CAUTION! It is very, very easy to dramatically slow down the operation
      of CLUTer, to such a degree that it may appear to be frozen. The short
      version: stick with, let's say, 100 or fewer unique colors per palette, or
      you're in for a long wait. If you want to use an image as your palette,
      run it through TurnsTile first, with big tiles and/or a lowered 'res'.

        The long version: a lookup table is constructed when this plugin is
      loaded, so that the nearest color to a given value in the input can be
      retrieved from a list instead of computed for every pixel in every frame.
      This lets the plugin work much faster once it's ready, but if you pass in
      a palette that has too many colors, you'll end up waiting ages for the LUT
      to be generated. I tried using a small JPEG image, that had barely over
      54,000 unique colors in it, and sat for half an hour before giving up.
      Searching through 54,000 possibilities, and doing that 16,777,216 times,
      has its price. If you're a masochist, go right ahead, but don't say I
      didn't warn you. As always, if I ever find a smarter approach I'll
      improve this.

    paletteframe    int, default 0

        Only one frame is used from any clip you pass in as your palette, so if
      you don't want to use the colors of frame 0, set paletteframe accordingly.

    interlaced    bool, default false

        As explained above, the terms "field based" and "interlaced" are not
      necessarily synonymous. Reading the proper luma values for a given chroma
      sample requires that I know the nature of your footage, and a simple
      boolean function parameter is the most reliable way I know of to achieve
      that. Only important for YV12 at the moment, since it's the only 2.5.x
      colorspace that features vertical chroma subsampling.


    --Extras--

      I've released TurnsTile under the GPLv2; you'll find a copy of the license
    in the file COPYING, and what little source code there is in the src folder.

      In the extras directory, I've included a set of tilesheets to serve as a
    jumping off point for your own experimentation, along with the AviSynth
    script I used to generate them. You'll need Gavino's GScript to make it work
    ( http://forum.doom9.org/showthread.php?t=147846 ), but there are no other
    requirements. This tilesheet generator isn't very flexible, and could
    certainly stand to be improved, so if anyone has any ideas I'd love to hear
    them.

      CGApalette.avs was introduced along with CLUTer() in version 0.3.0, and as
    stated in the comments is meant to be loaded by AVISource as a sample
    palette for that function. Open up the script to find more details.

      Finally, also in the extras folder is a copy of the script version of
    TurnsTile 0.1.0. It requires GScript, along with GRunT
    ( http://forum.doom9.org/showthread.php?t=139337 ), also from Gavino, and
    doesn't run very quickly, to say the least. That barely measurable speed
    was the motivation for me to try developing an actual plugin, and I only
    include the script here for educational purposes. Please don't think I
    advocate its use in the real world.


    --Changes--

        0.3.2 - April 10th, 2013

                    -Fix tilesheet processing for interlaced clips

        0.3.1 - September 21st, 2011

                    -Recompiled to remove SSE/SSE2 requirement and Visual C++
                    CRT dependency

        0.3.0 - May 6th, 2011

                    -Corrected braindead inclusion guard mistake in TurnsTile.h
                    -Added YV12 support
                    -Added CLUTer palettizing function
                    -Fixed 'res' option to round values correctly
                    -Expanded lotile/hitile operation to clip-only mode

        0.2.1 - March 12th, 2011

                    -Updated auto calc for tile size, now properly accounts for
                    minimum YUY2 width

        0.2.0 - March 10th, 2011

                    -Changed 'res' behavior to simulate bit depth adjustment
                    -Added 'levels', 'lotile', 'hitile'
                    -Added auto calculation of default tile size

        0.1.0 - December 24th, 2010

                    -Initial release
