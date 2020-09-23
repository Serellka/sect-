#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <ctime>

int parsing (std::ifstream &inf, std::map<std::string, std::string> &dict)
{
    try
    {
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
                if (!inf) throw "Oh shit file has been ended";
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
    }
    catch (const char* exception)
    {
        std::cerr << exception << '\n';
        return 0;
    }
    return 1;
}

int main(int argc, char* argv[])
{
    std::map<std::string, std::string> dict;
    std::ifstream inf("../data.xml");
    std::ifstream inpf("../template.txt");
    std::ofstream outf;
    bool f = !strcmp("-f", argv[1]);
    if (f)
        outf.open("../output.txt");

    try
    {
        if (!inf && !inpf)
            throw "We have no files with such titles";
    }
    catch (const char* exception)
    {
        std::cerr << exception << '\n';
        return 1;
    }

    if(!parsing(inf, dict)) return 1;

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
                try
                {
                    while (str[i] != '}')
                    {
                        if (str[i] != '*')
                            sl += str[i];
                        i++;
                        if (i == str.size()) throw "Oh shit that was out of range";
                    }
                    if (f)
                        outf << dict.find(sl)->second;
                    else
                        std::cout << dict.find(sl)->second;
                }
                catch (const char* exception)
                {
                    std::cerr << exception << '\n';
                    return 1;
                }
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