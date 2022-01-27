import os
from PIL import Image, ImageDraw


def hex_to_rgb(hex_string):
    h = hex_string.lstrip('#')
    return tuple(int(h[i: i + 2], 16) for i in (0, 2, 4))

    
def execute_formation(color_1, color_2):
    args = ', '.join([str(el) for el in color_1 + color_2])
    cmd = "./color_formation " + args
    os.system(cmd)


def draw_gradient(colors):
    n = len(colors)

    with Image.new("RGB", (n * 10, n * 10), (0,0,0,0)) as im:

        pencil = ImageDraw.Draw(im)
        for x in range(0, n * 10, 10):
            pencil.rectangle(((x, 0), (x + 10, n * 10)), fill=tuple(colors[x // 10]))

        im.show()
        im.save("hoover.jpg")


if __name__ == "__main__":
    # YELLOW COLORS
    # first_color = [253, 133, 16]
    # second_color = [253, 233, 16]

    first_color = hex_to_rgb('FFA573') # [253, 133, 16]
    second_color = hex_to_rgb('FF5C00') # [253, 233, 16]

    execute_formation(first_color, second_color)

    with open("diodes_colors.txt", "r", encoding='utf-8') as fp:
        lines = fp.readlines()

        colors = [[int(el) for el in line.split()] for line in lines]

    draw_gradient(colors)
