# MVVM-TableView-Demo

title: iOS开发-MVVM简单使用(初级①)

### MVC
任何一个正经开发过一阵子软件的人都熟悉MVC，它意思是Model View Controller, 是一个在复杂应用设计中组织代码的公认模式. 它也被证实在 iOS 开发中有着第二种含义: Massive View Controller(重量级视图控制器)。它让许多程序员绞尽脑汁如何去使代码被解耦和组织地让人满意. 总的来说, iOS 开发者已经得出结论: 他们需要给视图控制器瘦身, 并进一步分离事物;但该怎么做呢?
### MVVM
Model - model 在 MVVM 中没有真正的变化. 取决于你的偏好, 你的 model 可能会或可能不会封装一些额外的业务逻辑工作. 我更倾向于把它当做一个容纳表现数据-模型对象信息的结构体, 并在一个单独的管理类中维护的创建/管理模型的统一逻辑。


```
#import <Foundation/Foundation.h>

@interface ShowModel : NSObject
@property (nonatomic , copy) NSString              * image;
@property (nonatomic , copy) NSString              * begin_time;
@property (nonatomic , copy) NSString              * title;
@property (nonatomic , copy) NSString              * end_time;
@end

```

View - view 包含实际 UI 本身(不论是 UIView 代码, storyboard 和 xib), 任何视图特定的逻辑, 和对用户输入的反馈. 在 iOS 中这不仅需要 UIView 代码和那些文件, 还包括很多需由 UIViewController 处理的工作。


```
#import <UIKit/UIKit.h>
@class ShowModel;
@interface ShowCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UIImageView *iconImage;
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UILabel *timeLabel;
@property (weak, nonatomic) IBOutlet UILabel *addressLabel;
@property (nonatomic, strong) ShowModel *model;
@end

```


View-Model 这个术语本身会带来困惑, 因为它混搭了两个我们已知的术语, 但却是完全不同的东东. 它不是传统数据-模型结构中模型的意思(又来了, 只是我喜欢这个例子). 它的职责之一就是作为一个表现视图显示自身所需数据的静态模型;但它也有收集, 解释和转换那些数据的责任. 

```
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

```


```
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

```

Controller 一个更加清晰明确的任务: 呈现由 view-model 提供的数据。


```
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

```
![](https://github.com/roycehe/MVVM-TableView-Demo/blob/master/WX20170316-102512.png)

Github地址:https://github.com/roycehe/MVVM-TableView-Demo

后续更新更多进阶内容
