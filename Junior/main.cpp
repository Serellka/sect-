#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <ctime>

int main(int argc, char* argv[])
{
    std::cout << argv[1];
    std::map<std::string, std::string> dict;
    std::fstream inf("../data.xml", std::ifstream::in);
    std::fstream inpf("../template.txt", std::ifstream::in);
    std::fstream outf;
    bool f = !strcmp("-f", argv[1]);
    if (f)
        outf.open("../output.txt", std::ofstream::out);

    if (!inf && !inpf)
    {
        std::cerr << "Oh shit";
        return 0;
    }

    while (inf)
    {
        char c;
        inf >> c;
        if (c == '<') 
        {
            std::string sl = "";
            inf >> c;
            while (c != '>') 
            {
                sl += c;
                inf >> c;
            }
            if (sl == "root" || sl == "/root") continue;
            std::string str = "";
            inf >> c;
            while (c != '<') 
            {
                str += c;
                inf >> c;
            }
            if (sl != "current_date")
                dict.insert(std::make_pair(sl, str));
            else
            {
                time_t now = time(0);
                std::string dt = ctime(&now);
                dict.insert(std::make_pair(sl, dt));
            }
            while (c != '>') inf >> c;
        }
    }

    while (inpf)
    {
        std::string str;
        getline (inpf, str);
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] == '{')
            {
                i += 1;
                std::string sl = "";
                while (str[i] != '}')
                {
                    if (str[i] != '*')
                        sl += str[i];
                    i++;
                }
                if (f)
                    outf << dict.find(sl)->second;
                else
                    std::cout << dict.find(sl)->second;
            }
            else
            {
                if (f)
                    outf << str[i];
                else
                    std::cout << str[i];
            }
        }
        if (f)
            outf << '\n';
        else
            std::cout << '\n';
    }
}
