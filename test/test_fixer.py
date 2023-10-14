import os
from pathlib import Path


def fixTexturePath(line: str) -> str:
    if line.find("SO ") >= 0 and line.find(".xpm") >= 0:
        return line[:line.find("textures/")] + "textures/test/SO.png\n"
    if line.find("NO ") >= 0 and line.find(".xpm") >= 0 and line.find("forbidden") < 0:
        return line[:line.find("textures/")] + "textures/test/NO.png\n"
    if line.find("WE ") >= 0 and line.find(".xpm") >= 0:
        return line[:line.find("textures/")] + "textures/test/WE.png\n"
    if line.find("EA ") >= 0 and line.find(".xpm") >= 0:
        return line[:line.find("textures/")] + "textures/test/EA.png\n"
    else:
        return line


def writefile(file, line):
    # with open(path.with_suffix('.replace'), 'a') as file:
    file.write(line)


def readfile(path):
    new_file = open(path.with_suffix('.cub'), 'w')
    with open(path) as file:
        for line in file:
            writefile(new_file, fixTexturePath(line))
        file.close()
    new_file.close()


def main():
    good_maps = Path('./maps/good')
    bad_maps = Path('./maps/bad')

    for path in good_maps.iterdir():
        # os.popen(f"mv {path} {path.with_suffix('.copy')}")
        readfile(path)

    for path in bad_maps.iterdir():
        # os.popen(f"mv {path} {path.with_suffix('.copy')}")
        readfile(path)


if __name__ == "__main__":
    main()

# https://docs.python.org/3/library/os.path.html
# https://www.w3schools.com/python/python_file_open.asp
# https://stackoverflow.com/questions/41752946/replacing-a-character-from-a-certain-index

# s = "Example String"
# k = s[s.find("S"): s.find("S")+3] + "Hahah this is funny"
