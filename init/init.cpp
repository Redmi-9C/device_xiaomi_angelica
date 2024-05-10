/*
 * Copyright (C) 2021 crDroid Android Project
 * Copyright (C) 2020 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fstream>
#include <string>
#include <cstring>
#include <sys/sysinfo.h>

#include <android-base/properties.h>
#include <libinit_variants.h>
#include <libinit_utils.h>

#include "vendor_init.h"

using android::base::GetProperty;

void load_dalvik_properties() {
    char const *heapstartsize;
    char const *heapgrowthlimit;
    char const *heapsize;
    char const *heapminfree;
    char const *heapmaxfree;
    char const *heaptargetutilization;
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram >= 5ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        heapstartsize = "16m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.5";
        heapminfree = "8m";
        heapmaxfree = "32m";
    } else if (sys.totalram >= 3ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-4096-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.6";
        heapminfree = "8m";
        heapmaxfree = "16m";
    } else {
        // from - phone-xhdpi-2048-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.75";
        heapminfree = "512k";
        heapmaxfree = "8m";
    }

    property_override("dalvik.vm.heapstartsize", heapstartsize);
    property_override("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_override("dalvik.vm.heapsize", heapsize);
    property_override("dalvik.vm.heaptargetutilization", heaptargetutilization);
    property_override("dalvik.vm.heapminfree", heapminfree);
    property_override("dalvik.vm.heapmaxfree", heapmaxfree);
}

void load_device_properties() {
    std::string country = GetProperty("ro.boot.hwc", "");
    std::string name = GetProperty("ro.boot.hwname", "");

    variant_info_t variant;

    if (name == "angelica") {
        if (country == "Global" || country == "Global_DIP") {
angelica_global:
            // Redmi 9C (Global)
            variant = {
                .brand = "Redmi",
                .device = "angelica",
                .name = "angelica_global",
                .mod_device = "angelica_global",
                .marketname = "Redmi 9C",
                .model = "M2006C3MG",
                .build_fingerprint = "Redmi/angelica_global/angelica:11/RP1A.200720.011/V12.5.4.0.RCRMIXM:user/release-keys"
            };
        } else if (country == "Thailand") {
            // Redmi 9C (Thailand)
            variant = {
                .brand = "Redmi",
                .device = "angelica",
                .name = "angelica_global",
                .mod_device = "angelica_global",
                .marketname = "Redmi 9C",
                .model = "M2006C3MT",
                .build_fingerprint = "Redmi/angelica_global/angelica:11/RP1A.200720.011/V12.5.4.0.RCRMIXM:user/release-keys"
            };
        } else if (country == "Indonesia") {
            // Redmi 9C (Indonesia)
            variant = {
                .brand = "Redmi",
                .device = "angelica",
                .name = "angelica_global",
                .mod_device = "angelica_global",
                .marketname = "Redmi 9C",
                .model = "M2006C3MG",
                .build_fingerprint = "Redmi/angelica_id/angelica:11/RP1A.200720.011/V12.5.3.0.RCRIDXM:user/release-keys"
            };
        }
    } else {
        goto angelica_global;  // fallback to global variant
    set_variant_props(variant);
    }
}

void vendor_load_properties() {
    load_dalvik_properties();
    load_device_properties();
}
