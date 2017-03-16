//
//  ShowCell.h
//  MVVM-Demo
//
//  Created by 何晓文 on 2017/3/16.
//  Copyright © 2017年 何晓文. All rights reserved.
//

#import <UIKit/UIKit.h>
@class ShowModel;
@interface ShowCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UIImageView *iconImage;
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UILabel *timeLabel;
@property (weak, nonatomic) IBOutlet UILabel *addressLabel;
@property (nonatomic, strong) ShowModel *model;
@end
