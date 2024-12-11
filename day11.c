#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countDigits(long num) {
  int count = 0;
  while (num > 0) {
    num /= 10;
    ++count;
  }
  return count;
}

long getLeftDigits(long num, int digits) {
  return num / pow(10, digits);
}

long getRightDigits(long num, int digits) {
  return num % (long) pow(10, digits);
}

long blink(long stone, int to_blink, GHashTable *hash) {
  if (to_blink == 0) {
    return 1;
  }

  char *key = g_strdup_printf("%ld %d", stone, to_blink);
  void *lookup = g_hash_table_lookup(hash, key);

  if (lookup != NULL) {
    free(key);
    return (long) lookup;
  } else {
    long num_stones = 0;
    if (stone == 0) {
      num_stones += blink((long) 1, to_blink - 1, hash);
    } else {
      int stone_digits = countDigits(stone);
      if (stone_digits % 2 == 0) {
        num_stones += blink(getLeftDigits(stone, stone_digits / 2), to_blink - 1, hash);
        num_stones += blink(getRightDigits(stone, stone_digits / 2), to_blink - 1, hash);
      } else {
        num_stones += blink(stone * 2024, to_blink - 1, hash);
      }
    }
    g_hash_table_insert(hash, key, (void *) num_stones);
    free(key);
    return num_stones;
  }
}

int main() {
  FILE *file = fopen("input.txt", "r");
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  char *data = malloc(fileSize);
  fseek(file, 0, SEEK_SET);
  fread(data, 1, fileSize, file);
  fclose(file);

  GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
  long part1 = 0;
  long part2 = 0;

  char* stone = strtok(data, " ");
  while (stone != NULL) {
    long stone_num = atoi(stone);
    part1 += blink(stone_num, 25, hash);
    part2 += blink(stone_num, 75, hash);
    stone = strtok(NULL, " ");
  }

  printf("%ld %ld\n", part1, part2);

  free(data);
  g_hash_table_destroy(hash);
  return 0;
}
