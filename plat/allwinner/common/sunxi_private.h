/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SUNXI_PRIVATE_H__
#define __SUNXI_PRIVATE_H__

void sunxi_configure_mmu_el3(int flags);
void sunxi_cpu_off(unsigned int cluster, unsigned int core);
void sunxi_cpu_on(unsigned int cluster, unsigned int core);
void sunxi_disable_secondary_cpus(unsigned int primary_cpu);

void sunxi_security_setup(void);

#endif /* __SUNXI_PRIVATE_H__ */
