#include <stdlib.h>
#include <string.h>
#include <minunit.h>

int check_uniq(char** words, int wordsSize, char *str);

int unique_mores_representations(char** words, int wordsSize) {
  if (wordsSize < 1) {
    return 0;
  }
  static char *mores[] = {
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--.."
  };
  char *mores_str[wordsSize], *p, *str, *more_str, *start;
  int count = 0;

  for(int i = 0; i < wordsSize; i++) {
    int len = strlen(words[i]);
    if ((start = p = malloc((len * 4 + 1) * sizeof(char))) == NULL) {
      return -1;
    }

    str = words[i];
    // printf("%s\n", str);

    for(; *str != '\0'; str++) {
      more_str = mores[(*str - 'a')];
      for (; *more_str != '\0'; p++, more_str++) {
        *p = *more_str;
      };
    }
    *p = '\0';

    // printf("%s\n", start);
    if (check_uniq(mores_str, count, start)) {
      mores_str[count] = start;
      count++;
    }
  }
  // printf("%d", count);
  for (int j = 0; j < count; j++) {
    free(mores_str[j]);
  }

  return count;
}

int check_uniq(char **words, int wordSize, char *str) {
  for(int i = 0; i < wordSize; i++) {
    if (strcmp(words[i], str) == 0) {
      return 0;
    }
  }
  return 1;
}


MU_TEST(test_check) {
  char *words[] = { "gin", "zen", "gig", "msg" };
  mu_assert_int_eq(2, unique_mores_representations(words, 4));
  
  char *words2[] = {"a"};
  mu_assert_int_eq(1, unique_mores_representations(words2, 1));
  
  char *words3[] = {};
  mu_assert_int_eq(0, unique_mores_representations(words3, 0));
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_check);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return minunit_status;
  /* char *s = "abcdef"; */
  /* char *p, *start; */
  /* p = (char *)malloc((strlen(s) + 1) * sizeof(char)); */
  /* while(*s != '\0') { */
  /*   printf("%c", *s); */
  /*   *p++ = *s++; */
  /* }; */
  /* *p = '\0'; */
  /* printf("%s\n", p); */
  /* char *s2 = "xyz"; */
  /* start = p = (char *)malloc((strlen(s2) + 1) * sizeof(char)); */
  /* while((*p++ = *s2++) != '\0'); */
  /* //strcpy(p, s); */
  /* printf("%s\n", start); */
}
