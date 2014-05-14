//
//  oneClickPay.h
//  oneClickPay
//
//  Created by Serg Cyclone on 08.04.14.
//  Copyright (c) 2014 PrivatBank. All rights reserved.
//


@protocol oneClickPayDelegate;
@protocol oneClickPayDataSource;

@interface oneClickPay : NSObject

-(void)setDelegate:(NSObject<oneClickPayDelegate> *)delegate;
-(void)setDataSource:(NSObject<oneClickPayDataSource> *)dataSource;

- (void)pay;
- (void)payOTPConfirm;

- (void)cardList;
- (void)history;

- (void)addCardSetDefault:(BOOL)setDefault;
- (void)addCardOTPConfirm;

- (void)deleteCard;
- (void)setDefaultCard;

+ (instancetype)sharedInstance;
+ (instancetype)sharedInstanceWithDataSource:(NSObject<oneClickPayDataSource> *)dataSource andDelegate:(NSObject<oneClickPayDelegate> *)delegate;

@end



@protocol oneClickPayDataSource <NSObject>

- (NSString *)oneClickPayMerchantID;
- (NSString *)oneClickPayPhoneNumber;
- (NSString *)oneClickPayOTP;
- (NSString *)oneClickPayAmount;
- (NSString *)oneClickPayCurrency;
- (NSString *)oneClickPayDescription;
- (NSString *)oneClickPayCardID;

@optional
- (BOOL)oneClickPayNeedCVV2;
- (BOOL)oneClickPayNeed3DS;
- (BOOL)oneClickPayNeedOTP;

@end


@protocol oneClickPayDelegate <NSObject>

- (void)oneClickFailedWithError:(NSError *)error;

- (void)oneClickPaySuccess;
- (void)oneClickPaySent;
- (void)oneClickPayOTPSent;
- (void)oneClickPayRejected;

- (void)oneClickPayCardList:(NSArray*)cardList;
- (void)oneClickPayHistory:(NSArray*)history;

- (void)oneClickAddCardSuccess;
- (void)oneClickDeleteCardSuccess;
- (void)oneClickSetDefaultCardSuccess;

@end