/** @file
 * Copyright (c) 2020-2022, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include <stdio.h>
#include <stdint.h>

/** Begin config **/

/* Settings */
#define PLATFORM_OVERRIDE_SBSA_LEVEL   0x3     //The permissible levels are 3,4,5 and 6
#define PLATFORM_OVERRIDE_PRINT_LEVEL  0x3     //The permissible levels are 1,2,3,4 and 5

/* PCIe BAR config parameters*/
#define PLATFORM_OVERRIDE_PCIE_BAR64_VAL   0x500000000
#define PLATFORM_OVERRIDE_PCIE_BAR32NP_VAL 0x70200000
#define PLATFORM_OVERRIDE_PCIE_BAR32P_VAL  0x70000000

/* PE platform config paramaters */
#define PLATFORM_OVERRIDE_PE_CNT        0x8
#define PLATFORM_OVERRIDE_PE0_INDEX     0x0
#define PLATFORM_OVERRIDE_PE0_MPIDR     0x0
#define PLATFORM_OVERRIDE_PE0_PMU_GSIV  0x17
#define PLATFORM_OVERRIDE_PE1_INDEX     0x1
#define PLATFORM_OVERRIDE_PE1_MPIDR     0x100
#define PLATFORM_OVERRIDE_PE1_PMU_GSIV  0x17
#define PLATFORM_OVERRIDE_PE2_INDEX     0x2
#define PLATFORM_OVERRIDE_PE2_MPIDR     0x200
#define PLATFORM_OVERRIDE_PE2_PMU_GSIV  0x17
#define PLATFORM_OVERRIDE_PE3_INDEX     0x3
#define PLATFORM_OVERRIDE_PE3_MPIDR     0x300
#define PLATFORM_OVERRIDE_PE3_PMU_GSIV  0x17
#define PLATFORM_OVERRIDE_PE4_INDEX     0x4
#define PLATFORM_OVERRIDE_PE4_MPIDR     0x10000
#define PLATFORM_OVERRIDE_PE4_PMU_GSIV  0x17
#define PLATFORM_OVERRIDE_PE5_INDEX     0x5
#define PLATFORM_OVERRIDE_PE5_MPIDR     0x10100
#define PLATFORM_OVERRIDE_PE5_PMU_GSIV  0x17
#define PLATFORM_OVERRIDE_PE6_INDEX     0x6
#define PLATFORM_OVERRIDE_PE6_MPIDR     0x10200
#define PLATFORM_OVERRIDE_PE6_PMU_GSIV  0x17
#define PLATFORM_OVERRIDE_PE7_INDEX     0x7
#define PLATFORM_OVERRIDE_PE7_MPIDR     0x10300
#define PLATFORM_OVERRIDE_PE7_PMU_GSIV  0x17

/* GIC platform config parameters*/
#define PLATFORM_OVERRIDE_GIC_VERSION       0x3
#define PLATFORM_OVERRIDE_CORE_COUNT        0x4
#define PLATFORM_OVERRIDE_CLUSTER_COUNT     0x2
#define PLATFORM_OVERRIDE_GICC_COUNT        (PLATFORM_OVERRIDE_CORE_COUNT * PLATFORM_OVERRIDE_CLUSTER_COUNT)
#define PLATFORM_OVERRIDE_GICD_COUNT        0x1
#define PLATFORM_OVERRIDE_GICRD_COUNT       0x1
#define PLATFORM_OVERRIDE_GICITS_COUNT      0x1
#define PLATFORM_OVERRIDE_GICH_COUNT        0x1
#define PLATFORM_OVERRIDE_GICMSIFRAME_COUNT 0x0
#define PLATFORM_OVERRIDE_GICC_TYPE         0x1000
#define PLATFORM_OVERRIDE_GICD_TYPE         0x1001
#define PLATFORM_OVERRIDE_GICC_GICRD_TYPE   0x1002
#define PLATFORM_OVERRIDE_GICR_GICRD_TYPE   0x1003
#define PLATFORM_OVERRIDE_GICITS_TYPE       0x1004
#define PLATFORM_OVERRIDE_GICMSIFRAME_TYPE  0x1005
#define PLATFORM_OVERRIDE_GICH_TYPE         0x1006
#define PLATFORM_OVERRIDE_GICC_BASE         0x30000000
#define PLATFORM_OVERRIDE_GICD_BASE         0x30000000
#define PLATFORM_OVERRIDE_GICRD_BASE        0x300C0000
#define PLATFORM_OVERRIDE_GICITS_BASE       0x30040000
#define PLATFORM_OVERRIDE_GICH_BASE         0x2C010000
#define PLATFORM_OVERRIDE_GICITS_ID         0
#define PLATFORM_OVERRIDE_GICIRD_LENGTH     (0x20000*8)

/*
 *Secure EL1 timer Flags, Non-Secure EL1 timer Flags, EL2 timer Flags,
 *and Virtual timer Flags all can have the same definition as follows.
 */
#define INTERRUPT_IS_LEVEL_TRIGGERED 0x0
#define INTERRUPT_IS_EDGE_TRIGGERED  0x1
#define INTERRUPT_IS_ACTIVE_HIGH     0x0
#define INTERRUPT_IS_ACTIVE_LOW      0x1

#define TIMER_MODE      INTERRUPT_IS_LEVEL_TRIGGERED
#define TIMER_POLARITY  INTERRUPT_IS_ACTIVE_LOW

#define TIMER_IS_SECURE     0x1

#define TIMER_IS_ALWAYS_ON_CAPABLE   0x1

/* Timer platform config parameters */
#define PLATFORM_OVERRIDE_S_EL1_TIMER_FLAGS     ((TIMER_POLARITY << 1) | (TIMER_MODE << 0))
#define PLATFORM_OVERRIDE_NS_EL1_TIMER_FLAGS    ((TIMER_POLARITY << 1) | (TIMER_MODE << 0))
#define PLATFORM_OVERRIDE_NS_EL2_TIMER_FLAGS    ((TIMER_POLARITY << 1) | (TIMER_MODE << 0))
#define PLATFORM_OVERRIDE_VIRTUAL_TIMER_FLAGS   ((TIMER_POLARITY << 1) | (TIMER_MODE << 0))
#define PLATFORM_OVERRIDE_S_EL1_TIMER_GSIV      0x1D
#define PLATFORM_OVERRIDE_NS_EL1_TIMER_GSIV     0x1E
#define PLATFORM_OVERRIDE_NS_EL2_TIMER_GSIV     0x1A
#define PLATFORM_OVERRIDE_VIRTUAL_TIMER_GSIV    0x1B
#define PLATFORM_OVERRIDE_EL2_VIR_TIMER_GSIV    28
#define PLATFORM_OVERRIDE_PLATFORM_TIMER_COUNT  0x2

#define PLATFORM_OVERRIDE_SYS_TIMER_TYPE        0x2001
#define PLATFORM_OVERRIDE_TIMER_TYPE            PLATFORM_OVERRIDE_SYS_TIMER_TYPE
#define PLATFORM_OVERRIDE_TIMER_COUNT           0x2
#define PLATFORM_OVERRIDE_TIMER_CNTCTL_BASE     0x2a810000

#define PLATFORM_OVERRIDE_TIMER_CNTBASE_0       0x2a830000
#define PLATFORM_OVERRIDE_TIMER_CNTEL0BASE_0    0xFFFFFFFFFFFFFFFF
#define PLATFORM_OVERRIDE_TIMER_GSIV_0          0x5c
#define PLATFORM_OVERRIDE_TIMER_VIRT_GSIV_0     0x0
#define PLATFORM_OVERRIDE_TIMER_PHY_FLAGS_0     0x0
#define PLATFORM_OVERRIDE_TIMER_VIRT_FLAGS_0    0x0
#define PLATFORM_OVERRIDE_TIMER_CMN_FLAGS_0     ((TIMER_IS_ALWAYS_ON_CAPABLE << 1) | (!TIMER_IS_SECURE << 0))
#define PLATFORM_OVERRIDE_TIMER_FLAGS_0         ((PLATFORM_OVERRIDE_TIMER_CMN_FLAGS_0 << 16) | \
                                                 (PLATFORM_OVERRIDE_TIMER_VIRT_FLAGS_0 << 8) | \
                                                 (PLATFORM_OVERRIDE_TIMER_PHY_FLAGS_0))

#define PLATFORM_OVERRIDE_TIMER_CNTBASE_1       0x2a820000
#define PLATFORM_OVERRIDE_TIMER_CNTEL0BASE_1    0xFFFFFFFFFFFFFFFF
#define PLATFORM_OVERRIDE_TIMER_GSIV_1          0x5B
#define PLATFORM_OVERRIDE_TIMER_VIRT_GSIV_1     0x0
#define PLATFORM_OVERRIDE_TIMER_PHY_FLAGS_1     0x0
#define PLATFORM_OVERRIDE_TIMER_VIRT_FLAGS_1    0x0
#define PLATFORM_OVERRIDE_TIMER_CMN_FLAGS_1     ((TIMER_IS_ALWAYS_ON_CAPABLE << 1) | (TIMER_IS_SECURE << 0))
#define PLATFORM_OVERRIDE_TIMER_FLAGS_1         ((PLATFORM_OVERRIDE_TIMER_CMN_FLAGS_1 << 16) | \
                                                 (PLATFORM_OVERRIDE_TIMER_VIRT_FLAGS_1 << 8) | \
                                                 (PLATFORM_OVERRIDE_TIMER_PHY_FLAGS_1))
#define PLATFORM_OVERRIDE_TIMER_CNTFRQ         0x0

/* Watchdog platform config parameters */
#define WD_MODE     INTERRUPT_IS_LEVEL_TRIGGERED
#define WD_POLARITY INTERRUPT_IS_ACTIVE_HIGH

#define WD_IS_SECURE     0x1

#define PLATFORM_OVERRIDE_WD_TIMER_COUNT    0x2
#define PLATFORM_OVERRIDE_WD_REFRESH_BASE   0x2A450000
#define PLATFORM_OVERRIDE_WD_CTRL_BASE      0x2A440000
#define PLATFORM_OVERRIDE_WD_GSIV_0         0x5D
#define PLATFORM_OVERRIDE_WD_FLAGS_0        ((!WD_IS_SECURE << 2) | (WD_POLARITY << 1) | (WD_MODE << 0))
#define PLATFORM_OVERRIDE_WD_GSIV_1         0x5E
#define PLATFORM_OVERRIDE_WD_FLAGS_1        ((WD_IS_SECURE << 2) | (WD_POLARITY << 1) | (WD_MODE << 0))



/* PCIE platform config parameters */
#define PLATFORM_OVERRIDE_NUM_ECAM                1

/* Platform config parameters for ECAM_0 */
#define PLATFORM_OVERRIDE_PCIE_ECAM_BASE_ADDR_0   0x60000000
#define PLATFORM_OVERRIDE_PCIE_SEGMENT_GRP_NUM_0  0x0
#define PLATFORM_OVERRIDE_PCIE_START_BUS_NUM_0    0x0
#define PLATFORM_OVERRIDE_PCIE_END_BUS_NUM_0      0xFF

/* Sample macros for ECAM_1
 * #define PLATFORM_OVERRIDE_PCIE_ECAM_BASE_ADDR_1  0x00000000
 * #define PLATFORM_OVERRIDE_PCIE_SEGMENT_GRP_NUM_1 0x0
 * #define PLATFORM_OVERRIDE_PCIE_START_BUS_NUM_1   0x0
 * #define PLATFORM_OVERRIDE_PCIE_END_BUS_NUM_1     0x0
 */

/* PCIE device hierarchy table */

#define PLATFORM_PCIE_NUM_ENTRIES        21
#define PLATFORM_PCIE_P2P_NOT_SUPPORTED  1

#define PLATFORM_PCIE_DEV0_CLASSCODE     0x6040000
#define PLATFORM_PCIE_DEV0_VENDOR_ID     0x13B5
#define PLATFORM_PCIE_DEV0_DEV_ID        0xDEF
#define PLATFORM_PCIE_DEV0_BUS_NUM       0
#define PLATFORM_PCIE_DEV0_DEV_NUM       1
#define PLATFORM_PCIE_DEV0_FUNC_NUM      0
#define PLATFORM_PCIE_DEV0_SEG_NUM       0
#define PLATFORM_PCIE_DEV0_DMA_SUPPORT   0
#define PLATFORM_PCIE_DEV0_DMA_COHERENT  0
#define PLATFORM_PCIE_DEV0_P2P_SUPPORT   1
#define PLATFORM_PCIE_DEV0_DMA_64BIT     0
#define PLATFORM_PCIE_DEV0_BEHIND_SMMU   0
#define PLATFORM_PCIE_DEV0_ATC_SUPPORT   0

#define PLATFORM_PCIE_DEV1_CLASSCODE     0x6040000
#define PLATFORM_PCIE_DEV1_VENDOR_ID     0x13B5
#define PLATFORM_PCIE_DEV1_DEV_ID        0xDEF
#define PLATFORM_PCIE_DEV1_BUS_NUM       0
#define PLATFORM_PCIE_DEV1_DEV_NUM       2
#define PLATFORM_PCIE_DEV1_FUNC_NUM      0
#define PLATFORM_PCIE_DEV1_SEG_NUM       0
#define PLATFORM_PCIE_DEV1_DMA_SUPPORT   0
#define PLATFORM_PCIE_DEV1_DMA_COHERENT  0
#define PLATFORM_PCIE_DEV1_P2P_SUPPORT   1
#define PLATFORM_PCIE_DEV1_DMA_64BIT     0
#define PLATFORM_PCIE_DEV1_BEHIND_SMMU   0
#define PLATFORM_PCIE_DEV1_ATC_SUPPORT   0

#define PLATFORM_PCIE_DEV2_CLASSCODE     0x6040000
#define PLATFORM_PCIE_DEV2_VENDOR_ID     0x13B5
#define PLATFORM_PCIE_DEV2_DEV_ID        0xDEF
#define PLATFORM_PCIE_DEV2_BUS_NUM       0
#define PLATFORM_PCIE_DEV2_DEV_NUM       3
#define PLATFORM_PCIE_DEV2_FUNC_NUM      0
#define PLATFORM_PCIE_DEV2_SEG_NUM       0
#define PLATFORM_PCIE_DEV2_DMA_SUPPORT   0
#define PLATFORM_PCIE_DEV2_DMA_COHERENT  0
#define PLATFORM_PCIE_DEV2_P2P_SUPPORT   1
#define PLATFORM_PCIE_DEV2_DMA_64BIT     0
#define PLATFORM_PCIE_DEV2_BEHIND_SMMU   0
#define PLATFORM_PCIE_DEV2_ATC_SUPPORT   0

#define PLATFORM_PCIE_DEV3_CLASSCODE     0xED000001
#define PLATFORM_PCIE_DEV3_VENDOR_ID     0x13B5
#define PLATFORM_PCIE_DEV3_DEV_ID        0xED01
#define PLATFORM_PCIE_DEV3_BUS_NUM       0
#define PLATFORM_PCIE_DEV3_DEV_NUM       0x1E
#define PLATFORM_PCIE_DEV3_FUNC_NUM      0
#define PLATFORM_PCIE_DEV3_SEG_NUM       0
#define PLATFORM_PCIE_DEV3_DMA_SUPPORT   0
#define PLATFORM_PCIE_DEV3_DMA_COHERENT  0
#define PLATFORM_PCIE_DEV3_P2P_SUPPORT   1
#define PLATFORM_PCIE_DEV3_DMA_64BIT     0
#define PLATFORM_PCIE_DEV3_BEHIND_SMMU   0
#define PLATFORM_PCIE_DEV3_ATC_SUPPORT   0

#define PLATFORM_PCIE_DEV4_CLASSCODE     0xED000001
#define PLATFORM_PCIE_DEV4_VENDOR_ID     0x13B5
#define PLATFORM_PCIE_DEV4_DEV_ID        0xED01
#define PLATFORM_PCIE_DEV4_BUS_NUM       0
#define PLATFORM_PCIE_DEV4_DEV_NUM       0x1E
#define PLATFORM_PCIE_DEV4_FUNC_NUM      1
#define PLATFORM_PCIE_DEV4_SEG_NUM       0
#define PLATFORM_PCIE_DEV4_DMA_SUPPORT   0
#define PLATFORM_PCIE_DEV4_DMA_COHERENT  0
#define PLATFORM_PCIE_DEV4_P2P_SUPPORT   1
#define PLATFORM_PCIE_DEV4_DMA_64BIT     0
#define PLATFORM_PCIE_DEV4_BEHIND_SMMU   0
#define PLATFORM_PCIE_DEV4_ATC_SUPPORT   0

#define PLATFORM_PCIE_DEV5_CLASSCODE     0x1060101
#define PLATFORM_PCIE_DEV5_VENDOR_ID     0x0ABC
#define PLATFORM_PCIE_DEV5_DEV_ID        0xACED
#define PLATFORM_PCIE_DEV5_BUS_NUM       0
#define PLATFORM_PCIE_DEV5_DEV_NUM       0x1F
#define PLATFORM_PCIE_DEV5_FUNC_NUM      0
#define PLATFORM_PCIE_DEV5_SEG_NUM       0
#define PLATFORM_PCIE_DEV5_DMA_SUPPORT   0
#define PLATFORM_PCIE_DEV5_DMA_COHERENT  0
#define PLATFORM_PCIE_DEV5_P2P_SUPPORT   1
#define PLATFORM_PCIE_DEV5_DMA_64BIT     0
#define PLATFORM_PCIE_DEV5_BEHIND_SMMU   0
#define PLATFORM_PCIE_DEV5_ATC_SUPPORT   0

#define PLATFORM_PCIE_DEV6_CLASSCODE     0x1060101
#define PLATFORM_PCIE_DEV6_VENDOR_ID     0x0ABC
#define PLATFORM_PCIE_DEV6_DEV_ID        0xACED
#define PLATFORM_PCIE_DEV6_BUS_NUM       1
#define PLATFORM_PCIE_DEV6_DEV_NUM       0
#define PLATFORM_PCIE_DEV6_FUNC_NUM      0
#define PLATFORM_PCIE_DEV6_SEG_NUM       0
#define PLATFORM_PCIE_DEV6_DMA_SUPPORT   0
#define PLATFORM_PCIE_DEV6_DMA_COHERENT  0
#define PLATFORM_PCIE_DEV6_P2P_SUPPORT   1
#define PLATFORM_PCIE_DEV6_DMA_64BIT     0
#define PLATFORM_PCIE_DEV6_BEHIND_SMMU   0
#define PLATFORM_PCIE_DEV6_ATC_SUPPORT   0

#define PLATFORM_PCIE_DEV7_CLASSCODE     0xED000000
#define PLATFORM_PCIE_DEV7_VENDOR_ID     0x13B5
#define PLATFORM_PCIE_DEV7_DEV_ID        0xED01
#define PLATFORM_PCIE_DEV7_BUS_NUM       2
#define PLATFORM_PCIE_DEV7_DEV_NUM       0
#define PLATFORM_PCIE_DEV7_FUNC_NUM      0
#define PLATFORM_PCIE_DEV7_SEG_NUM       0
#define PLATFORM_PCIE_DEV7_DMA_SUPPORT   0
#define PLATFORM_PCIE_DEV7_DMA_COHERENT  0
#define PLATFORM_PCIE_DEV7_P2P_SUPPORT   1
#define PLATFORM_PCIE_DEV7_DMA_64BIT     0
#define PLATFORM_PCIE_DEV7_BEHIND_SMMU   0
#define PLATFORM_PCIE_DEV7_ATC_SUPPORT   0

#define PLATFORM_PCIE_DEV8_CLASSCODE     0xED000000
#define PLATFORM_PCIE_DEV8_VENDOR_ID     0x13B5
#define PLATFORM_PCIE_DEV8_DEV_ID        0xED01
#define PLATFORM_PCIE_DEV8_BUS_NUM       2
#define PLATFORM_PCIE_DEV8_DEV_NUM       0
#define PLATFORM_PCIE_DEV8_FUNC_NUM      4
#define PLATFORM_PCIE_DEV8_SEG_NUM       0
#define PLATFORM_PCIE_DEV8_DMA_SUPPORT   0
#define PLATFORM_PCIE_DEV8_DMA_COHERENT  0
#define PLATFORM_PCIE_DEV8_P2P_SUPPORT   1
#define PLATFORM_PCIE_DEV8_DMA_64BIT     0
#define PLATFORM_PCIE_DEV8_BEHIND_SMMU   0
#define PLATFORM_PCIE_DEV8_ATC_SUPPORT   0

#define PLATFORM_PCIE_DEV9_CLASSCODE    0x6040000
#define PLATFORM_PCIE_DEV9_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV9_DEV_ID       0xDEF
#define PLATFORM_PCIE_DEV9_BUS_NUM      3
#define PLATFORM_PCIE_DEV9_DEV_NUM      0
#define PLATFORM_PCIE_DEV9_FUNC_NUM     0
#define PLATFORM_PCIE_DEV9_SEG_NUM      0
#define PLATFORM_PCIE_DEV9_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV9_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV9_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV9_DMA_64BIT    0
#define PLATFORM_PCIE_DEV9_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV9_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV10_CLASSCODE    0x6040000
#define PLATFORM_PCIE_DEV10_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV10_DEV_ID       0xDEF
#define PLATFORM_PCIE_DEV10_BUS_NUM      4
#define PLATFORM_PCIE_DEV10_DEV_NUM      0
#define PLATFORM_PCIE_DEV10_FUNC_NUM     0
#define PLATFORM_PCIE_DEV10_SEG_NUM      0
#define PLATFORM_PCIE_DEV10_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV10_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV10_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV10_DMA_64BIT    0
#define PLATFORM_PCIE_DEV10_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV10_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV11_CLASSCODE    0x6040000
#define PLATFORM_PCIE_DEV11_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV11_DEV_ID       0xDEF
#define PLATFORM_PCIE_DEV11_BUS_NUM      4
#define PLATFORM_PCIE_DEV11_DEV_NUM      1
#define PLATFORM_PCIE_DEV11_FUNC_NUM     0
#define PLATFORM_PCIE_DEV11_SEG_NUM      0
#define PLATFORM_PCIE_DEV11_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV11_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV11_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV11_DMA_64BIT    0
#define PLATFORM_PCIE_DEV11_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV11_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV12_CLASSCODE    0x6040000
#define PLATFORM_PCIE_DEV12_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV12_DEV_ID       0xDEF
#define PLATFORM_PCIE_DEV12_BUS_NUM      4
#define PLATFORM_PCIE_DEV12_DEV_NUM      2
#define PLATFORM_PCIE_DEV12_FUNC_NUM     0
#define PLATFORM_PCIE_DEV12_SEG_NUM      0
#define PLATFORM_PCIE_DEV12_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV12_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV12_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV12_DMA_64BIT    0
#define PLATFORM_PCIE_DEV12_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV12_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV13_CLASSCODE    0x1060101
#define PLATFORM_PCIE_DEV13_VENDOR_ID    0xABC
#define PLATFORM_PCIE_DEV13_DEV_ID       0xACED
#define PLATFORM_PCIE_DEV13_BUS_NUM      5
#define PLATFORM_PCIE_DEV13_DEV_NUM      0
#define PLATFORM_PCIE_DEV13_FUNC_NUM     0
#define PLATFORM_PCIE_DEV13_SEG_NUM      0
#define PLATFORM_PCIE_DEV13_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV13_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV13_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV13_DMA_64BIT    0
#define PLATFORM_PCIE_DEV13_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV13_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV14_CLASSCODE    0xED000000
#define PLATFORM_PCIE_DEV14_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV14_DEV_ID       0xED01
#define PLATFORM_PCIE_DEV14_BUS_NUM      6
#define PLATFORM_PCIE_DEV14_DEV_NUM      0
#define PLATFORM_PCIE_DEV14_FUNC_NUM     0
#define PLATFORM_PCIE_DEV14_SEG_NUM      0
#define PLATFORM_PCIE_DEV14_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV14_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV14_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV14_DMA_64BIT    0
#define PLATFORM_PCIE_DEV14_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV14_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV15_CLASSCODE    0xED000000
#define PLATFORM_PCIE_DEV15_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV15_DEV_ID       0xED01
#define PLATFORM_PCIE_DEV15_BUS_NUM      6
#define PLATFORM_PCIE_DEV15_DEV_NUM      0
#define PLATFORM_PCIE_DEV15_FUNC_NUM     7
#define PLATFORM_PCIE_DEV15_SEG_NUM      0
#define PLATFORM_PCIE_DEV15_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV15_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV15_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV15_DMA_64BIT    0
#define PLATFORM_PCIE_DEV15_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV15_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV16_CLASSCODE    0xFF000000
#define PLATFORM_PCIE_DEV16_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV16_DEV_ID       0xFF80
#define PLATFORM_PCIE_DEV16_BUS_NUM      7
#define PLATFORM_PCIE_DEV16_DEV_NUM      0
#define PLATFORM_PCIE_DEV16_FUNC_NUM     0
#define PLATFORM_PCIE_DEV16_SEG_NUM      0
#define PLATFORM_PCIE_DEV16_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV16_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV16_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV16_DMA_64BIT    0
#define PLATFORM_PCIE_DEV16_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV16_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV17_CLASSCODE    0xFF000000
#define PLATFORM_PCIE_DEV17_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV17_DEV_ID       0xFF80
#define PLATFORM_PCIE_DEV17_BUS_NUM      7
#define PLATFORM_PCIE_DEV17_DEV_NUM      0
#define PLATFORM_PCIE_DEV17_FUNC_NUM     3
#define PLATFORM_PCIE_DEV17_SEG_NUM      0
#define PLATFORM_PCIE_DEV17_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV17_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV17_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV17_DMA_64BIT    0
#define PLATFORM_PCIE_DEV17_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV17_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV18_CLASSCODE    0xFF000000
#define PLATFORM_PCIE_DEV18_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV18_DEV_ID       0xFF80
#define PLATFORM_PCIE_DEV18_BUS_NUM      8
#define PLATFORM_PCIE_DEV18_DEV_NUM      0
#define PLATFORM_PCIE_DEV18_FUNC_NUM     0
#define PLATFORM_PCIE_DEV18_SEG_NUM      0
#define PLATFORM_PCIE_DEV18_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV18_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV18_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV18_DMA_64BIT    0
#define PLATFORM_PCIE_DEV18_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV18_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV19_CLASSCODE    0xFF000000
#define PLATFORM_PCIE_DEV19_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV19_DEV_ID       0xFF80
#define PLATFORM_PCIE_DEV19_BUS_NUM      8
#define PLATFORM_PCIE_DEV19_DEV_NUM      0
#define PLATFORM_PCIE_DEV19_FUNC_NUM     1
#define PLATFORM_PCIE_DEV19_SEG_NUM      0
#define PLATFORM_PCIE_DEV19_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV19_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV19_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV19_DMA_64BIT    0
#define PLATFORM_PCIE_DEV19_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV19_ATC_SUPPORT  0

#define PLATFORM_PCIE_DEV20_CLASSCODE    0x6040000
#define PLATFORM_PCIE_DEV20_VENDOR_ID    0x13B5
#define PLATFORM_PCIE_DEV20_DEV_ID       0x0DEF
#define PLATFORM_PCIE_DEV20_BUS_NUM      0
#define PLATFORM_PCIE_DEV20_DEV_NUM      4
#define PLATFORM_PCIE_DEV20_FUNC_NUM     0
#define PLATFORM_PCIE_DEV20_SEG_NUM      0
#define PLATFORM_PCIE_DEV20_DMA_SUPPORT  0
#define PLATFORM_PCIE_DEV20_DMA_COHERENT 0
#define PLATFORM_PCIE_DEV20_P2P_SUPPORT  1
#define PLATFORM_PCIE_DEV20_DMA_64BIT    0
#define PLATFORM_PCIE_DEV20_BEHIND_SMMU  0
#define PLATFORM_PCIE_DEV20_ATC_SUPPORT  0

/* PERIPHERAL platform config parameters */
#define UART_ADDRESS                     0xF9750000
#define BASE_ADDRESS_ADDRESS_SPACE_ID    0x0
#define BASE_ADDRESS_REGISTER_BIT_WIDTH  0x20
#define BASE_ADDRESS_REGISTER_BIT_OFFSET 0x0
#define BASE_ADDRESS_ADDRESS_SIZE        0x3
#define BASE_ADDRESS_ADDRESS             0x7FF80000
#define UART_INTERRUPT_TYPE              8
#define UART_IRQ                         0
#define UART_GLOBAL_SYSTEM_INTERRUPT     0x93
#define UART_PCI_DEVICE_ID               0xFFFF
#define UART_PCI_VENDOR_ID               0xFFFF
#define UART_PCI_BUS_NUMBER              0x0
#define UART_PCI_DEV_NUMBER              0x0
#define UART_PCI_FUNC_NUMBER             0x0
#define UART_PCI_FLAGS                   0x0
#define UART_PCI_SEGMENT                 0x0

/* IOVIRT platform config parameters */
#define IOVIRT_ADDRESS               0xF9780000
#define IORT_NODE_COUNT              3
#define IOVIRT_ITS_COUNT             1
#define IOVIRT_SMMUV3_BASE_ADDRESS   0x4F000000
#define IOVIRT_SMMU_CTX_INT_OFFSET   0x0
#define IOVIRT_SMMU_CTX_INT_CNT      0x0
#define IOVIRT_RC_PCI_SEG_NUM        0x0
#define IOVIRT_RC_MEMORY_PROPERTIES  0x1
#define IOVIRT_RC_ATS_ATTRIBUTE      0x0
#define RC_MAP0_INPUT_BASE           0x0
#define RC_MAP0_ID_COUNT             0xFFFF
#define RC_MAP0_OUTPUT_BASE          0x0
#define RC_MAP0_OUTPUT_REF           0x134

#define SMMUV3_ID_MAP0_INPUT_BASE       0x0
#define SMMUV3_ID_MAP0_ID_COUNT         0xFFFF
#define SMMUV3_ID_MAP0_OUTPUT_BASE      0x0
#define SMMUV3_ID_MAP0_OUTPUT_REF       0x30
#define SMMUV3_ID_MAP1_INPUT_BASE       0x0
#define SMMUV3_ID_MAP1_ID_COUNT         0x1
#define SMMUV3_ID_MAP1_OUTPUT_BASE      0x10000
#define SMMUV3_ID_MAP1_OUTPUT_REF       0x30
#define IOVIRT_RC_NUM_MAP            1
#define IOVIRT_SMMUV3_NUM_MAP        2
#define IOVIRT_MAX_NUM_MAP           3

/* DMA platform config parameters */
#define PLATFORM_OVERRIDE_DMA_CNT   0

/*Exerciser platform config details*/
#define TEST_REG_COUNT              10
#define EXERCISER_ID                0xED0113B5
#define PCIE_CAP_CTRL_OFFSET        0x4// offset from the extended capability header

/* Exerciser MMIO Offsets */
#define INTXCTL         0x004
#define MSICTL          0x000
#define DMACTL1         0x08
#define DMA_BUS_ADDR    0x010
#define DMA_LEN         0x018
#define DMASTATUS       0x01C
#define PCI_MAX_BUS     255
#define PCI_MAX_DEVICE  31

#define PCI_EXT_CAP_ID  0x10
#define PASID           0x1B
#define PCIE            0x1
#define PCI             0x0

/* PCI/PCIe express extended capability structure's
   next capability pointer mask and cap ID mask */
#define PCIE_NXT_CAP_PTR_MASK 0x0FFF
#define PCIE_CAP_ID_MASK      0xFFFF
#define PCI_CAP_ID_MASK       0x00FF
#define PCI_NXT_CAP_PTR_MASK  0x00FF
#define CAP_PTR_MASK          0x00FF

#define CLR_INTR_MASK       0xFFFFFFFE
#define PASID_TLP_STOP_MASK 0xFFFFFFBF
#define PASID_VAL_MASK      ((0x1ul << 20) - 1)
#define PASID_VAL_SHIFT     12
#define PASID_LEN_SHIFT     7
#define PASID_LEN_MASK      0x7ul
#define DMA_TO_DEVICE_MASK  0xFFFFFFEF

/* shift_bit */
#define SHIFT_1BIT             1
#define SHIFT_2BIT             2
#define SHIFT_4BIT             4
#define SHITT_8BIT             8
#define MASK_BIT               1
#define PREFETCHABLE_BIT_SHIFT 3

#define PCI_CAP_PTR_OFFSET  8
#define PCIE_CAP_PTR_OFFSET 20

#define MSI_GENERATION_MASK (1 << 31)

#define NO_SNOOP_START_MASK 0x20
#define NO_SNOOP_STOP_MASK  0xFFFFFFDF
#define PCIE_CAP_DIS_MASK   0xFFFEFFFF
#define PCIE_CAP_EN_MASK    (1 << 16)
#define PASID_EN_MASK       (1 << 6)
/* PCIe Config space Offset */
#define BAR0_OFFSET        0x10
#define COMMAND_REG_OFFSET 0x04
#define CAP_PTR_OFFSET     0x34
#define PCIE_CAP_OFFSET    0x100

#define PCIE_CAP_CTRL_OFFSET 0x4// offset from the extended capability header

/* Memory config */
#define PLATFORM_OVERRIDE_MEMORY_ENTRY_COUNT        0x4
#define PLATFORM_OVERRIDE_MEMORY_ENTRY0_PHY_ADDR    0xC000000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY0_VIRT_ADDR   0xC000000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY0_SIZE        0x4000000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY0_TYPE        MEMORY_TYPE_DEVICE
#define PLATFORM_OVERRIDE_MEMORY_ENTRY1_PHY_ADDR    0x10000000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY1_VIRT_ADDR   0x10000000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY1_SIZE        0xC170000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY1_TYPE        MEMORY_TYPE_NOT_POPULATED
#define PLATFORM_OVERRIDE_MEMORY_ENTRY2_PHY_ADDR    0xFF600000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY2_VIRT_ADDR   0xFF600000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY2_SIZE        0x10000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY2_TYPE        MEMORY_TYPE_RESERVED
#define PLATFORM_OVERRIDE_MEMORY_ENTRY3_PHY_ADDR    0x80000000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY3_VIRT_ADDR   0x80000000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY3_SIZE        0x7F000000
#define PLATFORM_OVERRIDE_MEMORY_ENTRY3_TYPE        MEMORY_TYPE_NORMAL

/** End config **/
