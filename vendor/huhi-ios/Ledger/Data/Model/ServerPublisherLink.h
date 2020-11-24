/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#import <CoreData/CoreData.h>

@class ServerPublisherInfo;

NS_ASSUME_NONNULL_BEGIN

@interface ServerPublisherLink : NSManagedObject

+ (NSFetchRequest<ServerPublisherLink *> *)fetchRequest;

@property (nonatomic, copy) NSString *publisherID;
@property (nullable, nonatomic, copy) NSString *provider;
@property (nullable, nonatomic, copy) NSString *link;
@property (nullable, nonatomic, retain) ServerPublisherInfo *serverPublisherInfo;

@end

NS_ASSUME_NONNULL_END
