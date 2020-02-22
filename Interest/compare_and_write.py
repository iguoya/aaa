#!/usr/bin/python
import re
import sys
fp = open("ldap-master.ldif", 'r')
str = fp.read();
#convert info to the blocks
blks = str.split('\n\n')
i = 0
#visit block one by one
fmail = file('mail_and_pwd.txt', 'a')
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
            fmail.write(content)
#            print mailline
#            sys.exit(1)
            i = i+1
fmail.close()
print i
fp.close()
