// SPDX-License-Identifier: GPL-2.0-only
#include "asm-generic/errno-base.h"
#include "linux/kstrtox.h"
#include "linux/minmax.h"
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/string.h>

#define LAST_ERROR_CODE 134UL

static dev_t error_tran_dev; // Holds the major and minor number for our driver
static struct cdev error_tran_cdev; // Char device. Holds fops and device number

static unsigned int latest_error_code = 0;

static char *error_table[] = {
    [0] = "No error!\n",
    [1] = "Operation not permitted.\n",
    [2] = "No such file or directory.\n",
    [3] = "No such process.\n",
    [4] = "Interrupted system call.\n",
    [5] = "I/O error.\n",
    [6] = "No such device or address.\n",
    [7] = "Argument list too long.\n",
    [8] = "Exec format error.\n",
    [9] = "Bad file number.\n",
    [10] = "No child processes.\n",
    [11] = "Try again.\n",
    [12] = "Out of memory.\n",
    [13] = "Permission denied.\n",
    [14] = "Bad address.\n",
    [15] = "Block device required.\n",
    [16] = "Device or resource busy.\n",
    [17] = "File exists.\n",
    [18] = "Cross-device link.\n",
    [19] = "No such device.\n",
    [20] = "Not a directory.\n",
    [21] = "Is a directory.\n",
    [22] = "Invalid argument.\n",
    [23] = "File table overflow.\n",
    [24] = "Too many open files.\n",
    [25] = "Not a typewriter.\n",
    [26] = "Text file busy.\n",
    [27] = "File too large.\n",
    [28] = "No space left on device.\n",
    [29] = "Illegal seek.\n",
    [30] = "Read-only file system.\n",
    [31] = "Too many links.\n",
    [32] = "Broken pipe.\n",
    [33] = "Math argument out of domain of func.\n",
    [34] = "Math result not representable.\n",
    [35] = "Resource deadlock would occur.\n",
    [36] = "File name too long.\n",
    [37] = "No record locks available.\n",
    [38] = "Invalid system call number.\n",
    [39] = "Directory not empty.\n",
    [40] = "Too many symbolic links encountered.\n",
    [42] = "No message of desired type.\n",
    [43] = "Identifier removed.\n",
    [44] = "Channel number out of range.\n",
    [45] = "Level 2 not synchronized.\n",
    [46] = "Level 3 halted.\n",
    [47] = "Level 3 reset.\n",
    [48] = "Link number out of range.\n",
    [49] = "Protocol driver not attached.\n",
    [50] = "No CSI structure available.\n",
    [51] = "Level 2 halted.\n",
    [52] = "Invalid exchange.\n",
    [53] = "Invalid request descriptor.\n",
    [54] = "Exchange full.\n",
    [55] = "No anode.\n",
    [56] = "Invalid request code.\n",
    [57] = "Invalid slot.\n",
    [59] = "Bad font file format.\n",
    [60] = "Device not a stream.\n",
    [61] = "No data available.\n",
    [62] = "Timer expired.\n",
    [63] = "Out of streams resources.\n",
    [64] = "Machine is not on the network.\n",
    [65] = "Package not installed.\n",
    [66] = "Object is remote.\n",
    [67] = "Link has been severed.\n",
    [68] = "Advertise error.\n",
    [69] = "Srmount error.\n",
    [70] = "Communication error on send.\n",
    [71] = "Protocol error.\n",
    [72] = "Multihop attempted.\n",
    [73] = "RFS specific error.\n",
    [74] = "Not a data message.\n",
    [75] = "Value too large for defined data type.\n",
    [76] = "Name not unique on network.\n",
    [77] = "File descriptor in bad state.\n",
    [78] = "Remote address changed.\n",
    [79] = "Can not access a needed shared library.\n",
    [80] = "Accessing a corrupted shared library.\n",
    [81] = ".lib section in a.out corrupted.\n",
    [82] = "Attempting to link in too many shared libraries.\n",
    [83] = "Cannot exec a shared library directly.\n",
    [84] = "Illegal byte sequence.\n",
    [85] = "Interrupted system call should be restarted.\n",
    [86] = "Streams pipe error.\n",
    [87] = "Too many users.\n",
    [88] = "Socket operation on non-socket.\n",
    [89] = "Destination address required.\n",
    [90] = "Message too long.\n",
    [91] = "Protocol wrong type for socket.\n",
    [92] = "Protocol not available.\n",
    [93] = "Protocol not supported.\n",
    [94] = "Socket type not supported.\n",
    [95] = "Operation not supported on transport endpoint.\n",
    [96] = "Protocol family not supported.\n",
    [97] = "Address family not supported by protocol.\n",
    [98] = "Address already in use.\n",
    [99] = "Cannot assign requested address.\n",
    [100] = "Network is down.\n",
    [101] = "Network is unreachable.\n",
    [102] = "Network dropped connection because of reset.\n",
    [103] = "Software caused connection abort.\n",
    [104] = "Connection reset by peer.\n",
    [105] = "No buffer space available.\n",
    [106] = "Transport endpoint is already connected.\n",
    [107] = "Transport endpoint is not connected.\n",
    [108] = "Cannot send after transport endpoint shutdown.\n",
    [109] = "Too many references: cannot splice.\n",
    [110] = "Connection timed out.\n",
    [111] = "Connection refused.\n",
    [112] = "Host is down.\n",
    [113] = "No route to host.\n",
    [114] = "Operation already in progress.\n",
    [115] = "Operation now in progress.\n",
    [116] = "Stale file handle.\n",
    [117] = "Structure needs cleaning.\n",
    [118] = "Not a XENIX named type file.\n",
    [119] = "No XENIX semaphores available.\n",
    [120] = "Is a named type file.\n",
    [121] = "Remote I/O error.\n",
    [122] = "Quota exceeded.\n",
    [123] = "No medium found.\n",
    [124] = "Wrong medium type.\n",
    [125] = "Operation Canceled.\n",
    [126] = "Required key not available.\n",
    [127] = "Key has expired.\n",
    [128] = "Key has been revoked.\n",
    [129] = "Key was rejected by service.\n",
    [130] = "Owner died.\n",
    [131] = "State not recoverable.\n",
    [132] = "Operation not possible due to RF-kill.\n",
    [133] = "Memory page has hardware error.\n",
    [134] = "Wrong file type for the intended operation.\n",
    [LAST_ERROR_CODE + 1] = "Invalid error code.\n"
};


static ssize_t error_tran_read(struct file *file, char __user *buf, size_t size,
               loff_t *ppos)
{
    // Return the string corresponding to the current driver state
    return simple_read_from_buffer(buf, size, ppos, error_table[latest_error_code],
                       strlen(error_table[latest_error_code]));
}

static ssize_t error_tran_write(struct file *file, const char __user *buf,
                size_t size, loff_t *ppos)
{
    char input[8];
    int ret;
    int len = min(sizeof(input) - 1, size);

    // Copy the first character written to this device to 'value'
    if(copy_from_user(input, buf, len)){
        return -EFAULT;
    }
    input[len] = '\0';

    ret = kstrtouint(input, 10, &latest_error_code);

    if(latest_error_code > LAST_ERROR_CODE || ret < 0 || error_table[latest_error_code] == NULL) latest_error_code = LAST_ERROR_CODE + 1;

    return size; // We only read one character from the written string
}

// Define the functions that implement our file operations
static struct file_operations error_tran_fops =
{
    .read = error_tran_read,
    .write = error_tran_write,
};

static int __init error_tran_init(void)
{
    int ret;

    // Allocate a major and a minor number
    ret = alloc_chrdev_region(&error_tran_dev, 0, 1, "error_tran");
    if (ret)
        pr_err("Failed to allocate device number\n");

    // Initialize our character device structure
    cdev_init(&error_tran_cdev, &error_tran_fops);

    // Register our character device to our device number
    ret = cdev_add(&error_tran_cdev, error_tran_dev, 1);
    if (ret)
        pr_err("Char device registration failed\n");

    pr_info("error_tran driver initialized!\n");

    return 0;
}

static void __exit error_tran_exit(void)
{
    // Clean up our mess
    cdev_del(&error_tran_cdev);
    unregister_chrdev_region(error_tran_dev, 1);

    pr_info("error_tran driver exiting!\n");
}

module_init(error_tran_init); // Register our functions so they get called when our
module_exit(error_tran_exit); // module is loaded and unloaded

MODULE_AUTHOR("");
MODULE_DESCRIPTION("");
MODULE_LICENSE("GPL");