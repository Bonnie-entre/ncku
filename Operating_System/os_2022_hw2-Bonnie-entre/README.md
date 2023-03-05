# OS_Homework2


## Some knowledge
### in My_proc.c
- `MODULE_LICENSE("GPL");
MODULE_AUTHOR("shallnet");` is necessary

### fprintf, snprintf, sprintf,

## when debug

### steps
1. make
2. make load
3. make exeMT
4. debug
5. make clean, make unload
6. repeat
<br>

### Compare the result
```diff result.txt ans.txt```

<br>

### /proc
- proc 為虛擬檔案一般難以修改刪除
- 內存有多個系統文件
<br>

### 查看 內核訊息
`dmesg | tail`
- including pr_info, printk...
<br>

### for vm
`// sudo mount –t vboxsf OS /home/os2022/文件/OS`

