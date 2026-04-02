#ifndef stream_h
#define stream_h

struct stream {
  int (*available)();
  char (*peek)();
  char (*read)();
};

#endif