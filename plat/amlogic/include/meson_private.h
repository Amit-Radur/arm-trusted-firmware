/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __MESON_PRIVATE_H__
#define __MESON_PRIVATE_H__

void meson_cpu_on(unsigned int cluster, unsigned int core);

void plat_meson_pwrc_setup(void);

#endif /* __MESON_PRIVATE_H__ */

