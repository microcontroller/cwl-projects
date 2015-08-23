#ifndef   __PASS_CHECK_H
#define   __PASS_CHECK_H

#define PASS_VULN_TRIVIAL (1)
#define PASS_VULN_EASY    (1)

#define BAD_PASS_DELAY    (1000)

#define DEFAULT_PW        ("password")
#define DEFAULT_PW_LEN    (8)

uint8_t read_pass(void);
uint8_t test_pass(void);

#endif // __PASS_CHECK_H