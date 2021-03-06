//
//  APIBaseManager.h
//  WKNetworking
//
//  Created by wktzjz on 15/6/4.
//  Copyright (c) 2015年 Sara. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSUInteger, APIManagerErrorType){
    APIManagerErrorTypeDefault,       //没有产生过API请求，这个是manager的默认状态。
    APIManagerErrorTypeSuccess,       //API请求成功且返回数据正确，此时manager的数据是可以直接拿来使用的。
    APIManagerErrorTypeNoContent,     //API请求成功但返回数据不正确。如果回调数据验证函数返回值为NO，manager的状态就会是这个。
    APIManagerErrorTypeParamsError,   //参数错误，此时manager不会调用API，因为参数验证是在调用API之前做的。
    APIManagerErrorTypeTimeout,       //请求超时。WKApiProxy设置的是20秒超时，具体超时时间的设置请自己去看WKApiProxy的相关代码。
    APIManagerErrorTypeNoNetWork      //网络不通。在调用API之前会判断一下当前网络是否通畅，这个也是在调用API之前验证的，和上面超时的状态是有区别的。
};

typedef NS_ENUM (NSUInteger, APIManagerRequestType){
    APIManagerRequestTypeGet,
    APIManagerRequestTypePost,
    APIManagerRequestTypeRestGet,
    APIManagerRequestTypeRestPost
};

@class APIBaseManager;

//Network API回调
@protocol APIManagerApiCallBackDelegate <NSObject>
@required
- (void)managerCallAPIDidSuccess:(APIBaseManager *)manager;
- (void)managerCallAPIDidFailed:(APIBaseManager *)manager;
@end


@protocol RTAPIManagerCallbackDataReformer <NSObject>
@required
- (id)manager:(APIBaseManager *)manager reformData:(NSDictionary *)data;
@end

/*
APIBaseManager的派生类必须符合这些protocal
*/
@protocol APIManager <NSObject>

@required
- (NSString *)methodName;
- (NSString *)serviceType;
- (APIManagerRequestType)requestType;

@optional
- (void)cleanData;
- (NSDictionary *)reformParams:(NSDictionary *)params;
- (BOOL)shouldCache;

@end


@interface APIBaseManager : NSObject

@property (nonatomic, weak) id <APIManagerApiCallBackDelegate> delegate;

@property (nonatomic, assign, readonly) BOOL isReachable;

@property (nonatomic, strong) NSString *methodName;
@property (nonatomic, strong) NSString *serviceType;
@property (nonatomic, assign) APIManagerRequestType requestType;

@property (nonatomic, strong) id fetchedData;

- (NSInteger)getNetworkDataWithParams:(NSDictionary *)params;


@end
