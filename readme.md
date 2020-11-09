# intro
This is a C language implementation of the number of the hexadecimal conversion library, support between 2-16 any base. Big numbers are also supported. This code can run on an embedded chip, such as Cortex-M3.
It can be easily integrated into a project because it doesn't have any other dependencies.Just include the conv.c and conv.h files.

# feature
1. There are no dependencies other than standard c99 library functions.
1. No malloc func
1. Support big number

# limit
1. Only between binary and hexadecimal is supported, because four bits are used to store one digit in order to save space.
1. Support for bases larger than 16 is easy, and requires only simple modifications.

# usage
**api**
```c
size_t base_convert(const uint8_t *buffer, const uint8_t buffer_len, char *out,
                 const size_t out_capcity, const uint8_t src_base,
                 const uint8_t dst_base);
```
**example**
```c
  // 1223244d2323434344554454454545454545454545454545545454
  uint8_t tmp1[] = {0x12, 0x23, 0x24, 0x4d, 0x23, 0x23, 0x43, 0x43, 0x44,
                    0x55, 0x44, 0x54, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
                    0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x54, 0x54, 0x54};
  base_convert(tmp1, sizeof(tmp1), result, sizeof(result), 16, 10);
  assert(strcmp(result,"7461241206556999471574479633161605519200171385253631869597275220") ==0);

  // ab122222221222222222222222212129
  uint8_t tmp4[] = {0xab,0x12,0x22,0x22,0x22,0x12,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x21,0x21,0x29};
  base_convert(tmp4, sizeof(tmp4), result, sizeof(result), 12, 10);
  // 3.11196750780223e+34
  assert(strcmp(result, "31119675078022301687079151459276593") == 0);  
```

**test**
>see test.c
```c
int main(int argc, char const *argv[]) {
  test_bin_to_dec();
  test_hex_to_dec();
  test_oct_to_dec();
  test_dec_to_oct();
  test_12_to_oct();
  return 0;
}
```
**result**
```shell
➜  base-conversion git:(master) ✗ gcc test.c conv.c -o test.out
➜  base-conversion git:(master) ✗ ./test.out 
func: test_bin_to_dec      passed
func: test_hex_to_dec      passed
func: test_oct_to_dec      passed
func: test_dec_to_oct      passed
func: test_12_to_oct       passed
➜  base-conversion git:(master) ✗ 
```

# other
**gcc version**
```shell
➜  base-conversion git:(master) ✗ gcc --version
gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
