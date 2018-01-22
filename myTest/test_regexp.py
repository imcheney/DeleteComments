import re

import os


def test_regexp():
    s = 'www.baidu.com'
    res = re.match('.*baidu', s)
    print(res)


def test_get_current_path():
    pwd = os.getcwd()
    return pwd

if __name__ == '__main__':
    print (test_get_current_path())

