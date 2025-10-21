#include "main.h"

# === STEP 1: Go inside your project folder ===
cd ~/holbertonschool-low_level_programming/more_functions_nested_loops

# === STEP 2: Remove extra files that cause the checker to fail ===
rm -f 0-main.c 0-isuper

# === STEP 3: Make sure only the correct files remain ===
ls
# You should now see only:
# 0-isupper.c  main.h

# === STEP 4: Double-check the content of 0-isupper.c ===
cat > 0-isupper.c << 'EOF'
#include "main.h"

/**
 * _isupper - checks for uppercase character
 * @c: the character to check
 *
 * Return: 1 if c is uppercase, 0 otherwise
 */
int _isupper(int c)
{
    if (c >= 'A' && c <= 'Z')
        return (1);
    else
        return (0);
}
