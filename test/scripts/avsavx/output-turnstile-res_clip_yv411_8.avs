Import("util.avs")

TurnsTileTestSource("../clips/hsl.png")
ConvertToYV411(matrix="PC.601")

TurnsTile(4, 1, res=8)