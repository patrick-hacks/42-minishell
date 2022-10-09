#ifndef LIB_ENVIRON_ENVIRON_H_
#define LIB_ENVIRON_ENVIRON_H_

extern char **g_environ;

int environ_init(void);
void environ_cleanup(void);
int environ_add(char *new_entry);
void environ_remove(char *entry);
char *environ_get(char *entry);

void environ_print(void);

#endif // LIB_ENVIRON_ENVIRON_H_
