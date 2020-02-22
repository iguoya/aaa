#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#       untitled.py
#       

import re
import sys

def main():
#    generate_mailbox_log('ldap-master.ldif')
#    generate_mailbox_log('ldap.bak')
#    compare_logs("ldap-master.ldif", "ldap.bak", "need_to_replace.log")
    replace_backfile('ldap.bak','need_to_replace.log')
def replace_backfile(bakfile, replacefile):
    fp = open(bakfile, 'r')
    content = fp.read()
    blks = content.split("\n\n")
    lines = file_to_lines(replacefile)
    fpn = open("ldap.bak.new", 'a')
    i = 1
    for blk in blks:
        happen_replace = 0
        for line in lines:
            line = line.split(',')
            if line[0] != '' and line[1] != '' and line[2] !='': 
                line[1] = line[1].strip()
                line[2] = line[2].strip()
                if (-1 != blk.find("mail:"+line[0])) and (-1 != blk.find(line[2])):
                    #  the blk replace and write to file,
                    blk.replace(line[2],line[1])
                    #print blk
                    #print "^^^^^^^^^^^^^^^^^^^^^"
                    #print  i,line[0],line[2]
                    fpn.write(blk+"\n\n")
                    i=i+1
                    happen_replace = 1
        # not match , write file directly
        if (happen_replace == 0):
            fpn.write(blk+"\n\n")
    fpn.close()
    fp.close()
def compare_logs(newfile, oldfile, recordfile):
    # open ldap-master.ldif.txt and convert to lines  
    newlines = file_to_lines(newfile+".log")
    # open ldap.bak.txt and convert to lines
    oldlines = file_to_lines(oldfile+".log")
    for newline in newlines:
        newline = newline.split(',')
        for oldline in oldlines:
            oldline = oldline.split(',')
            # if exist the same mailbox , if not same then record it
            if (newline[0] == oldline[0]):
                #if isset("oldline[1]"):
                if (newline[1] != oldline[1]):
                    # record the mailbox address to replace
                    write_log(recordfile, newline[0]+","+newline[1]+","+oldline[1]+'\n')
                else:
                    write_log("not"+recordfile,newline[0]+","+newline[1]+","+oldline[1]+'\n')
def generate_mailbox_log(filename):
    fp = open(filename, 'r')
    fcontent = fp.read();
    #convert info to the blocks
    blks = fcontent.split('\n\n')
    #visit block one by one
    i = 0
    for blk in blks:
        lines = blk.split('\n')
        # looking for the mail in block
        for mailline in lines:
            is_find = mailline.find('mail:')
            if(is_find != -1):
                mail = mailline.split(':')
                if(-1 == mail[1].find('@')):
                    break
                content = ''
                content = mail[1]+',' 
                # the mail exist then looking for userPassword in this block
                for pwdline in lines:
                    is_find = pwdline.find('userPassword')
                    if(is_find != -1):
                        pwd = pwdline.split('::')
                        content +=pwd[1]+'\n'
    #            print content
                #write mail and pwd to a file
                write_log(filename, content)
                i = i+1
    print "the ",filename, "has ", i ,"lines about mailbox address"
def file_to_lines(filename):
    fp = open(filename, 'r')
    content = fp.read()
    lines = content.split('\n')
    fp.close()
    return lines
def write_log(filename,content):
    fp = open(filename+".log", 'a')
    fp.write(content)
    fp.close()
def isset(v):
    try:
        type(eval(v))
    except:
        return 0
    else:
        return 1
if __name__ == '__main__':
	main()

