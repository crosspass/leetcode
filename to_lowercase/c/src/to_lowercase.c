char* toLowerCase(char* str) {
  char *s = str;
  char char_index[128];
  char_index[65] = 'a';
  char_index[66] = 'b';
  char_index[67] = 'c';
  char_index[68] = 'd';
  char_index[69] = 'e';
  char_index[70] = 'f';
  char_index[71] = 'g';
  char_index[72] = 'h';
  char_index[73] = 'i';
  char_index[74] = 'j';
  char_index[75] = 'k';
  char_index[76] = 'l';
  char_index[77] = 'm';
  char_index[78] = 'n';
  char_index[79] = 'o';
  char_index[80] = 'p';
  char_index[81] = 'q';
  char_index[82] = 'r';
  char_index[83] = 's';
  char_index[84] = 't';
  char_index[85] = 'u';
  char_index[86] = 'v';
  char_index[87] = 'w';
  char_index[88] = 'x';
  char_index[89] = 'y';
  char_index[90] = 'z';

  while(*s != '\0') {
    if('A' <= *s && *s <= 'Z') {
      *s = char_index[*s];
    }
    s++;
  }
  return str;
}
