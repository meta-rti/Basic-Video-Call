//
//  LastmileViewController.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Copyright © 2019 Wuji. All rights reserved.
//

#import "LastmileViewController.h"

/// LastmileViewController implements various last mille related delegate functions for WujiRtcEngine.
/// "Last mile" refers to the connection between the local device and Wuji's edge server.
@interface LastmileViewController () <WujiRtcEngineDelegate>

@property (weak, nonatomic) IBOutlet UILabel *qualityLabel;
@property (weak, nonatomic) IBOutlet UILabel *rttLabel;
@property (weak, nonatomic) IBOutlet UILabel *uplinkLabel;
@property (weak, nonatomic) IBOutlet UILabel *downlinkLabel;

@property (strong, nonatomic) UIActivityIndicatorView *activityView;
@property (assign, nonatomic) BOOL isLastmileProbeTesting;
@property (weak, nonatomic) WujiRtcEngineKit *wujiKit;
@end

@implementation LastmileViewController
#pragma mark - Getter, Setter
- (WujiRtcEngineKit *)wujiKit {
    return [self.dataSource lastmileVCNeedWujiKit];
}

- (void)setIsLastmileProbeTesting:(BOOL)isLastmileProbeTesting {
    if (isLastmileProbeTesting) {
        WujiLastmileProbeConfig *config = [[WujiLastmileProbeConfig alloc] init];
        config.probeUplink = YES;
        config.probeDownlink = YES;
        config.expectedUplinkBitrate = 5000;
        config.expectedDownlinkBitrate = 5000;
        [self.wujiKit startLastmileProbeTest:config];
        [self.activityView startAnimating];
        self.title = @"Testing...";
    } else {
        [self.activityView stopAnimating];
        [self.wujiKit stopLastmileProbeTest];
        self.title = @"Test result";
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self addActivityView];
    self.wujiKit.delegate = self;
    self.wujiKit.delegate = self;
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

#pragma mark - WujiRtcEngineDelegate

/// Reports the last mile network quality of the local user once every two seconds before the user joins a channel.
/// @param engine - RTC engine instance
/// @param quality -The last mile network quality based on the uplink and dowlink packet loss rate and jitter. See list at:
- (void)rtcEngine:(WujiRtcEngineKit *)engine lastmileQuality:(WujiNetworkQuality)quality {
    NSString *string;
    switch (quality) {
        case WujiNetworkQualityExcellent:      string = @"excellent";   break;
        case WujiNetworkQualityGood:           string = @"good";        break;
        case WujiNetworkQualityPoor:           string = @"poor";        break;
        case WujiNetworkQualityBad:            string = @"bad";         break;
        case WujiNetworkQualityVBad:           string = @"very bad";    break;
        case WujiNetworkQualityDown:           string = @"down";        break;
        case WujiNetworkQualityUnknown:        string = @"unknown";     break;
        case WujiNetworkQualityDetecting:      string = @"detecting";   break;
        case WujiNetworkQualityUnsupported:    string = @"unsupported"; break;
    }
    self.qualityLabel.text = string;
}

/// Reports the last-mile network probe result.
/// @param engine - RTC engine instance
/// @param result - The uplink and downlink last-mile network probe test result, see list here:
- (void)rtcEngine:(WujiRtcEngineKit *)engine lastmileProbeTestResult:(WujiLastmileProbeResult *)result {
    self.rttLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)result.rtt];
    self.uplinkLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)result.uplinkReport.packetLossRate];
    self.downlinkLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)result.downlinkReport.packetLossRate];
    self.isLastmileProbeTesting = NO;
}
@end
