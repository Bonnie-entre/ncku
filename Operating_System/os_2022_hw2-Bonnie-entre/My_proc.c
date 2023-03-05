/* 
 * procfs1.c 
 */ 
 
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/proc_fs.h> 
#include <linux/uaccess.h> 
#include <linux/version.h> 
#include <linux/seq_file.h>
 
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0) 
#define HAVE_PROC_OPS 
#endif 
 
#define procfs_name "thread_info" 
#define PROCFS_MAX_SIZE		1024
// #define PROCFS_NAME 		"buffer1k"
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("bonnie");

static int mypid;
static long long time_count;
static int context_switch;

static struct proc_dir_entry *our_proc_file; 
static unsigned long procfs_buffer_size = 0;
static char procfs_buffer[PROCFS_MAX_SIZE];
static char read_buffer[PROCFS_MAX_SIZE];

static ssize_t procfile_read(struct file *filePointer, char __user *buffer, 
                             size_t buffer_length, loff_t *offset){ 

    // pr_info("procfile_read buffer is %s\n", buffer);
    sprintf(read_buffer, "ThreadId:%d Time:%lld(ms) context stwitch times: %d", mypid, time_count, context_switch);
    // pr_info("procfile_read read_buffer is %s\n", read_buffer);

    unsigned long read_len = sizeof(read_buffer);
    int complete = 0;
        
    if (copy_to_user(buffer, read_buffer, read_len) ) {    
        pr_info("procfile_read copy_to_user failed2\n"); 
        return -EFAULT;
        
    } else { 
        pr_info("procfile read %s read_buf is %s\n", filePointer->f_path.dentry->d_name.name, buffer);  
        *offset += read_len; 
    } 
    
    if(read_len)
        return complete;
    return read_len;
} 


static ssize_t procfile_write(struct file* file, const char __user *buffer , size_t count, loff_t *f_pos){
	pr_info("into procfile_write\n");

    // for MT_matrix
    struct task_struct* target_task;
    mypid = current->pid;
    target_task = pid_task(find_vpid(mypid), PIDTYPE_PID);
    
    time_count = target_task->utime / 1000000;
    context_switch = target_task->nvcsw + target_task->nivcsw;


    /* get buffer size */
	procfs_buffer_size = count;
	if (procfs_buffer_size > PROCFS_MAX_SIZE ) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	
	/* write data to the buffer */
	if ( copy_from_user(procfs_buffer, buffer, procfs_buffer_size) ) {
		return -EFAULT;
	}
    
    return count;
}


static const struct proc_ops proc_file_fops = { 
    .proc_read = procfile_read,
    .proc_write = procfile_write,
}; 
 

static int __init procfs1_init(void) 
{ 
    our_proc_file = proc_create(procfs_name, 0666, NULL, &proc_file_fops); 
    if (NULL == our_proc_file) { 
        proc_remove(our_proc_file); 
        pr_alert("Error:Could not initialize /proc/%s\n", procfs_name); 
        return -ENOMEM; 
    } 

    pr_info("/proc/%s created\n", procfs_name); 
    return 0; 
} 
 

static void __exit procfs1_exit(void) 
{ 
    proc_remove(our_proc_file); 
    pr_info("/proc/%s removed\n", procfs_name); 
} 


module_init(procfs1_init); 
module_exit(procfs1_exit); 
