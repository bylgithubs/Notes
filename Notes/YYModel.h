//
//  YYModel.h
//  Notes
//
//  Created by BaoYu Liao on 2021/10/25.
//  Copyright © 2021 PersonalONBYL. All rights reserved.
//

#ifndef YYModel_h
#define YYModel_h


#import <YYModel.h>

- (void)encodeWithCoder:(NSCoder *)aCoder { [self yy_modelEncodeWithCoder:aCoder]; }
- (id)initWithCoder:(NSCoder *)aDecoder { self = [super init]; return [self yy_modelInitWithCoder:aDecoder]; }
- (id)copyWithZone:(NSZone *)zone { return [self yy_modelCopy]; }
- (NSUInteger)hash { return [self yy_modelHash]; }
- (BOOL)isEqual:(id)object { return [self yy_modelIsEqual:object]; }


#endif /* YYModel_h */
