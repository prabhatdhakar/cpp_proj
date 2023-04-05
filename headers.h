#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include<sys/wait.h>
#include <functional>
#include<sys/stat.h>

std::string cmd(std::string);
enum Command {
                INVALID,
                LIST,
                PWD,
                CWD,
                MKD,
                RMD
   };
   