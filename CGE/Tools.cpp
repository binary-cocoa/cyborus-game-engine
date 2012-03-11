#include "Tools.h"
#include "Memory.h"

#include <cstdlib>
#include <cstdio>
#include <cctype>

namespace CGE
{
    bool caseInsensitiveEquals(const char* inA, const char* inB)
    {
        while (true)
        {
            char a = tolower(*inA++);
            char b = tolower(*inB++);

            if (a != b)
                return false;
            else if (!a)
                return true;
        }
    }

    char* fileToBuffer(const char* inFile)
    {
        FILE* f = fopen(inFile, "r");

        if (!f) return NULL;

        fseek(f, 0, SEEK_END);

        size_t length = ftell(f);

        fseek(f, 0, SEEK_SET);

        char* outBuffer = NULL;

        if (length > 0)
        {
            outBuffer = (char*)allocate(length + 1);

            if (outBuffer)
            {
                size_t r = fread(outBuffer, sizeof(char), length, f);

                if (!r)
                {
                    release(outBuffer);
                    return NULL;
                }

                outBuffer[length] = '\0';
            }
        }

        fclose(f);
        return outBuffer;
    }


}
