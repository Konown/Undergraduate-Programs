# created by chw 2022/8/14

import os


def main():
    res = []
    filetype = '.jpg'
    list_path = 'VOCdevkit/VOC2007/JPEGImages/'
    save_file = './yolov5_val.txt'

    with open(save_file, 'w') as f:
        for root, dirs, files in os.walk(list_path):
            for file in files:
                name, suf = os.path.splitext(file)

                if suf == filetype:
                    res.append(os.path.join(root, file + '\n'))
        f.writelines(res)


if __name__ == '__main__':
    main()
    