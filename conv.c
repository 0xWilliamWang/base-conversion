#include "conv.h"

int base_convert(const uint8_t *buffer, const uint8_t buffer_len, uint8_t *out,
                 const uint8_t out_capcity, const uint8_t src_base,
                 const uint8_t dst_base) {
  if (100 < buffer_len)
    return -1;

  uint8_t quotients[100] = {0};
  uint8_t next_quotients[100] = {0};
  uint8_t last_remainders[100] = {0};

  memcpy(quotients, buffer, buffer_len);

  int out_len = 0;
  int div_index = 0;
  int remainder = 0;
  int quotient_digits = 0;

  for (int quotient_digits = buffer_len; quotient_digits > 0;) {
    for (div_index = 0, remainder = 0; div_index < quotient_digits;
         div_index++) {
      // 先计算当前字节的前4bit
      remainder = remainder * src_base + ((quotients[div_index] & 0xf0) >> 4);
      // 计算商
      uint8_t tmp1 = remainder / dst_base;
      // 计算余数
      remainder %= dst_base;

      // 再计算当前字节的后4bit
      remainder = remainder * src_base + (quotients[div_index] & 0x0f);
      uint8_t tmp2 = remainder / dst_base;
      remainder %= dst_base;

      // 保存下一轮的商
      next_quotients[div_index] = (tmp1 << 4 | tmp2);
    }

    // 保存商的位数
    quotient_digits = div_index;
    // 保存最后一位余数
    last_remainders[out_len++] = remainder;

    // 统计前导零的数量，以便后续不再处理前导零
    int zero_cnt = 0;
    for (int i = 0; i < quotient_digits; i++) {
      if (next_quotients[i] == 0)
        zero_cnt++;
      else
        break;
    }

    quotient_digits -= zero_cnt;
    // 清除不需要再使用的商
    memset(quotients, 0, sizeof(quotients));
    memcpy(quotients, next_quotients + zero_cnt, quotient_digits);
    // 清除不需要再使用的余数
    memset(next_quotients, 0, quotient_digits);
  }

  if (out_capcity < out_len + 1)
    return -1;

  int index = 0;
  for (; index < out_len;) {
    out[index++] = last_remainders[out_len - index - 1] + '0';
  }
  out[index++] = 0;
  return index;
}

