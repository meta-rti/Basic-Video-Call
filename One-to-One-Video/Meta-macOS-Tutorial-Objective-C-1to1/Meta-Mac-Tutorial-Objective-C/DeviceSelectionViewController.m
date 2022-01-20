//
//  DeviceSelectionViewController.m
//  Meta Mac Tutorial Objective-C
//
//  Created by 3 on 2020/12/17.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "DeviceSelectionViewController.h"

@interface DeviceSelectionViewController ()

@property (weak) IBOutlet NSPopUpButton *microphoneSelection;
@property (weak) IBOutlet NSPopUpButton *speakerSelection;
@property (weak) IBOutlet NSPopUpButton *cameraSelection;

@property (strong, nonatomic) NSArray* connectedRecordingDevices;
@property (strong, nonatomic) NSArray* connectedPlaybackDevices;
@property (strong, nonatomic) NSArray* connectedVideoCaptureDevices;

@end

@implementation DeviceSelectionViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.preferredContentSize = NSMakeSize(500, 250);
    [self loadDevicesInPopUpButtons];
}

- (void)loadDevicesInPopUpButtons {
    [self.microphoneSelection removeAllItems];
    [self.speakerSelection removeAllItems];
    [self.cameraSelection removeAllItems];

    self.connectedRecordingDevices = [self.metaKit enumerateDevices:0];
    for (id device in self.connectedRecordingDevices) {
        [self.microphoneSelection addItemWithTitle:([device deviceName])];
    }
    
    self.connectedPlaybackDevices = [self.metaKit enumerateDevices:1];
    for (id device in self.connectedPlaybackDevices) {
        [self.speakerSelection addItemWithTitle:([device deviceName])];
    }
    
    self.connectedVideoCaptureDevices = [self.metaKit enumerateDevices:3];
    for (id device in self.connectedVideoCaptureDevices) {
        [self.cameraSelection addItemWithTitle:([device deviceName])];
    // Populate the NSPopUpButtons with the enumerated device list
    }
}

- (void)rtcEngine:(MetaRtcEngineKit *)engine device:(NSString*) deviceId type:(MetaMediaDeviceType) deviceType stateChanged:(NSInteger) state {
    [self loadDevicesInPopUpButtons];
    // Repopulate NSPopUpButtons if a device is plugged in or removed
}

- (IBAction)didClickConfirmButton:(NSButton *)button {
    [self.metaKit setDevice:0 deviceId:[self.connectedRecordingDevices[self.microphoneSelection.indexOfSelectedItem] deviceId]];
    [self.metaKit setDevice:1 deviceId:[self.connectedPlaybackDevices[self.speakerSelection.indexOfSelectedItem] deviceId]];
    [self.metaKit setDevice:3 deviceId:[self.connectedVideoCaptureDevices[self.cameraSelection.indexOfSelectedItem] deviceId]];
    // Set the devices
    [self dismissViewController:self];
}

@end