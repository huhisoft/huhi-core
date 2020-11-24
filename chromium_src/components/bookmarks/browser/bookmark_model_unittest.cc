/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "../../../../../components/bookmarks/browser/bookmark_model_unittest.cc"
namespace bookmarks {

TEST_F(BookmarkModelTest, HuhiMigrateOtherNodeFolder) {
  // -- Bookmarks
  // |-- A
  // |-- Other Bookmarks
  //     |-- B
  //     |   |--B1.com
  //     |-- C.com
  const bookmarks::BookmarkNode* other_node_folder =
      model_->AddFolder(model_->bookmark_bar_node(),
                        model_->bookmark_bar_node()->children().size(),
                        model_->other_node()->GetTitledUrlNodeTitle());
  model_->AddFolder(model_->bookmark_bar_node(), 0, ASCIIToUTF16("A"));
  const BookmarkNode* folder =
      model_->AddFolder(other_node_folder, 0, ASCIIToUTF16("B"));
  model_->AddURL(folder, 0, ASCIIToUTF16("B1"), GURL("https://B1.com"));

  model_->AddURL(other_node_folder, 1, ASCIIToUTF16("C.com"),
                 GURL("https://C.com"));
  // After migration, it should be
  // -- Bookmarks
  // |-- A
  // -- Other Bookmarks
  // |-- B
  // |   |--B1.com
  // |-- C.com
  HuhiMigrateOtherNodeFolder(model_.get());
  ASSERT_EQ(model_->other_node()->children().size(), 2u);
  ASSERT_EQ(model_->bookmark_bar_node()->children().size(), 1u);
  EXPECT_EQ(model_->bookmark_bar_node()->children()[0]->GetTitle(),
            ASCIIToUTF16("A"));
  EXPECT_EQ(model_->other_node()->children()[0]->GetTitle(), ASCIIToUTF16("B"));
  EXPECT_EQ(model_->other_node()->children()[0]->children()[0]->GetTitle(),
            ASCIIToUTF16("B1"));
  EXPECT_EQ(model_->other_node()->children()[1]->GetTitle(),
            ASCIIToUTF16("C.com"));

  // Empty folder
  model_->AddFolder(model_->bookmark_bar_node(),
                    model_->bookmark_bar_node()->children().size(),
                    model_->other_node()->GetTitledUrlNodeTitle());
  HuhiMigrateOtherNodeFolder(model_.get());
  ASSERT_EQ(model_->bookmark_bar_node()->children().size(), 1u);
  ASSERT_EQ(model_->other_node()->children().size(), 2u);
}

TEST_F(BookmarkModelTest, HuhiMigrateOtherNodeFolderNotExist) {
  ASSERT_EQ(model_->bookmark_bar_node()->children().size(), 0u);
  HuhiMigrateOtherNodeFolder(model_.get());
  ASSERT_EQ(model_->other_node()->children().size(), 0u);

  const BookmarkNode* folder = model_->AddFolder(model_->bookmark_bar_node(), 0,
                                                 ASCIIToUTF16("Other B"));
  model_->AddURL(folder, 0, ASCIIToUTF16("B1"), GURL("https://B1.com"));
  HuhiMigrateOtherNodeFolder(model_.get());
  ASSERT_EQ(model_->bookmark_bar_node()->children().size(), 1u);
  ASSERT_EQ(model_->other_node()->children().size(), 0u);

  model_->AddURL(model_->bookmark_bar_node(), 1,
                 model_->other_node()->GetTitledUrlNodeTitle(),
                 GURL("https://other.bookmarks"));
  HuhiMigrateOtherNodeFolder(model_.get());
  ASSERT_EQ(model_->bookmark_bar_node()->children().size(), 2u);
  ASSERT_EQ(model_->other_node()->children().size(), 0u);
}

TEST_F(BookmarkModelTest, HuhiClearSyncV1MetaInfo_PermanentNodes) {
  AsMutable(model_->bookmark_bar_node())->SetMetaInfo("order", "1.0.1");
  AsMutable(model_->other_node())->SetMetaInfo("order", "1.0.2");

  HuhiClearSyncV1MetaInfo(model_.get());

  ASSERT_EQ(model_->bookmark_bar_node()->GetMetaInfoMap(), nullptr);
  ASSERT_EQ(model_->other_node()->GetMetaInfoMap(), nullptr);
}

TEST_F(BookmarkModelTest, HuhiClearSyncV1MetaInfo) {
  BookmarkNode::MetaInfoMap meta_info_map;
  meta_info_map["object_id"] = "object_id_value";
  meta_info_map["order"] = "order_value";
  meta_info_map["parent_object_id"] = "parent_object_id_value";
  meta_info_map["position_in_parent"] = "position_in_parent_value";
  meta_info_map["sync_timestamp"] = "sync_timestamp_value";
  meta_info_map["version"] = "version_value";
  meta_info_map["originator_cache_guid"] = "originator_cache_guid_value";
  meta_info_map["originator_client_item_id"] =
      "originator_client_item_id_value";
  meta_info_map["mtime"] = "mtime_value";
  meta_info_map["ctime"] = "ctime_value";

  // -- Bookmarks
  // |-- A
  // |   |--A1.com
  // |-- C1.com (The only node contains non related meta info)
  // -- Other Bookmarks
  // |-- B
  // |   |--B1.com
  const BookmarkNode* folder_A = model_->AddFolder(
      model_->bookmark_bar_node(), 0, ASCIIToUTF16("A"), &meta_info_map);
  const BookmarkNode* bookmark_A1 = model_->AddURL(
      folder_A, 0, ASCIIToUTF16("A1"), GURL("https://A1.com"), &meta_info_map);
  const BookmarkNode* bookmark_C1 = model_->AddURL(
      folder_A, 1, ASCIIToUTF16("C1"), GURL("https://C1.com"), &meta_info_map);
  model_->SetNodeMetaInfo(bookmark_C1, "huhi_meta", "huhi_meta_value");
  const BookmarkNode* folder_B = model_->AddFolder(
      model_->other_node(), 0, ASCIIToUTF16("B"), &meta_info_map);
  const BookmarkNode* bookmark_B1 = model_->AddURL(
      folder_A, 0, ASCIIToUTF16("B1"), GURL("https://B1.com"), &meta_info_map);
  ASSERT_NE(folder_A->GetMetaInfoMap(), nullptr);
  ASSERT_NE(bookmark_A1->GetMetaInfoMap(), nullptr);
  ASSERT_NE(bookmark_C1->GetMetaInfoMap(), nullptr);
  ASSERT_NE(folder_B->GetMetaInfoMap(), nullptr);
  ASSERT_NE(bookmark_B1->GetMetaInfoMap(), nullptr);

  HuhiClearSyncV1MetaInfo(model_.get());

  ASSERT_EQ(folder_A->GetMetaInfoMap(), nullptr);
  ASSERT_EQ(bookmark_A1->GetMetaInfoMap(), nullptr);
  ASSERT_NE(bookmark_C1->GetMetaInfoMap(), nullptr);
  ASSERT_EQ(folder_B->GetMetaInfoMap(), nullptr);
  ASSERT_EQ(bookmark_B1->GetMetaInfoMap(), nullptr);

  std::string huhi_meta;
  ASSERT_TRUE(bookmark_C1->GetMetaInfo("huhi_meta", &huhi_meta));
  ASSERT_EQ(huhi_meta, "huhi_meta_value");
}

}  // namespace bookmarks
