#!/usr/bin/python
# -*- coding: UTF-8 -*-
import re
import os

def main():
#    SDK_URL = ""
#    if "SDK_URL" in os.environ:
#        SDK_URL = os.environ["SDK_URL"]
#
#    TARGET_LIBS_ZIP = "wuji_sdk.zip"
#    TARGET_INTERNAL_FOLDER = "Wuji_sdk"
#    ZIP_STRUCTURE_FOLDER = "Wuji_Native_SDK_for_iOS_FULL/libs"
#    FRAMEWORK_NAME = "WujiRtcKit.framework"
#    APP_NAME = "Wuji iOS Tutorial"
#
#    wget = "wget -q " + SDK_URL + " -O " + TARGET_LIBS_ZIP
#    os.system(wget)
#
#    unzip = "unzip -q " + TARGET_LIBS_ZIP + " -d " + TARGET_INTERNAL_FOLDER
#    os.system(unzip)
#
#    mv = "mv -f " + TARGET_INTERNAL_FOLDER + "/" + ZIP_STRUCTURE_FOLDER + "/" + FRAMEWORK_NAME + " \"" + APP_NAME +"\""
#    os.system(mv)
#
#    appId = ""

    if "WUJI_APP_ID" in os.environ:
        appId = os.environ["WUJI_APP_ID"]
    token = ""

    f = open("./Wuji-iOS-Tutorial/AppID.swift", 'r+')
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
