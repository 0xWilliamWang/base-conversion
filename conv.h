#pragma once

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

size_t base_convert(const uint8_t *buffer, const uint8_t buffer_len, char *out,
                 const size_t out_capcity, const uint8_t src_base,
                 const uint8_t dst_base);