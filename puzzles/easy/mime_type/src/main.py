#! /usr/bin/env python3

n = int(input())
q = int(input())

mimetypes = {}

for i in range(n):
    ext, mt = input().split()
    mimetypes[ext.lower()] = mt

for i in range(q):
    fname = input()
    index = fname.rfind(".")

    # Extension not found
    if index == -1:
        print("UNKNOWN")
    else:
        # Extension found, try to fetch it from the dict
        try:
            extension = fname[index + 1 :].lower()
            print((mimetypes[extension]))
        # Key does not exist
        except:
            print("UNKNOWN")
