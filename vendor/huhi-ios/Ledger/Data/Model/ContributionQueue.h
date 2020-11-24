/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class ContributionPublisher;

NS_ASSUME_NONNULL_BEGIN

@interface ContributionQueue : NSManagedObject

+ (NSFetchRequest<ContributionQueue *> *)fetchRequest;

@property (nonatomic) int64_t id;
@property (nonatomic) int32_t type;
@property (nonatomic) double amount;
@property (nonatomic) bool partial;
@property (nullable, nonatomic, retain) NSSet<ContributionPublisher *> *publishers;

@end

@interface ContributionQueue (CoreDataGeneratedAccessors)

- (void)addPublishersObject:(ContributionPublisher *)value;
- (void)removePublishersObject:(ContributionPublisher *)value;
- (void)addPublishers:(NSSet<ContributionPublisher *> *)values;
- (void)removePublishers:(NSSet<ContributionPublisher *> *)values;

@end

NS_ASSUME_NONNULL_END
