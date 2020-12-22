
BUILD_DATE=`date +%Y-%m-%d-%H.%M.%S`
ArchivePath=Wuji-iOS-Tutorial-${BUILD_DATE}.xcarchive

xcodebuild clean -project "Wuji-iOS-Tutorial.xcodeproj" -scheme "Wuji-iOS-Tutorial" -configuration Release
xcodebuild -project "Wuji-iOS-Tutorial.xcodeproj" -scheme "Wuji-iOS-Tutorial" -archivePath ${ArchivePath} archive
xcodebuild -exportArchive -exportOptionsPlist exportPlist.plist -archivePath ${ArchivePath} -exportPath .
