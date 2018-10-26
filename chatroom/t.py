#!/usr/bin/env python
# -*- coding: utf-8 -*-

import socket
bufsize = 100
user = "\"tiger\""
password = "\"freebsd\""
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect(("localhost", 5000))

msg = "{\"action\":\"login\",\"user\":"+user+",\"password\":"+password+"}"
print msg

sock.send(msg)

result = sock.recv(bufsize)
print result

msg = "{\"action\": \"get_users\"}"
sock.send(msg)

result = sock.recv(bufsize)
print result


msg = "{\"action\": \"get_users\"}"
sock.send(msg)

print result

sock.close()
