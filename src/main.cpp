import controller;
import std;

using namespace std;

int main() {
  try {
    Controller().process();
  } catch (const exception &err) {
    cerr << "Error: " << err.what() << endl;
    return 1;
  }

  return 0;
}
