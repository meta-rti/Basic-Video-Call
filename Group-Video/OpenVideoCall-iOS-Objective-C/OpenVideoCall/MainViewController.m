//
//  MainViewController.m
//  OpenVideoCall
//
//  Created by 3 on 2020/12/15.
//  Portions Copyright (c) 2020 meta-rti. All rights reserved.
//

#import "MainViewController.h"
#import "SettingsViewController.h"
#import "RoomViewController.h"
#import "Encryption.h"
#import "KeyCenter.h"
#import "FileCenter.h"
#import "Settings.h"
#import "MediaCharater.h"
#import "CommonExtension.h"
#import "LastmileViewController.h"

@interface MainViewController () <SettingsVCDelegate, SettingsVCDataSource, LastmileVCDataSource, RoomVCDataSource, UITextFieldDelegate>
@property (weak, nonatomic) IBOutlet UITextField *roomNameTextField;
@property (weak, nonatomic) IBOutlet UITextField *encryptionTextField;
@property (weak, nonatomic) IBOutlet UIButton *encryptionButton;
@property (weak, nonatomic) IBOutlet UIButton *testNetworkButton;

@property (strong, nonatomic) MetaRtcEngineKit *metaKit;
@property (assign, nonatomic) EncryptionType encryptionType;
@property (strong, nonatomic) Settings *settings;
@end

@implementation MainViewController
#pragma mark - Getter, Setter
- (MetaRtcEngineKit *)metaKit {
    if (!_metaKit) {
        _metaKit = [MetaRtcEngineKit sharedEngineWithAppId:[KeyCenter AppId] delegate:nil];
        [_metaKit setLogFilter:MetaLogFilterInfo];
        [_metaKit setLogFile:[FileCenter logFilePath]];
    }
    return _metaKit;
}

- (Settings *)settings {
    if (!_settings) {
        _settings = [[Settings alloc] init];
        _settings.dimension = MetaVideoDimension640x360;
        _settings.frameRate = MetaVideoFrameRateFps15;
    }
    return _settings;
}

- (void)setEncryptionType:(EncryptionType)encryptionType {
    _encryptionType = encryptionType;
    NSString *name = [Encryption descriptionWithType:encryptionType];
    [self.encryptionButton setTitle:name forState:UIControlStateNormal];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self metaKit];
    [self updateViews];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSString *segueId = segue.identifier;
    
    if ([segueId isEqualToString:@"mainToSettings"]) {
        SettingsViewController *settingsVC = segue.destinationViewController;
        settingsVC.delegate = self;
        settingsVC.dataSource = self;
    } else if ([segueId isEqualToString:@"mainToLastmile"]) {
        LastmileViewController *testVC = segue.destinationViewController;
        testVC.dataSource = self;
    } else if ([segueId isEqualToString:@"mainToRoom"]) {
        RoomViewController *roomVC = segue.destinationViewController;
        roomVC.dataSource = self;
    }
}

- (IBAction)doRoomNameTextFieldEditing:(UITextField *)sender {
    NSString *text = sender.text;
    if (text && text.length > 0) {
        NSString *legalString = [MediaCharater updateToLegalMediaStringFromString:text];
        sender.text = legalString;
    }
}

- (IBAction)doEncryptionPressed:(UIButton *)sender {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil message:nil preferredStyle:UIAlertControllerStyleActionSheet];
    NSArray *typeArray = [Encryption allTypesArray];
    __weak typeof(self) weakself = self;
    
    for (int i = 0; i < typeArray.count; i++) {
        EncryptionType type = [typeArray[i] intValue];
        UIAlertAction *action = [UIAlertAction actionWithTitle:[Encryption descriptionWithType:type]
                                                         style:UIAlertActionStyleDefault
                                                       handler:^(UIAlertAction * _Nonnull action) {
                                                           weakself.encryptionType = type;
                                                       }];
        [alertController addAction:action];
    }
    UIAlertAction *cancel = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil];
    [alertController addAction: cancel];
    [self presentViewController:alertController animated:YES completion:nil];
}

- (IBAction)doJoinPressed:(UIButton *)sender {
    // start join room when join button pressed
    [self enterRoom];
}

#pragma mark - Private
- (void)updateViews {
    // view elements initialization
    self.encryptionButton.layer.borderColor = UIColor.WJGray.CGColor;
    self.testNetworkButton.layer.borderColor = UIColor.WJGray.CGColor;
    
    UIColor *placeholderColor = [UIColor colorWithRed:196.0 / 255.0 green:196.0 / 255.0 blue:198.0 / 255.0 alpha:1];
    NSDictionary *attributes = @{NSForegroundColorAttributeName : placeholderColor};
    NSString *roomNamePlaceholder = @"Channel Name";
    NSString *encryptionPlaceholder = @"Encryption Key";
    
    self.roomNameTextField.attributedPlaceholder = [[NSAttributedString alloc] initWithString:roomNamePlaceholder
                                                                                   attributes:attributes];
    self.encryptionTextField.attributedPlaceholder = [[NSAttributedString alloc] initWithString:encryptionPlaceholder
                                                                                     attributes:attributes];
}

- (void)enterRoom {
    NSString *roomName = self.roomNameTextField.text;
    if (!roomName.length) {
        return;
    }
    
    NSString *secret = self.encryptionTextField.text;
    if (secret.length) {
        self.settings.encryption.secret = secret;
        self.settings.encryption.type = self.encryptionType;
    } else {
        self.settings.encryption.type = EncryptionTypeNone;
    }
    self.settings.roomName = roomName;
    [self performSegueWithIdentifier:@"mainToRoom" sender:nil];
}

#pragma mark - SettingsVCDelegate, SettingsVCDataSource
- (void)settingsVC:(SettingsViewController *)settingsVC didSelectDimension:(CGSize)dimension {
    self.settings.dimension = dimension;
}

- (void)settingsVC:(SettingsViewController *)settingsVC didSelectFrameRate:(MetaVideoFrameRate)frameRate {
    self.settings.frameRate = frameRate;
}

- (Settings *)settingsVCNeedSettings {
    return self.settings;
}

#pragma mark - LastmileVCDataSource
- (MetaRtcEngineKit *)lastmileVCNeedMetaKit {
    return self.metaKit;
}

#pragma mark - RoomVCDataSource
- (MetaRtcEngineKit *)roomVCNeedMetaKit {
    return self.metaKit;
}

- (Settings *)roomVCNeedSettings {
    return self.settings;
}

#pragma mark - UITextFieldDelegate
- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    if (textField == self.roomNameTextField) {
        [self enterRoom];
    } else {
        [textField resignFirstResponder];
    }
    return YES;
}

#pragma mark - Others
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationItem.titleView.hidden = NO;
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    self.navigationItem.titleView.hidden = YES;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.view endEditing:YES];
}
@end
