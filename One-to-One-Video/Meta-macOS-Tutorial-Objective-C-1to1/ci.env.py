#!/usr/bin/python
# -*- coding: UTF-8 -*-
import re
import os

def main():
    
    appId = ""
    if "META_APP_ID" in os.environ:
        appId = os.environ["META_APP_ID"]
    token = ""

    #if need reset
    f = open("./Meta-Mac-Tutorial-Objective-C/AppID.m", 'r+')
    content = f.read()

    #if need reset
    appString = "@\"" + appId + "\""
    tokenString = "@\"" + token + "\""
    contentNew = re.sub(r'<#Your App ID#>', appString, content)
    contentNew = re.sub(r'<#Temp Token#>', tokenString, contentNew)
    f.seek(0)
    f.write(contentNew)
    f.truncate()


if __name__ == "__main__":
    main()