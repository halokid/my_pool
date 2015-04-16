#!/usr/bin/env python

import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM);

port=8888
host="127.0.0.1"
sql='select'
s.sendto(sql, (host, port))
