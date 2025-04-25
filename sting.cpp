#include "string.hpp"
#include <cstring>
#include <algorithm>

String::~String() {
  delete[] Data;
}

String::String() : Data(new char[1]) {
  Data[0] = '\0';
}

String::String(const String& rhs) : Data(new char[strlen(rhs.Data) + 1]) {
  strcpy(Data, rhs.Data);
}

String::String(const char* data) : Data(new char[strlen(data) + 1]) {
  strcpy(Data, data);
}

String& String::operator=(const String& rhs) {
  if (this != &rhs) {
    String temp(rhs);
    swap(temp);
  }
  return *this;
}

String& String::operator+=(const String& rhs) {
  size_t new_len = strlen(Data) + strlen(rhs.Data);
  char* buffer = new char[new_len + 1];
  strcpy(buffer, Data);
  strcat(buffer, rhs.Data);
  delete[] Data;
  Data = buffer;
  return *this;
}

String& String::operator*=(unsigned int m) {
  size_t len = strlen(Data);
  size_t new_len = len * m;
  char* buffer = new char[new_len + 1];
  buffer[0] = '\0';

  for (unsigned int i = 0; i < m; ++i)
    strcat(buffer, Data);

  delete[] Data;
  Data = buffer;
  return *this;
}

bool String::operator==(const String& rhs) const {
  return strcmp(Data, rhs.Data) == 0;
}

bool String::operator<(const String& rhs) const {
  return strcmp(Data, rhs.Data) < 0;
}

size_t String::Find(const String& substr) const {
  char* pos = strstr(Data, substr.Data);
  if (!pos) return -1;
  return pos - Data;
}

void String::Replace(char oldSymbol, char newSymbol) {
  for (size_t i = 0; Data[i] != '\0'; ++i)
    if (Data[i] == oldSymbol) Data[i] = newSymbol;
}

size_t String::Size() const {
  return strlen(Data);
}

bool String::Empty() const {
  return Size() == 0;
}

char String::operator[](size_t index) const {
  return Data[index];
}

char& String::operator[](size_t index) {
  return Data[index];
}

void String::RTrim(char symbol) {
  size_t len = strlen(Data);
  while (len > 0 && Data[len - 1] == symbol)
    Data[--len] = '\0';
}

void String::LTrim(char symbol) {
  size_t len = strlen(Data);
  size_t start = 0;
  while (Data[start] == symbol)
    ++start;

  memmove(Data, Data + start, len - start + 1);
}

void String::swap(String& oth) {
  std::swap(Data, oth.Data);
}

String operator+(const String& a, const String& b) {
  String result(a);
  result += b;
  return result;
}

String operator*(const String& a, unsigned int b) {
  String result(a);
  result *= b;
  return result;
}

bool operator!=(const String& a, const String& b) {
  return !(a == b);
}

bool operator>(const String& a, const String& b) {
  return b < a;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  return out << str.Data;
}
