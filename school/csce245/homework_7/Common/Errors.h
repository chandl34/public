#ifndef ERRORS_H            /* -*- c++ -*- */
#define ERRORS_H

class Error {
public:
  Error(const char * msg) : msg(msg) { }
  const char * GetMsg() const { return msg; }
  virtual ~Error() {}
private:
  const char * msg;
};


class CodingError : public Error {
public:
  CodingError(const char* m) : Error(m) {}
};

class ParsingError : public Error {
public:
  ParsingError(const char* m) : Error(m) {}
};

class ConnectionError : public Error {
public:
  ConnectionError(const char* m) : Error(m) {}
};

class ConnectionResetError : public Error {
public:
    ConnectionResetError(const char* m) : Error(m) {}
}; 

class BoundryError : public Error {
public:
  BoundryError(const char* m) : Error(m) {}
};

#endif
