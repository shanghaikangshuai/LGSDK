//
//  LGSDKManager.h
//  LoveGame
//
//  Created by Adxyun_Karson on 2017/8/29.
//  Copyright © 2017年 Adxyun. All rights reserved.
//
/*
 *********************************************************************************
 *LGSDK内部使用了IDFA广告表示，文档应该指出，以免接入方接入后App Store审核出现不必要的问题
 *LGSDk 支付相关：URL Shame为LGSDKPay
 *需要接入方配合做一些Apple Pay的配置
 *由于静态库中使用了分类,所以需要接入方的工程做如下配置:Target->Build Setting->Other Link Flags->加入:-all_load
 *********************************************************************************
 */
#import <UIKit/UIKit.h>

/**
 登录成功回调
 */
typedef void(^LoginSuccessBlock)(NSString *identificationStr);

/**
 取消支付回调,SDK内部未生成订单号
 */
typedef void(^UserCancelPayBlock)(void);

@interface LGSDKManager : NSObject
#pragma mark -
#pragma mark --回调相关
/*! @brief 用户登录成功的bloack回调
 */
@property(nonatomic,copy)LoginSuccessBlock loginSuccessBlock;

/*! @brief 用户登录成功的bloack回调
 */
@property(nonatomic,copy)UserCancelPayBlock userCancelPayBlock;

#pragma mark -
#pragma mark --接口相关
/*! @brief 创建LGSDK单例管理对象，此对象用来统一调度SDK内部逻辑
 * @return 返回LGSDK单例管理对象
 */
+ (instancetype)LG_shareManager;

/*! @brief 注册LGSDK标示
 * @param MerchantIDStr 此参数为支持Apple Pay所需的ID,若接入方不支持Apple Pay,可传nil--eg:@"merchant.com.example.merchantname"
 */
-(void)LG_rigisterSDKWithAppID:(NSString *)appId MerchantID:(NSString *)MerchantIDStr;

/*! @brief 接管app界面，进行艾游戏官方验证
 *
 * 调用此方法说明同意LGSDK从方法调用处开始接手管理App进行艾游戏官方验证
 */
-(void)LG_beginLoveGameCheck;

/*! @brief 用来检查接入方是否按照文档进行相关配置（即调用上面接管app的方法的时机）
 *
 * 调用此方法后，会检查从方法调用处的时机是否符合调用beginLoveGameCheck方法的条件，若日志打印“界面未加载完毕，请修改相关配置”，则说明beginLoveGameCheck调用位置过早
 */
-(BOOL)LG_checkLoadSDKOpportunity;

/*! @brief c处理支付回调
 */
-(void)LG_dealPayResult:(NSURL *)url;

/*! @brief 用户在游戏内部调起购买相关支付界面
 */
-(BOOL)LG_wakeUpPay:(NSDictionary *)payParam;

/*! @brief 获取SDK版本号
 */
-(NSString *)LG_getSDKVersion;

/*! @brief 应用程序整个生命周期即将结束时调用,做一些SDK内部的清理工作,建议:- (void)applicationWillTerminate:(UIApplication *)application
 */
-(void)LG_clear;
@end
