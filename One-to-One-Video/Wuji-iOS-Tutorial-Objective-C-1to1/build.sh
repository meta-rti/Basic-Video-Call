
BUILD_DATE=`date +%Y-%m-%d-%H.%M.%S`
ArchivePath=Wuji-iOS-Tutorial-${BUILD_DATE}.xcarchive

xcodebuild clean -project "Wuji-iOS-Tutorial-Objective-C.xcodeproj" -scheme "Wuji-iOS-Tutorial-Objective-C" -configuration Release
xcodebuild -project "Wuji-iOS-Tutorial-Objective-C.xcodeproj" -scheme "Wuji-iOS-Tutorial-Objective-C" -archivePath ${ArchivePath} archive
xcodebuild -exportArchive -exportOptionsPlist exportPlist.plist -archivePath ${ArchivePath} -exportPath .
