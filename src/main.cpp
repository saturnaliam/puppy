// horribly messy c++ code, enter at ur own risk
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

enum Ops {
  OP_ADD,
  OP_SUB,
  OP_OUT,
};

void panic(std::string message) {
  std::cerr <<  message << "\n";
  exit(1);
}

std::string tolower(std::string input) {
  std::string lower;

  for (char c : input) {
    lower += tolower(c);
  }

  return lower;
}

std::vector<std::string> formatString(std::string input) {
  std::string buffer;

  std::vector<std::string> program;

  for (int i = 0; i < input.size(); i++) {
    char c = tolower(input[i]);
    char C = input[i];
    switch (c) {
      case 'k':
      case 'p':
      case 'b':
      case 'i':
      case 'y':
      case 'a':
      case 'r':
        buffer += C;

        if (c == 'k' || c == 'p') {
          program.push_back(buffer);
          buffer = "";
        }
        break;
      case ' ':
        if (tolower(input[i - 1]) == 'k' || tolower(input[i - 1]) == 'p' || input[i - 1] == ' ') {
          program.push_back(" ");
        }
        break;

      default:
        if (iswspace(C)) break;
        std::string panicMessage = "PUPPY does not understand the character ";
        panic(panicMessage + C + "!");
    }
  }

  if (buffer != "") program.push_back(buffer);
  return program;
}

std::vector<Ops> scan(std::vector<std::string> input) {
  std::vector<Ops> program;

  for(std::string command: input) {
    std::string lowercase = tolower(command);
    if (lowercase != "yip" && lowercase != "bark" && lowercase != " ") {
      std::string panicMessage = "PUPPY does not understand the word ";
      panic(panicMessage + command + "!");
    }

    if (lowercase == " ") {
      program.push_back(OP_OUT);
    }

    for (char c : command) {
      if (islower(c)) {
        program.push_back(OP_SUB);
      } else if (isupper(c)) {
        program.push_back(OP_ADD);
      }
    }
  }

  return program;
}

void interpret(std::vector<Ops> instructions) {
  int cell = 0;

  for (auto op : instructions) {
    switch (op) {
      case OP_ADD:
        cell++;
        break;
      case OP_SUB:
        cell--;
        break;
      case OP_OUT:
        std::cout << (char)cell;
        break;
    }
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "usage: puppy <input file>\n";
    return 1;
  }

  std::ifstream file(argv[1]);

  std::string contents, line;
  while (std::getline(file, line)) {
    contents += line;
  }

  file.close();

  std::vector<std::string> program = formatString(contents);
  std::vector<Ops> ops = scan(program);

  interpret(ops);

  return 0;
}