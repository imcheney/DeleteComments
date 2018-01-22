"""
CommentDeleter Version 1.0
Xiaolong Chen
NetEase Inc.
"""

import os
import re

import sys

code_type = ''

# global status def
S_INIT = 0
S_SLASH = 1
S_BLOCK_COMMENT = 2
S_BLOCK_COMMENT_STAR = 3
S_LINE_COMMENT = 4
S_STR = 5
S_STR_ESCAPE = 6


def trim_dir(path):
    print("dir: " + path)
    for root, dirs, files in os.walk(path):
        for name in files:
            trim_file(os.path.join(root, name))
        for name in dirs:  # 递归处理dir
            trim_dir(os.path.join(root, name))


def trim_file(src_filename):
    print("file: " + src_filename)
    if not re.match(".+." + code_type + "$", src_filename):
        print("ignored, pass...")
    else:
        print("matched, ok...")
        new_filename = src_filename + ".new"
        fp_src = open(src_filename, encoding='utf-8')
        fp_dst = open(new_filename, 'w', encoding='utf-8')  # 打开原文件名的空白文件
        state = S_INIT

        for line in fp_src.readlines():
            for c in line:
                if state == S_INIT:
                    if c == '/':
                        state = S_SLASH
                    elif c == '"':
                        state = S_STR
                        fp_dst.write(c)
                    else:
                        fp_dst.write(c)
                elif state == S_SLASH:
                    if c == '*':
                        state = S_BLOCK_COMMENT
                    elif c == '/':
                        state = S_LINE_COMMENT
                    else:
                        fp_dst.write('/')
                        fp_dst.write(c)
                elif state == S_BLOCK_COMMENT:
                    if c == '*':
                        state = S_BLOCK_COMMENT_STAR
                elif state == S_BLOCK_COMMENT_STAR:
                    if c == '/':
                        state = S_INIT
                    else:
                        state = S_BLOCK_COMMENT
                elif state == S_LINE_COMMENT:
                    if c == '\n':
                        state = S_INIT
                        fp_dst.write(c)
                elif state == S_STR:
                    if c == '"':
                        state = S_INIT
                    fp_dst.write(c)
        fp_src.close()
        fp_dst.close()


if __name__ == '__main__':
    global code_type
    if len(sys.arv) == 3:
        path = sys.argv[1]
        code_type = sys.argv[2]
    elif len(sys.argv) == 2:
        path = sys.argv[1]
        code_type = 'cpp'
    elif len(sys.argv) == 1:
        path = os.getcwd()  # 没有明确写出的话, path应当是当前路径
        code_type = 'cpp'
    else:
        print('Wrong command! Usage: python3 CommentDeleter [path] [code_type]')
        sys.exit(0)
    # dir or file
    if os.path.isdir(path):
        trim_dir(path)
    elif os.path.isfile(path):
        trim_file(path)
    else:
        print('Error: invalid path')
        sys.exit(0)
