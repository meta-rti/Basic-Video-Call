//
//  LastmileViewController.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "LastmileViewController.h"

/// LastmileViewController implements various last mille related delegate functions for MetaRtcEngine.
/// "Last mile" refers to the connection between the local device and Meta's edge server.
@interface LastmileViewController () <MetaRtcEngineDelegate>

@property (weak, nonatomic) IBOutlet UILabel *qualityLabel;
@property (weak, nonatomic) IBOutlet UILabel *rttLabel;
@property (weak, nonatomic) IBOutlet UILabel *uplinkLabel;
@property (weak, nonatomic) IBOutlet UILabel *downlinkLabel;

@property (strong, nonatomic) UIActivityIndicatorView *activityView;
@property (assign, nonatomic) BOOL isLastmileProbeTesting;
@property (weak, nonatomic) MetaRtcEngineKit *metaKit;
@end

@implementation LastmileViewController
#pragma mark - Getter, Setter
- (MetaRtcEngineKit *)metaKit {
    return [self.dataSource lastmileVCNeedMetaKit];
}

- (void)setIsLastmileProbeTesting:(BOOL)isLastmileProbeTesting {
    if (isLastmileProbeTesting) {
        MetaLastmileProbeConfig *config = [[MetaLastmileProbeConfig alloc] init];
        config.probeUplink = YES;
        config.probeDownlink = YES;
        config.expectedUplinkBitrate = 5000;
        config.expectedDownlinkBitrate = 5000;
        [self.metaKit startLastmileProbeTest:config];
        [self.activityView startAnimating];
        self.title = @"Testing...";
    } else {
        [self.activityView stopAnimating];
        [self.metaKit stopLastmileProbeTest];
        self.title = @"Test result";
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self addActivityView];
    self.metaKit.delegate = self;
    self.metaKit.delegate = self;
    self.isLastmileProbeTesting = YES;
    self.view.backgroundColor = [UIColor whiteColor];
}

- (void)dealloc {
    self.isLastmileProbeTesting = NO;
}

#pragma mark - Private
- (void)addActivityView {
    UIActivityIndicatorView *activityView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:activityView];
    self.navigationItem.rightBarButtonItem = rightItem;
    self.activityView = activityView;
}

#pragma mark - MetaRtcEngineDelegate

/// Reports the last mile network quality of the local user once every two seconds before the user joins a channel.
/// @param engine - RTC engine instance
/// @param quality -The last mile network quality based on the uplink and dowlink packet loss rate and jitter. See list at:
- (void)rtcEngine:(MetaRtcEngineKit *)engine lastmileQuality:(MetaNetworkQuality)quality {
    NSString *string;
    switch (quality) {
        case MetaNetworkQualityExcellent:      string = @"excellent";   break;
        case MetaNetworkQualityGood:           string = @"good";        break;
        case MetaNetworkQualityPoor:           string = @"poor";        break;
        case MetaNetworkQualityBad:            string = @"bad";         break;
        case MetaNetworkQualityVBad:           string = @"very bad";    break;
        case MetaNetworkQualityDown:           string = @"down";        break;
        case MetaNetworkQualityUnknown:        string = @"unknown";     break;
        case MetaNetworkQualityDetecting:      string = @"detecting";   break;
        case MetaNetworkQualityUnsupported:    string = @"unsupported"; break;
    }
    self.qualityLabel.text = string;
}

/// Reports the last-mile network probe result.
/// @param engine - RTC engine instance
/// @param result - The uplink and downlink last-mile network probe test result, see list here:
- (void)rtcEngine:(MetaRtcEngineKit *)engine lastmileProbeTestResult:(MetaLastmileProbeResult *)result {
    self.rttLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)result.rtt];
    self.uplinkLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)result.uplinkReport.packetLossRate];
    self.downlinkLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)result.downlinkReport.packetLossRate];
    self.isLastmileProbeTesting = NO;
}
@end
