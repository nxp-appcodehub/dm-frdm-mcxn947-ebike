# Copyright 2020-2023 NXP
# All rights reserved.
#
# SPDX-License-Identifier: MIT
#

GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/generated/images/*.c))

DEPPATH += --dep-path $(PRJ_DIR)/generated/images
VPATH += :$(PRJ_DIR)/generated/images

CFLAGS += "-I$(PRJ_DIR)/generated/images"