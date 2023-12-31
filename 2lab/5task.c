#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*
  Изменить программу п. 3 так, чтобы родительский процесс выполнялся,
  не ожидая завершения порожденного процесса. Что произойдет с
  порожденным процессом, когда он завершится? Как убить зомби?
  После завершения порожденный процесс станет зомби, если родительский процесс ещё не вызвал wait()
  Убивать зомби самому не нужно, система сама завершит процесс зомби после завершения
  родительского процесса. Чтобы убить зомби надо убить его родительский процесс.
  Для избежания появления зомби желательно использовать wait()
*/

void Err_Handler(int line);

extern char **environ;

int main(int argc, char const *argv[])
{
  int res = 0;

  res = fork();
  if (res == -1)
    Err_Handler(__LINE__);
  if (!res) { //  Потомок
    printf("Процесс потомок. PID: %d, PPID: %d\n", getpid(), getppid());
    printf("Выполнение потомка\n");
    printf("\nЗавершение потомка с кодом 1. PPID = %d\n", getppid());
    exit(1);
  } else {    //  Родитель
    printf("Процесс родитель. PID: %d, PPID: %d\n", getpid(), getppid());
    printf("Выполнение процесса родителя\n");
    sleep(3);
    execlp("ps", "ps", NULL); //  вывод запущенных процессов
    printf("Завершение процесса родителя\n");
    exit(0);
  }
  return 0;
}
/*
  l и v указывают, передаются ли аргументы списком
  или массивом. Символ p указывает, что система будет искать указанный файл по
  полному пользовательскому пути. В командах, где используются варианты с p,
  можно указать только имя файла, если он находится в пределах пользовательско­
  го пути.
*/
/*-----------------------------------------------------------------------*/
void Err_Handler(int line)
{
  printf("Errno value:\t%d\n", errno);
  fprintf(stderr, "Error occured! %s\n %s:%d\n", strerror(errno), __FILE__, line);
  exit(0);
}
