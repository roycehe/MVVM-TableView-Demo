//
//  ShowViewModel.h
//  MVVM-Demo
//
//  Created by 何晓文 on 2017/3/16.
//  Copyright © 2017年 何晓文. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class ShowModel;

typedef void (^ReturnValueBlock) (id response);
typedef void (^ErrorBlock) (NSError *error);
@interface ShowViewModel : NSObject

/**
 *数据请求
 */
- (void)getShowDataWith:(ReturnValueBlock)successBlock failMsg:(ErrorBlock)failBlock;
@end
