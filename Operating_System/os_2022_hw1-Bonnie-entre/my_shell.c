// sudo mount –t vboxsf OS /home/os2022/文件/OS
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


/*
  Function Declarations for builtin shell commands:
 */
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_echo(char **args, int len);
int lsh_pid(char **args);
int lsh_record(char **args);

/*
  Function Declarations for loop:
 */
char ***lsh_split_line(char line[], int *pipe_num, int **pipe_word_num);
int loop_pipe(char ***cmd, int cmd_num, int *cml_len);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "help",
  "mypid",
  "record",
};

int (*builtin_func[]) (char **) = {
  &lsh_help,
  &lsh_pid,
  &lsh_record,
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

// record
int count_record = 0;
char record_arr[17][64];

/*
  Builtin function implementations.
*/

int lsh_help(char **args)
{
  int i;
  printf("Bonnie's shell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");
  printf("1: help\n2: cd:\n3: echo:\n4: record:\n5: replay:\n6: mypid:\n7: exit:\n\n");
  printf("Use the man command for information on other programs.\n");
  exit(0);
  return 1;
}

int lsh_echo(char **args, int len){
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"echo\"\n");
        return 1;
    }

    int k=1;
    if(!strcmp(args[1], "-n")){     // withou -n
      k=2;
    }
                        
    for(; k<len; k++){
      printf("%s ", args[k]);
    }
    if(strcmp(args[1], "-n")){     // withou -n
      fprintf(stdout, "\n");
    }

  exit(0);
  return 1;
}

int pid_ch_flag = 0;
int lsh_pid(char **args){
    if (args[1] == NULL) {
          fprintf(stderr, "lsh: expected argument to \"mypid\"\n");
          return 1;
    }

    // char buf[100];
    int id;
    if(!strcmp( args[1],"-i")){
        printf("%d\n", getppid());
    }
    else if(!strcmp( args[1],"-c")){
        char **a = malloc(sizeof(char*)*2);
        a[0] = malloc(sizeof(char)*4);
        a[1] = malloc(sizeof(char)*64);
        a[0] = "cat";
        sprintf(a[1], "/proc/%d/task/%d/children",atoi(args[2]) ,atoi(args[2]));
        pid_ch_flag = 1;
        int pid=fork();
        if(pid==0)
            execvp(a[0], a);
        else{
            wait(NULL);
            printf("\n");
        }
    }
    else if(!strcmp( args[1],"-p")){
        char *str1 = malloc(sizeof(char)*BUFSIZ);
        sprintf(str1, "cat /proc/%d/status | grep PPid",atoi(args[2]));

        int pipe_num, *pipe_word_num;
        char ***args_pipe = lsh_split_line(str1, &pipe_num, &pipe_word_num);
        return loop_pipe(args_pipe, pipe_num, pipe_word_num);
    }
    exit(0);
    return 1;
}

int lsh_record(char **args){
  printf("history cmd:\n");
  if(count_record>=16){
      for(int i=0; i<16; i++){
          printf("%d: %s\n", i+1, record_arr[i]);
      }
  }
  else{
      for(int i=0; i<count_record%16; i++){
        // for(int j=0; j<strlen(record_arr[i]); j++)
          printf("%d: %s\n", i+1, record_arr[i]);
      }
  }
  exit(0);
  return 1;
}

/*
  Loop Implement of cml
*/

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *lsh_read_line(void)
{
#ifdef LSH_USE_STD_GETLINE
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // We received an EOF
    } else  {
      perror("lsh: getline\n");
      exit(EXIT_FAILURE);
    }
  }
  return line;
#else
#define LSH_RL_BUFSIZE 1024
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
#endif
}

char ***lsh_split_line(char line[], int *pipe_num, int **pipe_word_num) {
    //先算出有幾個pipe
    int n = 1;
    for(int i=0; line[i] != '\0'; i++) {
        if(line[i] == '|')
            n++;
    }

    int *arr = (int*)malloc(n*sizeof(int));  //each pipe has how many words
    int cur_n = 0;
    int word_num = 0;
    int pos = 0;

    //計算arr[]
    for(pos=0; line[pos] != '\0'; pos++) {
        if(line[pos] == ' ')
            word_num++;
        if(line[pos] == '|') {
            arr[cur_n] = word_num;
            word_num = 0;
            cur_n++;
            pos++;
        }
    }
    arr[cur_n] = word_num + 1;
    
    char ***args_pipe = (char***)malloc(n * sizeof(char**));
    char *tmp = (char*)malloc(10 * sizeof(char));
    int now_tmp_len = 0;
    pos = 0;
    
    for(int i=0; i<n; i++) {
        args_pipe[i] = (char**)malloc(arr[i] * sizeof(char*));

        for(int j=0; j<arr[i]; j++)
        {
            while(line[pos] != ' ' && line[pos] != '\0') {
                tmp[now_tmp_len++] = line[pos];
                pos++;
            }
            tmp[now_tmp_len] = '\0';
            now_tmp_len++;

            char *str = (char*)malloc(now_tmp_len * sizeof(char));
            strcpy(str, tmp);
            args_pipe[i][j] = str;

            tmp = (char*)malloc(10 * sizeof(char));
            now_tmp_len = 0;

            pos++;
        }
        
        //這時候 pos 應該是 '|'
        while(line[pos] == '|' || line[pos] == ' ')
            pos++;
    }

    *pipe_num = n;
    (*pipe_word_num) = arr;
    return args_pipe;
}

int loop_pipe(char ***cmd, int cmd_num, int *cml_len) {
    if (cmd[0] == NULL) {
    // An empty command was entered.
    return 1;
    }

    int p[2];
    pid_t pid;
    int fd_in = 0;
    int status;
    char filename_in[100];
    char filename_out[100];
    int in=0, out=0, background=0;
    int is_bulli = 0;
    for(int i=0; i<cmd_num; i++) {
        // exit
        if(!strcmp((*cmd)[0], "exit")){
            exit(0);
            return 0;
        }        
        // cd
        if(!strcmp((*cmd)[0],"cd")){
          if (chdir((*cmd)[1]) != 0) {
            perror("lsh");
          }
          continue;
        }

        // <
        for(int k=0; k<cml_len[i]; k++){
            if(strcmp((*cmd)[k], "<") == 0){
                for(int j=k; j<cml_len[i]-1; j++){
                  (*cmd)[j] = (*cmd)[j+1];
                }
                strcpy(filename_in, (*cmd)[k+1]);
                in = 1;
                break;
            }
        }
        // >
        for(int k=0; k<cml_len[i]; k++){
          if(!strcmp((*cmd)[k], ">")){
              (*cmd)[k] = NULL;
              strcpy(filename_out, (*cmd)[k+1]);
              out = 1;
              break;
          }
        }
        // &
        if(i==cmd_num-1){
          if(!strcmp((*cmd)[cml_len[i]-1], "&")){
            background = 1;
            (*cmd)[cml_len[i]-1] = NULL;
          }
        }


        // pipe
        pipe(p);
        pid = fork();
        if (pid == -1) {
            exit(0);
        }
        
        else if (pid == 0) {
            dup2(fd_in, STDIN_FILENO); //change the input according to the old one
            if(i + 1 < cmd_num)
                dup2(p[1], STDOUT_FILENO);
            
            //"<"
            else if(in){
              int fd0 = open(filename_in, O_RDONLY);
              dup2(fd0, STDIN_FILENO);
              close(fd0);
              (*cmd)[2] = NULL;
            }
            // ">"
            if(out){
              int fd1 = creat(filename_out, 0600);
              dup2(fd1, STDOUT_FILENO);
              close(fd1);
            }  

            // If there is no match system call
            for (int i = 0; i < lsh_num_builtins(); i++) {
                if(!strcmp((*cmd)[0],"echo")){
                    if(out)
                        status = lsh_echo(*cmd, cml_len[i]-2);
                    else
                        status = lsh_echo(*cmd, cml_len[i]);
                    exit(0);
                    return status;    
                }

                if(!strcmp((*cmd)[0], builtin_str[i])) {
                    int status = (*builtin_func[i])(*cmd);
                    return status;
                }
            } 
                
            
        execvp((*cmd)[0], *cmd);
        close(p[0]);
        exit(0);
        }
        else {  //parent
            if(!background){
              waitpid(pid,NULL,0);  //wait child to die
            }
            if(background && i==cmd_num-1){
              printf("[PID]: %d\n", pid);
            }

            fd_in = p[0]; //save the input for the next command
            cmd++;
            close(p[1]);
        }
    }
    if(!background){
        if(pid_ch_flag){
          printf("\n");
          pid_ch_flag = 0;
        }
    }
    return 1;
}

void lsh_loop(void)
{
    int status;
    char *line = NULL;
    int pipe_num, *pipe_word_num;
    int pid_line=0;
    printf("======================================================\n\
* welcome to bonnie's shell:                         *\n\
*                                                    *\n\
* Type \"help\" to see builtin functions.              *\n\
*                                                    *\n\
* If you want to do things below:                    *\n\
* + redirection: \">\" ot \"<\"                          *\n\
* + pipe: \"|\"                                        *\n\
* + background: \"&\"                                  *\n\
* Make sure they are seperated by \"(space)\".         *\n\
*                                                    *\n\
* Enjoy it!!                                         *\n\
======================================================\n\
");

    do {
      printf(">>> $ ");
      line = lsh_read_line();


    // record_command
    if(count_record>=16){
      for(int i=0; i<15; i++){
        for(int j=0; j<strlen(record_arr[i+1]); j++)
            record_arr[i][j] = record_arr[i+1][j];
        record_arr[i][strlen(record_arr[i+1])] = '\0';
      }
      for(int k=0; k<strlen(line); k++){
        record_arr[15][k] = line[k];
      }
      record_arr[15][strlen(line)] = '\0';
    }
    else{
      for(int k=0; k<strlen(line); k++){
        record_arr[count_record][k] = line[k];
      }
      record_arr[count_record][strlen(line)] = '\0';
    }

    // check replay
    if(line[0]=='r' && line[1]=='e' && line[2]=='p' && line[3]=='l' && line[4]=='a' && line[5]=='y'){
        char tmp[10];
        int t=0, i;
        for(i=7; line[i]!=' '; i++){
          tmp[t++] = line[i];
        }
        tmp[t]='\0';

        char tmp_line[64];
        t = 0;
        for(;i<strlen(line); i++){
          tmp_line[t++] = line[i];
        }
        tmp_line[t] = '\0';
        
        //change line
        int len_insert_cmd = strlen(record_arr[atoi(tmp)-1]);
        int k;
        for(k=0; k<len_insert_cmd; k++){
          line[k] = record_arr[atoi(tmp)-1][k];
        }
        // concate line
        if(strlen(tmp_line)){
          for(i=0; i< strlen(tmp_line); i++)
            line[k++] = tmp_line[i];
        }
        line[k] = '\0';    
    }

    char ***args_pipe = lsh_split_line(line, &pipe_num, &pipe_word_num);
    status = loop_pipe(args_pipe, pipe_num, pipe_word_num);


    count_record++;
    if(!pid_line)
      free(line);
    else
      pid_line = 0;
    free(args_pipe);
    } while (status);
}


int main() {

    lsh_loop();
    
    return EXIT_SUCCESS;
}
