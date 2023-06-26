#include "platform/fatfs/ff.h"

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <fcntl.h>

#include "events.h"

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define MAX_FDS 256
typedef struct file_desc
{
	const char* path;
	FIL fil;
} file_desc;
static file_desc fds[MAX_FDS];

extern int __io_putchar(int ch) __attribute__((weak));

#define SERIAL_RCV_BUF_LEN 255
#define SERIAL_MAX_INPUT_EVS 16


char serial_rcv_buf[SERIAL_RCV_BUF_LEN+1];
static int rcv_buf_idx = 0;
volatile int rcv_buf_rdy = 0;

serial_com_packet_t input_events[SERIAL_MAX_INPUT_EVS];
volatile int input_event_count = 0;

volatile uint8_t ev_buffer[128];
static int input_length_remaining = 0;

void stm32_input_rcv(serial_com_packet_t* c)
{
	if (input_event_count > SERIAL_MAX_INPUT_EVS)
		return;

	input_events[input_event_count] = *c;
	++input_event_count;
}

void stm32_serial_rcv(char c)
{
	putchar(c);

	if (rcv_buf_idx >= SERIAL_RCV_BUF_LEN)
		return;
	if (rcv_buf_rdy)
		return;

	if (c == '\n' || c == '\r')
	{
		serial_rcv_buf[rcv_buf_idx] = '\0';
		rcv_buf_rdy = 1;
		rcv_buf_idx = 0;
	}
	// backspace
	else if (c == '\b' || c == 0x7F)
	{
		if (rcv_buf_idx > 0)
			--rcv_buf_idx;
		serial_rcv_buf[rcv_buf_idx] = '\0';
	}
	else
	{
		serial_rcv_buf[rcv_buf_idx++] = c;
	}
}

static int find_free_fd()
{
	for (int i = STDERR_FILENO + 1; i < MAX_FDS; ++i)
	{
		if (fds[i].path == 0)
			return i;
	}

	assert(0);
	return -1;
}

int	mkdir (const char *_path, mode_t __mode )
{
	return f_mkdir(_path) == FR_OK ? 0 : -1;
}

int fsync(int fildes)
{
	return f_sync(&fds[fildes].fil) == FR_OK ? 0 : -1;
}

char *getcwd(char *buf, size_t size)
{
	if (f_getcwd(buf, size) != FR_OK)
		return 0;
	else
		return buf;
}

int chdir(const char *path)
{
	return f_chdir(path) == FR_OK ? 0 : -1;
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
  if (file == STDIN_FILENO) {
	  return EIO;
  }


	unsigned int count = 0;
	f_read(&fds[file].fil, ptr, len, &count);
	return count;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
  if (file == STDOUT_FILENO || file == STDERR_FILENO) {
	  for (int DataIdx = 0; DataIdx < len; DataIdx++)
	  {
	    __io_putchar(*ptr++);
	  }
	  return len;
  }

	unsigned int count = 0;
	f_write(&fds[file].fil, ptr, len, &count);
	return count;
}



int _close(int file)
{
	if (file >= STDIN_FILENO && file <= STDERR_FILENO)
	{
	  return 0;
	}

	if (f_close(&fds[file].fil) != FR_OK)
		return -1;
	fds[file].path = 0;
	return 0;
}


int _fstat(int file, struct stat *st)
{
  if (file >= STDIN_FILENO && file <= STDERR_FILENO) {
	st->st_mode = S_IFCHR;
	return 0;
  }

  FILINFO info;
  if (f_stat(fds[file].path, &info) != FR_OK)
	  return -1;
  st->st_size = info.fsize;
  st->st_mode = info.fattrib == AM_DIR ? S_IFDIR : S_IFREG;
  return 0;
}

int _isatty(int file)
{
  if (file >= STDIN_FILENO && file <= STDERR_FILENO)
	return 1;

  return 0;
}

int _lseek(int file, int ptr, int dir)
{
  if (file >= STDIN_FILENO && file <= STDERR_FILENO)
	return -1;

  int base = 0;
  if (dir == SEEK_CUR)
	  base = f_tell(&fds[file].fil);
  else if (dir == SEEK_END)
	  base = f_size(&fds[file].fil);
  int abs_offset = base + ptr;
  f_lseek(&fds[file].fil, abs_offset);
  return abs_offset;
}

int _open(char *path, int flags, ...)
{
	int fd = find_free_fd();
	fds[fd].path = path;

	unsigned fat_flags = FA_READ;
	if (flags & O_WRONLY)
		fat_flags |= FA_WRITE;
	if (flags & O_RDWR)
		fat_flags |= FA_READ | FA_WRITE;
	if (flags & O_APPEND)
		fat_flags |= FA_OPEN_APPEND;
	//if (flags & O_CREAT)
	//	fat_flags |= FA_CREATE_NEW;
	if (flags & O_TRUNC)
		fat_flags |= FA_CREATE_ALWAYS;
	if (flags & O_EXCL)
		fat_flags |= FA_CREATE_NEW;

	if (f_open(&fds[fd].fil, path, fat_flags) == FR_OK)
		return fd;
	else
		return -1;
}

int _wait(int *status)
{
  (void)status;
  errno = ECHILD;
  return -1;
}

int _unlink(char *name)
{
	return f_unlink(name) == FR_OK ? 0 : -1;
}

int _times(struct tms *buf)
{
  (void)buf;
  return -1;
}

int _stat(char *file, struct stat *st)
{
  FILINFO info;
  if (f_stat(file, &info) != FR_OK)
	  return -1;
  st->st_size = info.fsize;
  st->st_mode = info.fattrib == AM_DIR ? S_IFDIR : S_IFREG;
  return 0;
}

int _link(char *old, char *new)
{
  (void)old;
  (void)new;
  errno = EMLINK;
  return -1;
}
