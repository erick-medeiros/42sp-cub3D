# libft | 42sp

## Introduction
C programming can be very tedious when we doesn’t have access to the highly useful standard functions isnt? Alright, this project is about understanding the way these functions work essentially. Therefore, we should implement and learn how to use them. We are basically creating our own C library, and it will be helpful since we are going to use it in our next C school assignments. The idea is that, in this project we will be implementing our home-made functions from the library `libc`/`glibc` which will be very useful to get familiar with very basic algorithms, memory allocation, and specially to think of creative ways to code these functions.

## Function Overview
I'm actually expanding my libft throughout the year, and bellow is all functions avaiable at this moment: Ohh yea, the prefix `ft` stands for `f`orty `t`wo =)
| Function | Description |
| :------: | :---------: |
| `ft_atoi` | Convert a character string to an integer |
| `ft_bzero` | Zero a byte string |
| `ft_calloc` | A memory allocator which initializes the heap allocated memory |
| `ft_isalnum` | Checks for an alphanumeric character. (i.e `ft_isalpha || ft_isdigit`) |
| `ft_isalpha` | Checks for an alphabetic character |
| `ft_isascii` | Checks whether `c` is a 7-bit `unsigned char` value that fits into the ASCII character set |
| `ft_isdigit` | Checks for a digit (`0` through `9`) |
| `ft_isprint` | Checks for any printable character including space |
| `ft_itoa` | Convert the integer `n` into a character string |
| `ft_utoa` | Convert the unsigned integer `n` into a character string |
| `ft_ultoa` | Convert the unsigned long integer `n` into a character string |
| `ft_utoab` | Convert the unsigned integer `n` into a given base as character string |
| `ft_memcpy` | Copy memory area. This function copies `n` bytes from memory area `src` to memory area `dest` |
| `ft_memmove` | Same as `ft_memcpy`, but the memory areas may overlap here (prevent data lost) |
| `ft_memchr` | Scan memory for a character |
| `ft_memcmp` | Compare memory areas |
| `ft_memset` | Fill memory with a constant byte |
| `ft_split` | Extract tokens from strings |
| `ft_strchr` | Locate character in string |
| `ft_strrchr` | Reverse `ft_strchr` |
| `ft_strdup` | Duplicate an given string and gets a heap allocated one |
| `ft_strjoin` | Concatenates two strings allocating enough space in the heap first |
| `ft_strjoins` | Same as `ft_strjoin`, but it will free `s1` after concatenate both strings |
| `ft_strlcpy` | Copies up to `size - 1` characters from the NUL-terminated string `src` to `dst`, NUL-terminating the result |
| `ft_strlcat` | Appends the NUL-terminated string `src` to the end of `dst`. It will append at most `size - strlen(dst) - 1` bytes, NUL-terminating the result |
| `ft_strlen` | Calculate the length of a string |
| `ft_strmapi` | Invokes a callback function to every character in the given string |
| `ft_strncmp` | Compare part of two strings |
| `ft_strnstr` | Locate a substring in given `n` bytes |
| `ft_strtrim` | Remove occurrences of characters in a string from the start and end of a given character string `set` |
| `ft_substr` | Create a new character string from the n-th byte of an given string |
| `ft_tolower` | Transliterate uppercase characters to lowercase |
| `ft_toupper` | transliterate lowercase characters to uppercase |
| `ft_putchar_fd` | Write out a character to the given file descriptor |
| `ft_putendl_fd` | Write out a character string followed by a new line `\n` to a given file descriptor |
| `ft_putnbr_fd` | Write out a number to the given file descriptor |
| `ft_putstr_fd` | Write out a character string to the given file descriptor |
| `ft_putchar` | Write out a character to the standart output and returns `1` |
| `ft_putstr` | Write out a character string to the standart output and returns the number of bytes writen |
| `ft_putnstr` | Write out `n` bytes of a given string to the standart output and returns the number of bytes writen |
| `ft_putnbr` | Write out a integer value to the standart output and returns the number of bytes writen |
| `ft_putnbr_hex` | Write out a value in hexadecimal to the standart output and returns the number of bytes writen |
| `ft_putunbr` | Write out a unsigned integer to the standart output and returns the number of bytes writen |
| `ft_putptr` | Write out a memory location to the standart output and returns the number of bytes writen |
| `ft_free_matrix` | Frees the given matrix. (i.e. `ft_split` allocation) |
| `ft_lstnew` | Generates a new node |
| `ft_lstadd_front` | Insert a new node at the beginning of the list |
| `ft_lstadd_back` | Append a new node at the end of the list |
| `ft_lstsize` | Returns the number of nodes avaiable in the list |
| `ft_lstlast` | Retrieves the last node of the list |
| `ft_lstclear` | Frees a given node and every node after the given one |
| `ft_lstmap` | Applies a function to a copy of the list, freeing when necessary |
| `ft_lstiter` | Applies a function call to the content of every node of the list |
| `ft_lstdelone` | Frees and applies a function call to the content of a given node |
| `ft_gnl`| Function that returns a line read from a given file descriptor. See [get_next_line](https://github.com/ichmi/get_next_line#gnl--42sp) |
| `ft_printf` | Home-made `printf` function from `<stdio.h>`. See [ft_printf](https://github.com/ichmi/ft_printf#ft_printf--42sp) |

## Requirements
To use it, you should have the following packages installed:
```bash
apt-get install clang make
```

## Usage
First, you should clone the repo, and then you can just make it:
```bash
git clone https://github.com/ichmi/libft.git
make
```
It will generate an archive file called `libft.a` which you can use ir order to use these functions in your project:
```bash
# This command will check all object files avaiable inside the archive:
ar -t libft.a
```

Once you got the static library, you should compile your program with your favorite compiler with one of the following ways:
```bash
# if the library is avaiable in your current working directory with you entry point (i.e. main function), you can:
clang main.c -I. -L. -lft 
# or even
clang main.c -lft 

# if isnt, you could specify the include path -I<path> and the path where we can find the library -L<path> followed by the lib -l<libname>:
clang main.c -Ilibft/ -Llibft -lft

# Another way would be providing the archive file during your program compilation (Personally I dont like it):
clang main.c libft.a
clang main.c libft/libft.a
```
