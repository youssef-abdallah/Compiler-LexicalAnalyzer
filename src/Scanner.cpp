#include "Scanner.h"

Scanner::Scanner() {

}

Scanner& Scanner::getInstance() {
    static Scanner instance;
    return instance;
}
