int num_jewels_in_stones(char *j, char *s) {
  char char_index[128];
  char *p;
  int count = 0;
  p = j;
  for(int i = 0; i < 128; i++) {
    char_index[i] = 0;
  }
  while(*p != '\0') {
    char_index[*p] = 1;
    p++;
  }
  p = s;
  while(*p != '\0') {
    if (char_index[*p] == 1) {
      count++;
    }
    p++;
  }
  return count;
}
