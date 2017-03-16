//
//  ShowCell.m
//  MVVM-Demo
//
//  Created by 何晓文 on 2017/3/16.
//  Copyright © 2017年 何晓文. All rights reserved.
//

#import "ShowCell.h"
#import "UIImageView+WebCache.h"
#import "ShowModel.h"
@implementation ShowCell

-(void)setModel:(ShowModel *)model{

    _model = model;
    [_iconImage sd_setImageWithURL:[NSURL URLWithString:model.image]];
    _timeLabel.text = model.begin_time;
    _addressLabel.text = model.end_time;
    _titleLabel.text = model.title;
    
}


@end
