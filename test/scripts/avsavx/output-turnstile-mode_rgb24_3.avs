# TurnsTile - Mode option produces expected result
# [output][turnstile][mode]
#
# Expected:
#
#   16x16 white frame, with the following component values for each pixel:
#     RGB: 255 255 255
#
# Rationale:
#
#   For RGB24, the "unique" argument to MakeTileWithDot sets the center pixel's
#   values to 255 red, 170 green, and 85 blue. The tilesheet in use has 256
#   shades of gray, each with an index matching its grayscale value, and mode 3
#   for RGB24 clips reads the red component to get the tile index.



Import("util.avs")

clip = MakeTileWithDot(16, 16, "unique", $FFFFFF, "RGB24")
tilesheet = TurnsTileTestSource("../clips/output-turnstile-levels-tilesheet.png")
tilesheet = tilesheet.ConvertToRGB24()

TurnsTile(clip, tilesheet, mode=3)