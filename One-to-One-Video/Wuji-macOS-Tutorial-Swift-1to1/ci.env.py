#!/usr/bin/python
# -*- coding: UTF-8 -*-
import re
import os

def main():
    
    appId = ""
    if "WUJI_APP_ID" in os.environ:
        appId = os.environ["WUJI_APP_ID"]
    token = ""

    f = open("./Wuji-Mac-Tutorial-Swift/AppID.swift", 'r+')
    content = f.read()
    appString = "\"" + appId + "\""
    tokenString = "\"" + token + "\""
    contentNew = re.sub(r'<#Your App ID#>', appString, content)
    contentNew = re.sub(r'<#Temp Token#>', tokenString, contentNew)
    f.seek(0)
    f.write(contentNew)
    f.truncate()


if __name__ == "__main__":
    main()
