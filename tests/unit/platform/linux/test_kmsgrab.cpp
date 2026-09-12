/**
 * @file tests/unit/platform/linux/test_kmsgrab.cpp
 * @brief Tests for Linux KMS capture card selection.
 */
#ifdef SUNSHINE_BUILD_DRM
  #include "../../../tests_common.h"

  #include <src/platform/linux/kmsgrab.h>

TEST(KmsGrabCardSelectionTest, KeepsRequestedVkmsCardForCudaEncoder) {
  EXPECT_TRUE(platf::kms::should_include_card_for_capture(platf::kms::card_filter_e::nvidia_only, false, true, false));
}

TEST(KmsGrabCardSelectionTest, FiltersUnselectedNonNvidiaCardForCudaEncoderAutoSelection) {
  EXPECT_FALSE(platf::kms::should_include_card_for_capture(platf::kms::card_filter_e::nvidia_only, false, false, false));
}

TEST(KmsGrabCardSelectionTest, KeepsNonNvidiaCardWhenNvencIsForced) {
  EXPECT_TRUE(platf::kms::should_include_card_for_capture(platf::kms::card_filter_e::nvidia_only, false, false, true));
}

TEST(KmsGrabCardSelectionTest, KeepsRequestedNvidiaCardForVaapiEncoder) {
  EXPECT_TRUE(platf::kms::should_include_card_for_capture(platf::kms::card_filter_e::non_nvidia_only, true, true, false));
}

TEST(KmsGrabCardSelectionTest, FiltersUnselectedNvidiaCardForVaapiEncoder) {
  EXPECT_FALSE(platf::kms::should_include_card_for_capture(platf::kms::card_filter_e::non_nvidia_only, true, false, false));
}

TEST(KmsGrabCardSelectionTest, KeepsOrdinarySystemMemoryCard) {
  EXPECT_TRUE(platf::kms::should_include_card_for_capture(platf::kms::card_filter_e::any, false, false, false));
}
#endif
