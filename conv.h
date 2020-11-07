#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int base_convert(const uint8_t *buffer, const uint8_t buffer_len, uint8_t *out,
                 const uint8_t out_capcity, const uint8_t src_base,
                 const uint8_t dst_base);