#
# Copyright (C) 2023 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/non_ab_device.mk)

# Inherit from device makefile.
$(call inherit-product, device/xiaomi/angelica/device.mk)

# Inherit some common LineageOS stuff.
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

PRODUCT_DEVICE := angelica
PRODUCT_NAME := lineage_angelica
PRODUCT_BRAND := Redmi
PRODUCT_MODEL := M2006C3MG
PRODUCT_MANUFACTURER := Xiaomi

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="angelica_global-user 11 RP1A.200720.011 V12.5.4.0.RCRMIXM release-keys"

BUILD_FINGERPRINT := Redmi/angelica_global/angelica:11/RP1A.200720.011/V12.5.4.0.RCRMIXM:user/release-keys