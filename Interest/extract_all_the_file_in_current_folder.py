#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  untitled.py


import os
path = "."

def main():
    '''
    for i in range(1,25):
        if i < 10:
            i = "0"+str(i)
        if not os.path.exists("第"+str(i)+"天"):
            os.mkdir("第"+str(i)+"天")
    files = os.listdir(path)
    '''
    for f in files:
        #print f
        if not os.path.isdir(f):
            print f

            if not os.path.exists(f):
                sh = "unzip -O GBK "+f
                print sh
                os.system(sh)
            fnew = f.replace("zip", "avi")
            location = fnew.find("第")
            location = fnew.find("章")
            num = fnew[location+3:location+5]
            print num
            new_name = fnew[location:]
            sh = "mv "+fnew+" "+new_name
            print sh
            os.system(sh)
            sh = "mv -f "+new_name+" "+"第"+num+"天"
            print sh
            os.system(sh)


    return 0

if __name__ == '__main__':
    main()

