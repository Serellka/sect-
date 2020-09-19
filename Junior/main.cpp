#include <iostream>
#include <fstream>
#include <map>

int main()
{
    std::map<std::string, std::string> dict;
    std::fstream inf("../data.xml", std::ifstream::in);
    std::fstream inpf("../template.txt", std::ifstream::in);
    std::fstream outf("../output.txt", std::ofstream::out);

    if (!inf && !inpf)
    {
        std::cerr << "Oh shit";
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
            if (sl == "root" || sl=="/root") continue;
            std::string str = "";
            inf >> c;
            while (c != '<')
            {
                str += c;
                inf >> c;
            }
            dict.insert(std::make_pair(sl, str));
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
                if (str[i + 1] == '*')
                {
                    i += 2;
                    std::string sl = "";
                    while (str[i] != '}')
                    {
                        sl += str[i];
                        i++;
                    }
                    outf << dict.find(sl)->second;
                }
                else
                for (; str[i] != '}'; ++i) {}
            }
            else
            {
                outf << str[i];
            }
        }
        outf << '\n';
    }
}
