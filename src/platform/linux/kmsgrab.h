/**
 * @file src/platform/linux/kmsgrab.h
 * @brief Declarations shared by the Linux KMS capture implementation and tests.
 */
#pragma once

namespace platf::kms {

  /**
   * @brief Encoder-driven DRM card filter applied during KMS enumeration.
   */
  enum class card_filter_e {
    any,  ///< Accept cards from any DRM driver.
    nvidia_only,  ///< Accept NVIDIA cards unless the selected connector requires another card.
    non_nvidia_only,  ///< Reject NVIDIA cards unless the selected connector requires one.
  };

  /**
   * @brief Decide whether a DRM card should remain available to KMS capture.
   * @details A card containing the explicitly requested display is retained even
   *          when the encoder memory type would normally filter that card out.
   *
   * @param filter Encoder-driven DRM card filter.
   * @param card_is_nvidia Whether the DRM card is driven by NVIDIA.
   * @param contains_requested_display Whether the card owns the requested connector.
   * @param nvenc_forced Whether NVENC was explicitly selected in the configuration.
   * @return True when the DRM card should be enumerated for capture.
   */
  inline bool should_include_card_for_capture(
    card_filter_e filter,
    bool card_is_nvidia,
    bool contains_requested_display,
    bool nvenc_forced
  ) {
    if (contains_requested_display) {
      return true;
    }

    if (filter == card_filter_e::nvidia_only && !card_is_nvidia) {
      return nvenc_forced;
    }

    if (filter == card_filter_e::non_nvidia_only && card_is_nvidia) {
      return false;
    }

    return true;
  }

}  // namespace platf::kms
