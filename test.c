#include "conv.h"

void test_12_to_oct(void) {
  uint8_t result[100] = {0};
  int src_base=12;
  int dst_base=10;

  uint8_t tmp1[] = {0x10};
  base_convert(tmp1, sizeof(tmp1), result, sizeof(result), src_base, dst_base);
  assert(strcmp(result, "12") == 0);

  uint8_t tmp2[] = {0x12};
  base_convert(tmp2, sizeof(tmp2), result, sizeof(result), src_base, dst_base);
  assert(strcmp(result, "14") == 0);

  // 12a12a1212ab
  uint8_t tmp3[] = {0x12,0xa1,0x2a,0x12,0x12,0xab};
  base_convert(tmp3, sizeof(tmp3), result, sizeof(result), src_base, dst_base);
  assert(strcmp(result, "918972700259") == 0);

  // ab122222221222222222222222212129
  uint8_t tmp4[] = {0xab,0x12,0x22,0x22,0x22,0x12,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x21,0x21,0x29};
  base_convert(tmp4, sizeof(tmp4), result, sizeof(result), src_base, dst_base);
  // 3.11196750780223e+34
  assert(strcmp(result, "31119675078022301687079151459276593") == 0);

  printf("func: %-20s passed\n", __func__);
}

void test_dec_to_oct(void) {
  uint8_t result[100] = {0};
  int src_base=10;
  int dst_base=8;

  base_convert((uint8_t[]){0x05, 0x85}, 2, result, sizeof(result), src_base, dst_base);
  assert(strcmp(result, "1111") == 0);

  // 1000000000000000
  uint8_t tmp1[] = {0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  base_convert(tmp1, sizeof(tmp1), result, sizeof(result), src_base, dst_base);
  assert(strcmp(result, "34327724461500000") == 0);

  printf("func: %-20s passed\n", __func__);
}

void test_oct_to_dec(void) {
  uint8_t result[100] = {0};
  int src_base=8;
  int dst_base=10;

  base_convert((uint8_t[]){0x11, 0x11}, 2, result, sizeof(result), src_base, dst_base);
  assert(strcmp(result, "585") == 0);

  // 12321415435265754766522113423423223412
  uint8_t tmp1[] = {0x12, 0x32, 0x14, 0x15, 0x43, 0x52, 0x65, 0x75, 0x47, 0x66,
                    0x52, 0x21, 0x13, 0x42, 0x34, 0x23, 0x22, 0x34, 0x12};
  base_convert(tmp1, sizeof(tmp1), result, sizeof(result), src_base, dst_base);
  // 3.3779887201256976e+33
  assert(strcmp(result, "3377988720125697475487641939814154") == 0);

  printf("func: %-20s passed\n", __func__);
}

void test_bin_to_dec(void) {
  uint8_t result[100] = {0};

  base_convert((uint8_t[]){0x10, 0x10}, 2, result, sizeof(result), 2, 10);
  assert(strcmp(result, "10") == 0);

  // 101011110110
  base_convert((uint8_t[]){0x10, 0x10, 0x11, 0x11, 0x01, 0x10}, 6, result, sizeof(result), 2, 10);
  assert(strcmp(result, "2806") == 0);

  // 1100011101011010110101101011010110101101011010110101101011010110101101011010110101101011010110101101011010110101
  uint8_t tmp1[] = {0x11, 0x00, 0x01, 0x11, 0x01, 0x01, 0x10, 0x10, 0x11, 0x01,
                    0x01, 0x10, 0x10, 0x11, 0x01, 0x01, 0x10, 0x10, 0x11, 0x01,
                    0x01, 0x10, 0x10, 0x11, 0x01, 0x01, 0x10, 0x10, 0x11, 0x01,
                    0x01, 0x10, 0x10, 0x11, 0x01, 0x01, 0x10, 0x10, 0x11, 0x01,
                    0x01, 0x10, 0x10, 0x11, 0x01, 0x01, 0x10, 0x10, 0x11, 0x01,
                    0x01, 0x10, 0x10, 0x11, 0x01, 0x01};
  base_convert(tmp1, sizeof(tmp1), result, sizeof(result), 2, 10);
  // 4.043396495179591e+33
  assert(strcmp(result, "4043396495179591071612710095083189") == 0);

  printf("func: %-20s passed\n", __func__);
}

void test_hex_to_dec(void) {
  uint8_t result[100] = {0};

  base_convert((uint8_t[]){0xae, 0x3a}, 2, result, sizeof(result), 16, 10);
  assert(strcmp(result, "44602") == 0);

  base_convert((uint8_t[]){0x00}, 1, result, sizeof(result), 16, 10);
  assert(strcmp(result, "0") == 0);

  base_convert((uint8_t[]){0x01}, 1, result, sizeof(result), 16, 10);
  assert(strcmp(result, "1") == 0);

  base_convert((uint8_t[]){0x0a, 0xe3}, 2, result, sizeof(result), 16, 10);
  assert(strcmp(result, "2787") == 0);

  base_convert((uint8_t[]){0xae, 0x03}, 2, result, sizeof(result), 16, 10);
  assert(strcmp(result, "44547") == 0);

  base_convert((uint8_t[]){0xae, 0x30}, 2, result, sizeof(result), 16, 10);
  assert(strcmp(result, "44592") == 0);

  base_convert((uint8_t[]){0x8f, 0xc8, 0xe7, 0xf7, 0x8e, 0xfe}, 6, result, sizeof(result), 16, 10);
  assert(strcmp(result, "158093047992062") == 0);

  // 验证网站: https://tool.oschina.net/hexconvert/
  // 1223244d2323434344554454454545454545454545454545545454
  uint8_t tmp1[] = {0x12, 0x23, 0x24, 0x4d, 0x23, 0x23, 0x43, 0x43, 0x44,
                    0x55, 0x44, 0x54, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
                    0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x54, 0x54, 0x54};
  base_convert(tmp1, sizeof(tmp1), result, sizeof(result), 16, 10);
  assert(strcmp(result,"7461241206556999471574479633161605519200171385253631869597275220") ==0);

  printf("func: %-20s passed\n", __func__);
}

int main(int argc, char const *argv[]) {
  test_bin_to_dec();
  test_hex_to_dec();
  test_oct_to_dec();
  test_dec_to_oct();
  test_12_to_oct();
  
  return 0;
}
