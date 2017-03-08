.PHONY: all clean

targets = ciphertext correlate server study

all : $(targets)

clean :
	@rm -fv $(targets)

# The -O3 flag was used in original article
CFLAGS = -lm -lcrypto -O3
