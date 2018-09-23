/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __AML_MMAP_H__
#define __AML_MMAP_H__

/* Memory regions */
#define AML_DRAM_BASE			0x00000000
#define AML_DRAM_SIZE			0xBFFFFFFF

/* Memory-mapped devices */
#define AML_UART0_BASE                  0xc81004c0
#define AML_GICD_BASE			0xc4301000
#define AML_GICC_BASE			0xc4302000

#endif /* __AML_MMAP_H__ */
