#include "conv.h"

#define BUFFER_SIZE 100

size_t base_convert(const uint8_t *buffer, const uint8_t buffer_len, char *out,
                 const size_t out_capcity, const uint8_t src_base,
                 const uint8_t dst_base) {
  if (BUFFER_SIZE < buffer_len)
    return -1;

  uint8_t quotients[BUFFER_SIZE] = {0};
  uint8_t next_quotients[BUFFER_SIZE] = {0};
  uint8_t last_remainders[BUFFER_SIZE] = {0};

  memcpy(quotients, buffer, buffer_len);

  size_t out_len = 0;
  int div_index = 0;
  int remainder = 0;
  uint8_t tmp1, tmp2 = 0;

  for (int quotient_digits = buffer_len; quotient_digits > 0;) {
    for (div_index = 0, remainder = 0; div_index < quotient_digits; div_index++) {
      remainder = remainder * src_base + ((quotients[div_index] & 0xf0) >> 4);
      tmp1 = remainder / dst_base;
      remainder %= dst_base;

      remainder = remainder * src_base + (quotients[div_index] & 0x0f);
      tmp2 = remainder / dst_base;
      remainder %= dst_base;

      next_quotients[div_index] = (tmp1 << 4 | tmp2);
    }

    quotient_digits = div_index;
    last_remainders[out_len++] = remainder;

    int zero_cnt = 0;
    for (int i = 0; i < quotient_digits; i++) {
      if (next_quotients[i] == 0)
        zero_cnt++;
      else
        break;
    }

    quotient_digits -= zero_cnt;
    memset(quotients, 0, sizeof(quotients));
    memcpy(quotients, next_quotients + zero_cnt, quotient_digits);
    memset(next_quotients, 0, quotient_digits);
  }

  if (out_capcity < out_len + 1)
    return -1;

  size_t index = 0;
  for (; index < out_len;) {
    out[index++] = last_remainders[out_len - index - 1] + '0';
  }
  out[index++] = 0;
  return index;
}

