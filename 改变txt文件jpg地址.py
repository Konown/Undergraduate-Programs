# created by chw 2022/7/7

txtname = "../yolov5_val.txt"
filepathname = "VOCdevkit/images/val/"
char_ = '/'

with open(txtname, 'r+', encoding='utf-8') as f:
    lines = f.readlines()
    # f.truncate(0)
# print(lines)

for line_i, line in enumerate(lines):
    nPos = line.rfind(char_)
    name = line[nPos+1:]
    filename = filepathname + str(name)
    print(filename)
    lines[line_i] = filename

with open(txtname, 'w') as f:
    f.writelines(lines)



