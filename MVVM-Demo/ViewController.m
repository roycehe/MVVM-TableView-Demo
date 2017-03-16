//
//  ViewController.m
//  MVVM-Demo
//
//  Created by 何晓文 on 2017/3/16.
//  Copyright © 2017年 何晓文. All rights reserved.
//

#import "ViewController.h"
#import "ShowCell.h"
#import "ShowViewModel.h"
#import "ShowModel.h"
#import "MJExtension.h"
@interface ViewController ()<UITableViewDataSource,UITableViewDelegate>
@property (nonatomic,strong) NSMutableArray *showArray;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    UITableView *tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStylePlain];
    tableView.dataSource = self;
    tableView.delegate = self;
    tableView.rowHeight = 80;
    [self.view addSubview:tableView];
    [tableView registerNib:[UINib nibWithNibName:@"ShowCell" bundle:[NSBundle mainBundle]] forCellReuseIdentifier:@"show"];
    
    ShowViewModel *viewModel = [[ShowViewModel alloc]init];
    [viewModel getShowDataWith:^(id response) {
         NSDictionary *dic = (NSDictionary *)response;
        self.showArray = [ShowModel mj_objectArrayWithKeyValuesArray:dic[@"onlines"]];
        [tableView reloadData];
    } failMsg:^(NSError *error) {
        
    }];
    
}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.showArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    ShowCell *cell = [tableView dequeueReusableCellWithIdentifier:@"show"];
    cell.model = _showArray[indexPath.row];
    return cell;
}


- (NSMutableArray *)showArray {
    if (!_showArray) {
        _showArray = [[NSMutableArray alloc] init];
    }
    return _showArray;
    
}

@end
