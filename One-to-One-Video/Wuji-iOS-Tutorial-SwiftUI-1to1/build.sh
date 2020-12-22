
rm -f *.ipa
rm -rf *.app
rm -f *.zip
rm -rf dSYMs
rm -rf *.dSYM
rm -f *dSYMs.zip
rm -rf *.xcarchive

BUILD_DATE=`date +%Y-%m-%d-%H.%M.%S`
APP_TARGET=Wuji-iOS-Tutorial-SwiftUI-1to1
PROJECT_NAME=Wuji-iOS-Tutorial-SwiftUI-1to1.xcodeproj
ArchivePath=${APP_TARGET}-${BUILD_DATE}.xcarchive

xcodebuild clean -project ${PROJECT_NAME} -scheme ${APP_TARGET} -configuration Release
xcodebuild -project ${PROJECT_NAME} -scheme ${APP_TARGET}  -archivePath ${ArchivePath} archive
xcodebuild -exportArchive -exportOptionsPlist exportPlist.plist -archivePath ${ArchivePath} -exportPath .
