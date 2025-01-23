# created by chw 2022/8/14

import os
import shutil


def main():
    filetype = '.jpg'
    list_path = 'VOCdevkit/VOC2007/JPEGImages'
    save_path = './txt/'

    # 创建文件夹
    if os.path.exists(save_path):
        shutil.rmtree(save_path)    # 删除文件夹
    os.mkdir(save_path)

    # 生成同名 txt 文件
    files = os.listdir(list_path)
    for file in files:
        name, suf = os.path.splitext(file)

        if suf in filetype:
            print(save_path + name + '.txt')
            f = open(save_path + name + '.txt', 'w')
            f.close()


if __name__ == '__main__':
    main()


