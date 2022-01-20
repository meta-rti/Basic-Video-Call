
BUILD_DATE=`date +%Y-%m-%d-%H.%M.%S`
ArchivePath=Meta-iOS-Tutorial-${BUILD_DATE}.xcarchive

xcodebuild clean -project "Meta-iOS-Tutorial-Objective-C.xcodeproj" -scheme "Meta-iOS-Tutorial-Objective-C" -configuration Release
xcodebuild -project "Meta-iOS-Tutorial-Objective-C.xcodeproj" -scheme "Meta-iOS-Tutorial-Objective-C" -archivePath ${ArchivePath} archive
xcodebuild -exportArchive -exportOptionsPlist exportPlist.plist -archivePath ${ArchivePath} -exportPath .
