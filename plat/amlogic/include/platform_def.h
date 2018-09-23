/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_DEF_H
#define PLATFORM_DEF_H

#include <common_def.h>
#include <meson_mmap.h>
#include <tbbr/tbbr_img_def.h>
#include <utils_def.h>

#define BL31_BASE                       0x10100000
#define BL31_SIZE                       0x00080000
#define BL31_LIMIT                      (BL31_BASE + BL31_SIZE)

#define PLAT_MESON_NS_IMAGE_OFFSET      0x1000000

#define CACHE_WRITEBACK_SHIFT           6
#define CACHE_WRITEBACK_GRANULE         (1 << CACHE_WRITEBACK_SHIFT)

#define MAX_MMAP_REGIONS                (4 + PLATFORM_MMAP_REGIONS)
#define MAX_XLAT_TABLES                 9

#define PLAT_MAX_PWR_LVL_STATES         U(2)
#define PLAT_MAX_RET_STATE              U(1)
#define PLAT_MAX_OFF_STATE              U(2)

#define PLAT_MAX_PWR_LVL                U(2)
#define PLAT_NUM_PWR_DOMAINS            (1 + \
                                         PLATFORM_CLUSTER_COUNT + \
                                         PLATFORM_CORE_COUNT)

#define PLAT_PHY_ADDR_SPACE_SIZE        (1ULL << 32)
#define PLAT_VIRT_ADDR_SPACE_SIZE       (1ULL << 32)

#define PLATFORM_CLUSTER_COUNT          1
#define PLATFORM_CORE_COUNT             (PLATFORM_CLUSTER_COUNT * \
                                         PLATFORM_MAX_CPUS_PER_CLUSTER)
#define PLATFORM_MAX_CPUS_PER_CLUSTER   4
#define PLATFORM_MMAP_REGIONS           3
#define PLATFORM_STACK_SIZE             (0x440)

#endif /* PLATFORM_DEF_H */
