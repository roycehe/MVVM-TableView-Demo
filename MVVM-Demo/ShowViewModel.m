//
//  ShowViewModel.m
//  MVVM-Demo
//
//  Created by 何晓文 on 2017/3/16.
//  Copyright © 2017年 何晓文. All rights reserved.
//

#import "ShowViewModel.h"
#import "HttpServer.h"
@implementation ShowViewModel

-(void)getShowDataWith:(ReturnValueBlock)successBlock failMsg:(ErrorBlock)failBlock{


        NSMutableDictionary *params = [NSMutableDictionary dictionary];
        params[@"cate"] = @"latest";
        [Networking enableInterfaceDebug:YES];
        [Networking getWithUrl:@"https://api.douban.com/v2/onlines" params:params success:^(id response) {
            
            successBlock(response);

            NSLog(@"%@",response);
        } fail:^(NSError *error) {
            
            NSLog(@"%@",error);
            failBlock(error);
        }];
    
}
@end
