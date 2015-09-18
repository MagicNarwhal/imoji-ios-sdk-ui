//
//  AppDelegate.m
//  imoji-search
//
//  Created by Nima on 9/18/15.
//  Copyright © 2015 Imoji. All rights reserved.
//

#import <ImojiSDK/ImojiSDK.h>
#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // setup imoji sdk
    [[ImojiSDK sharedInstance] setClientId:[[NSUUID alloc] initWithUUIDString:@"748cddd4-460d-420a-bd42-fcba7f6c031b"]
                                  apiToken:@"U2FsdGVkX1/yhkvIVfvMcPCALxJ1VHzTt8FPZdp1vj7GIb+fsdzOjyafu9MZRveo7ebjx1+SKdLUvz8aM6woAw=="];
    
    return YES;
}

@end
