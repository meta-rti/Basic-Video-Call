
BUILD_DATE=`date +%Y-%m-%d-%H.%M.%S`
ArchivePath=Wuji-Mac-Tutorial-${BUILD_DATE}.xcarchive

xcodebuild clean -project "Wuji-Mac-Tutorial-Objective-C.xcodeproj" -scheme "Wuji-Mac-Tutorial-Objective-C" -configuration Release
xcodebuild CODE_SIGN_IDENTITY="" CODE_SIGNING_REQUIRED=NO CODE_SIGNING_ALLOWED=NO -project "Wuji-Mac-Tutorial-Objective-C.xcodeproj" -scheme "Wuji-Mac-Tutorial-Objective-C" -archivePath ${ArchivePath} archive
xcodebuild CODE_SIGN_IDENTITY="" CODE_SIGNING_REQUIRED=NO CODE_SIGNING_ALLOWED=NO -exportArchive -exportOptionsPlist exportPlist.plist -archivePath ${ArchivePath} -exportPath .
