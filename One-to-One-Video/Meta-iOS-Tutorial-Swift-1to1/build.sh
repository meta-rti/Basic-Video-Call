
BUILD_DATE=`date +%Y-%m-%d-%H.%M.%S`
ArchivePath=Meta-iOS-Tutorial-${BUILD_DATE}.xcarchive

xcodebuild clean -project "Meta-iOS-Tutorial.xcodeproj" -scheme "Meta-iOS-Tutorial" -configuration Release
xcodebuild -project "Meta-iOS-Tutorial.xcodeproj" -scheme "Meta-iOS-Tutorial" -archivePath ${ArchivePath} archive
xcodebuild -exportArchive -exportOptionsPlist exportPlist.plist -archivePath ${ArchivePath} -exportPath .
