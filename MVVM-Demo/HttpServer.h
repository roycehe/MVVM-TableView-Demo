//
//  HttpServer.h
//  Wine
//
//  Created by 何晓文 on 16/3/25.
//  Copyright © 2016年 何晓文. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
/*!
 * Royce
 *
 *  下载进度
 *
 *  @param bytesRead                 已下载的大小
 *  @param totalBytesRead            文件总大小
 *  @param totalBytesExpectedToRead 还有多少需要下载
 */
typedef void (^DownloadProgress)(int64_t bytesRead,
									int64_t totalBytesRead);

typedef DownloadProgress GetProgress;
typedef DownloadProgress PostProgress;

/*!
 *
 *  上传进度
 *
 *  @param bytesWritten              已上传的大小
 *  @param totalBytesWritten         总上传大小
 */
typedef void (^UploadProgress)(int64_t bytesWritten,
								  int64_t totalBytesWritten);

typedef NS_ENUM(NSUInteger, ResponseType) {
	kResponseTypeJSON = 1, // 默认
	kResponseTypeXML  = 2, // XML
	// 特殊情况下，一转换服务器就无法识别的，默认会尝试转换成JSON，若失败则需要自己去转换
	kResponseTypeData = 3
};

typedef NS_ENUM(NSUInteger, RequestType) {
	kRequestTypeJSON = 1, // 默认
	kRequestTypePlainText  = 2 // 普通text/html
};

@class NSURLSessionTask;

// 请勿直接使用NSURLSessionDataTask,以减少对第三方的依赖
// 所有接口返回的类型都是基类NSURLSessionTask，若要接收返回值
// 且处理，请转换成对应的子类类型
typedef NSURLSessionTask URLSessionTask;

/*!
 *
 *  请求成功的回调
 *
 *  @param response 服务端返回的数据类型，通常是字典
 */
typedef void(^ResponseSuccess)(id response);

/*!
 *
 *  网络响应失败时的回调
 *
 *  @param error 错误信息
 */
typedef void(^ResponseFail)(NSError *error);

/*!
 *
 *  基于AFNetworking的网络层封装类
 *
 *  @note 这里只提供公共api
 */
@interface Networking : NSObject

/*!
 *
 *  用于指定网络请求接口的基础url，如：
 *  http://henishuo.com或者http://101.200.209.244
 *  通常在AppDelegate中启动时就设置一次就可以了。如果接口有来源
 *  于多个服务器，可以调用更新
 *
 *  @param baseUrl 网络接口的基础url
 */
+ (void)updateBaseUrl:(NSString *)baseUrl;

/*!
 *
 *  对外公开可获取当前所设置的网络接口基础url
 *
 *  @return 当前基础url
 */
+ (NSString *)baseUrl;

/*!
 *
 *  开启或关闭接口打印信息
 *
 *  @param isDebug 开发期，最好打开，默认是NO
 */
+ (void)enableInterfaceDebug:(BOOL)isDebug;

/*!
 *
 *  配置返回格式，默认为JSON。若为XML或者PLIST请在全局修改一下
 *
 *  @param responseType 响应格式
 */
+ (void)configResponseType:(ResponseType)responseType;

/*!
 *
 *  配置请求格式，默认为JSON。如果要求传XML或者PLIST，请在全局配置一下
 *
 *  @param requestType 请求格式
 */
+ (void)configRequestType:(RequestType)requestType;

/*!
 *
 *  开启或关闭是否自动将URL使用UTF8编码，用于处理链接中有中文时无法请求的问题
 *
 *  @param shouldAutoEncode YES or NO,默认为NO
 */
+ (void)shouldAutoEncodeUrl:(BOOL)shouldAutoEncode;

/*!
 *
 *  配置公共的请求头，只调用一次即可，通常放在应用启动的时候配置就可以了
 *
 *  @param httpHeaders 只需要将与服务器商定的固定参数设置即可
 */
+ (void)configCommonHttpHeaders:(NSDictionary *)httpHeaders;

/*!
 *  @author Royce, 15-11-15 13:11:50
 *
 *  GET请求接口，若不指定baseurl，可传完整的url
 *
 *  @param url     接口路径，如/path/getArticleList?categoryid=1
 *  @param success 接口成功请求到数据的回调
 *  @param fail    接口请求数据失败的回调
 *
 *  @return 返回的对象中有可取消请求的API
 */
#pragma mark <-<-<-<-------GET------->->->->
+ (URLSessionTask *)getWithUrl:(NSString *)url
						  success:(ResponseSuccess)success
							 fail:(ResponseFail)fail;
/*!
 *  @author Royce, 15-11-15 13:11:50
 *
 *  GET请求接口，若不指定baseurl，可传完整的url
 *
 *  @param url     接口路径，如/path/getArticleList
 *  @param params  接口中所需要的拼接参数，如@{"categoryid" : @(12)}
 *  @param success 接口成功请求到数据的回调
 *  @param fail    接口请求数据失败的回调
 *
 *  @return 返回的对象中有可取消请求的API
 */
+ (URLSessionTask *)getWithUrl:(NSString *)url
						   params:(NSDictionary *)params
						  success:(ResponseSuccess)success
							 fail:(ResponseFail)fail;

+ (URLSessionTask *)getWithUrl:(NSString *)url
						   params:(NSDictionary *)params
						 progress:(GetProgress)progress
						  success:(ResponseSuccess)success
							 fail:(ResponseFail)fail;
#pragma mark <-<-<-<-------POST------->->->->
/*!
 *  @author Royce, 15-11-15 13:11:50
 *
 *  POST请求接口，若不指定baseurl，可传完整的url
 *
 *  @param url     接口路径，如/path/getArticleList
 *  @param params  接口中所需的参数，如@{"categoryid" : @(12)}
 *  @param success 接口成功请求到数据的回调
 *  @param fail    接口请求数据失败的回调
 *
 *  @return 返回的对象中有可取消请求的API
 */
+ (URLSessionTask *)postWithUrl:(NSString *)url
							params:(NSDictionary *)params
						   success:(ResponseSuccess)success
							  fail:(ResponseFail)fail;

+ (URLSessionTask *)postWithUrl:(NSString *)url
							params:(NSDictionary *)params
						  progress:(PostProgress)progress
						   success:(ResponseSuccess)success
							  fail:(ResponseFail)fail;
#pragma mark <-<-<-<-------上传下载------->->->->
/**
 *	@author Royce, 16-01-31 00:01:40
 *
 *	图片上传接口，若不指定baseurl，可传完整的url
 *
 *	@param image			图片对象
 *	@param url				上传图片的接口路径，如/path/images/
 *	@param filename		给图片起一个名字，默认为当前日期时间,格式为"yyyyMMddHHmmss"，后缀为`jpg`
 *	@param name				与指定的图片相关联的名称，这是由后端写接口的人指定的，如imagefiles
 *	@param mimeType		默认为image/jpeg
 *	@param parameters	参数
 *	@param progress		上传进度
 *	@param success		上传成功回调
 *	@param fail				上传失败回调
 *
 *	@return
 */
+ (URLSessionTask *)uploadWithImage:(UIImage *)image
								   url:(NSString *)url
							  filename:(NSString *)filename
								  name:(NSString *)name
							  mimeType:(NSString *)mimeType
							parameters:(NSDictionary *)parameters
							  progress:(UploadProgress)progress
							   success:(ResponseSuccess)success
								  fail:(ResponseFail)fail;

/**
 *	@author Royce, 16-01-31 00:01:59
 *
 *	上传文件操作
 *
 *	@param url						上传路径
 *	@param uploadingFile	待上传文件的路径
 *	@param progress			上传进度
 *	@param success				上传成功回调
 *	@param fail					上传失败回调
 *
 *	@return
 */
+ (URLSessionTask *)uploadFileWithUrl:(NSString *)url
						   uploadingFile:(NSString *)uploadingFile
								progress:(UploadProgress)progress
								 success:(ResponseSuccess)success
									fail:(ResponseFail)fail;


/*!
 *  @author Royce, 16-01-08 15:01:11
 *
 *  下载文件
 *
 *  @param url           下载URL
 *  @param saveToPath    下载到哪个路径下
 *  @param progressBlock 下载进度
 *  @param success       下载成功后的回调
 *  @param failure       下载失败后的回调
 */
+ (URLSessionTask *)downloadWithUrl:(NSString *)url
							saveToPath:(NSString *)saveToPath
							  progress:(DownloadProgress)progressBlock
							   success:(ResponseSuccess)success
							   failure:(ResponseFail)failure;

- (void)appendPartWithFileData:(NSData*)data

                          name:(NSString*)name

                      fileName:(NSString*)fileName

                      mimeType:(NSString*)mimeType;
@end
