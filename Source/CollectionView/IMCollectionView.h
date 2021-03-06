//
//  ImojiSDKUI
//
//  Created by Nima Khoshini
//  Copyright (C) 2015 Imoji
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to
//  deal in the Software without restriction, including without limitation the
//  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//  sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//  IN THE SOFTWARE.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <ImojiSDK_MagicNarwhal/IMImojiSession.h>
#import <ImojiSDK_MagicNarwhal/IMCategoryFetchOptions.h>
#import <ImojiSDK_MagicNarwhal/IMImojiImageReference.h>
#import "IMCollectionViewSplashCell.h"

typedef NS_ENUM(NSUInteger, IMCollectionViewContentType) {
    IMCollectionViewContentTypeImojis,
    IMCollectionViewContentTypeImojiCategories,
    IMCollectionViewContentTypeRecentsSplash,
    IMCollectionViewContentTypeCollectionSplash,
    IMCollectionViewContentTypeNoConnectionSplash,
    IMCollectionViewContentTypeNoResultsSplash
};

extern NSUInteger const IMCollectionViewNumberOfItemsToLoad;

@class IMImojiSession, IMImojiCategoryObject, IMImojiObject, IMCollectionLoadingView;

@protocol IMCollectionViewDelegate;

/**
 * A resuable collection view for displaying stickers backed by the ImojiSDK.
 */
@interface IMCollectionView : UICollectionView <UICollectionViewDelegateFlowLayout, UICollectionViewDataSource>

/**
* @abstract The current imoji session
*/
@property(nonatomic, strong, readonly, nonnull) IMImojiSession *session;

/**
* @abstract The type of content currently displayed in collection view
*/
@property(nonatomic, readonly) IMCollectionViewContentType contentType;

/**
 * @abstract The number of Imoji stickers to load. Defaults to IMCollectionViewNumberOfItemsToLoad.
 */
@property(nonatomic) NSUInteger numberOfImojisToLoad;

/**
 * @abstract The size in which to display the Imoji's. By default this is set to 100x100 and the collection view
 * will expand the cell to occupy any remaining space so that the cells fill the rows.
 */
@property(nonatomic) CGSize preferredImojiDisplaySize;

/**
 * @abstract The image bundle to use for displaying shared assets such as splash screen images. Defaults to
 * [IMResourceBundleUtil assetsBundle]
*/
@property(nonatomic, strong, nonnull) NSBundle *imagesBundle;


/**
 * @abstract Whether or not tapping on an Imoji sticker should animate. If YES, processCellAnimations is called when
 * the user selects an Imoji.
*/
@property(nonatomic) BOOL animateSelection;

/**
 * @abstract Whether or not infinite scrolling of content is enabled. Defaults to NO.
*/
@property(nonatomic) BOOL infiniteScroll;

/**
 * @abstract Whether or not use iOS 10's MSStickerViews to display Imoji stickers
*/
@property(nonatomic) BOOL loadUsingStickerViews;

/**
 * @abstract Indicates that the current view is loading. Only for the initial view.
 * Subsequent loading views, such as loading the next page of results within a category,
 * are handled by IMCollectionViewStatusCell.
 */
@property(nonatomic, strong, nullable) IMCollectionLoadingView *loadingView;

/**
 * @abstract The default rendering options to use for displaying the stickers.
*/
@property(nonatomic, strong, nonnull) IMImojiObjectRenderingOptions *renderingOptions;

@property(nonatomic, weak, nullable) id <IMCollectionViewDelegate> collectionViewDelegate;

/**
 * @abstract Creates a collection view with the specified Imoji session
 */
- (nonnull instancetype)initWithSession:(nonnull IMImojiSession *)session;

/**
 * @abstract Creates a collection view with the specified Imoji session
 */
+ (nonnull instancetype)imojiCollectionViewWithSession:(nonnull IMImojiSession *)session;

@end

@interface IMCollectionView (ImojiLoading)

/**
 * @abstract Loads Imoji stickers into the collection view using getFeaturedImojisWithNumberOfResults from IMImojiSession
 */
- (void)loadFeaturedImojis;

/**
 * @abstract Loads Imoji categories into the collection view using getImojiCategoriesWithClassification from IMImojiSession
 * DEPRECATED: Use loadImojiCategoriesWithOptions instead
 */
- (void)loadImojiCategories:(IMImojiSessionCategoryClassification)classification DEPRECATED_ATTRIBUTE;

/**
 * @abstract Loads Imoji categories into the collection view using getImojiCategoriesWithOptions from IMImojiSession
 * @param categoryFetchOptions A set of options for category retrieval.
 */
- (void)loadImojiCategoriesWithOptions:(nullable IMCategoryFetchOptions *)categoryFetchOptions;

/**
 * @abstract Loads Imoji from a given search term into the collection view using searchImojisWithTerm from IMImojiSession
 * The collection view will automatically scroll through multiple pages of stickers if they exist
 * DEPRECATED: Use loadImojisFromSearch:contributingImoji: instead
 */
- (void)loadImojisFromSearch:(nullable NSString *)searchTerm DEPRECATED_ATTRIBUTE;

/**
 * @abstract Loads Imoji from a given search term into the collection view using searchImojisWithTerm from IMImojiSession
 * The collection view will automatically scroll through multiple pages of stickers if they exist
 */
- (void)loadImojisFromSearch:(nullable NSString *)searchTerm contributingImoji:(nullable IMImojiImageReference *)contributingImoji;

/**
 * @abstract Parses a given sentence for popular Imoji stickers
 */
- (void)loadImojisFromSentence:(nonnull NSString *)sentence;

/**
 * @abstract Loads Imoji stickers into the collection view using fetchImojisByIdentifiers from IMImojiSession
 */
- (void)loadImojisFromIdentifiers:(nonnull NSArray *)imojiIdentifiers;

/**
 * @abstract Loads Imoji stickers for an authenticated user into the collection view using
 * getImojisForAuthenticatedUserWithResultSetResponseCallback from IMImojiSession. Defaults to loading all collected content
 * DEPRECATED: Use loadCollectedImojisWithType: instead
 */
- (void)loadUserCollectionImojis DEPRECATED_ATTRIBUTE;

/**
 * @abstract Loads Imoji stickers for an authenticated user into the collection view using
 * getImojisForAuthenticatedUserWithResultSetResponseCallback from IMImojiSession. Caller can specify the type of
 * collected content to load
 */
- (void)loadCollectedImojisWithType:(IMImojiCollectionType)collectionType;

/**
 * @abstract Loads Imoji stickers for an authenticated user into the recents view using
 * getImojisForAuthenticatedUserWithResultSetResponseCallback from IMImojiSession
 */
- (void)loadRecents;

/**
 * @abstract Loads Imoji stickers from a category
 * DEPRECATED: Use loadImojisFromCategory:contributingImoji: instead
 */
- (void)loadImojisFromCategory:(nonnull IMImojiCategoryObject *)category DEPRECATED_ATTRIBUTE;

/**
 * @abstract Loads Imoji stickers from a category
 * In addition, the category's IMImojiImageReference is passed along.
 * When loading a category, if contributingImoji is not nil, then loading a category will place the contributingImoji image as the first result.
 */
- (void)loadImojisFromCategory:(nonnull IMImojiCategoryObject *)category contributingImoji:(nullable IMImojiImageReference *)imojiImage;

/**
 * @abstract Shows specified splash content in the collection view
 */
- (void)displaySplashOfType:(IMCollectionViewSplashCellType)splashType;

/**
 * Loads a preloaded set of Imoji objects into the collection view.
 * @param imojis The preloaded set of Imoji objects
 * @param header The header to set
 */
- (void)loadImojisFromArray:(nonnull NSArray<IMImojiObject *> *)imojis withHeader:(nullable NSString *)header;

/**
 * Loads a preloaded set of Imoji Category objects into the collection view.
 * @param imojiCategories The preloaded set of Imoji Category objects
 * @param header The header to set
 */
- (void)loadImojiCategoriesFromArray:(nonnull NSArray<IMImojiCategoryObject *> *)imojiCategories withHeader:(nullable NSString *)header;

@end

@interface IMCollectionView (Override)

- (void)processCellAnimations:(nonnull NSIndexPath *)currentIndexPath;

- (nullable id)contentForIndexPath:(nonnull NSIndexPath *)path;

- (nullable id)imageForIndexPath:(nonnull NSIndexPath *)path;

- (BOOL)isPathShowingLoadingIndicator:(nonnull NSIndexPath *)indexPath;

@end

@protocol IMCollectionViewDelegate <NSObject>

@optional

/**
 * @abstract Notified when the specified content has completed loading
 */
- (void)imojiCollectionView:(nonnull IMCollectionView *)collectionView didFinishLoadingContentType:(IMCollectionViewContentType)contentType;

/**
 * @abstract Notified when the user has tapped on the a given splash cell
 */
- (void)userDidSelectSplash:(IMCollectionViewSplashCellType)splashType fromCollectionView:(nonnull IMCollectionView *)collectionView;

/**
 * @abstract Notified when a user selected an imoji
 */
- (void)userDidSelectImoji:(nonnull IMImojiObject *)imoji fromCollectionView:(nonnull IMCollectionView *)collectionView;

/**
 * @abstract Notified when a user selected an imoji and an MSSticker object exists (applicable only when loadUsingStickerViews is set to YES)
 * When implemented, this method is called in place of userDidSelectImoji:fromCollectionView:
 */
- (void)userDidSelectSticker:(nonnull NSObject*)msStickerObject andImoji:(nonnull IMImojiObject *)imoji fromCollectionView:(nonnull IMCollectionView *)collectionView;

/**
 * @abstract Notified when a user selected a category
 * DEPRECATED: Use userDidSelectCategory:contributingImoji:fromCollectionView instead
 */
- (void)userDidSelectCategory:(nonnull IMImojiCategoryObject *)category fromCollectionView:(nonnull IMCollectionView *)collectionView DEPRECATED_ATTRIBUTE;

/**
 * @abstract Notified when a user selected a category.
 */
- (void)userDidSelectCategory:(nonnull IMImojiCategoryObject *)category contributingImoji:(nullable IMImojiImageReference *)imojiImage fromCollectionView:(nonnull IMCollectionView *)collectionView;

/**
 * @abstract Notified when a user has scrolled the collection view
 */
- (void)imojiCollectionViewDidScroll:(nonnull IMCollectionView *)collectionView;

/**
 * @abstract Notified when a user selected an attribution link
 */
- (void)userDidSelectAttributionLink:(nonnull NSURL *)attributionLink fromCollectionView:(nonnull IMCollectionView *)collectionView;

@end
