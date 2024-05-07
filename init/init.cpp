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
        heapstartsize = "16m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.5";
        heapminfree = "8m";
        heapmaxfree = "32m";
    } else {
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.6";
        heapminfree = "8m";
        heapmaxfree = "16m";
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

    if (name != "angelica") {
        return; // Not an "angelica" device
    }

    variant_info_t variant;

    if (country == "Global" || country == "Global_DIP") {
        variant = {
            .brand = "Redmi",
            .device = "angelica",
            .name = "angelica_global",
            .mod_device = "angelica_global",
            .marketname = "Redmi 9C",
            .model = "M2006C3MG",
            .build_fingerprint = "Redmi/angelica_global/angelica:11/RP1A.200720.011/V12.5.4.0.RCRMIXM:user/release-keys"
        };
    }

    set_variant_props(variant);
}

void vendor_load_properties() {
    load_dalvik_properties();
    load_device_properties();
}
