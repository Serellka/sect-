#include <iostream>
#include <fstream>

int main()
{
    std::fstream inf("../template.txt", std::ifstream::in);
    std::fstream inpf("../data.txt", std::ifstream::in);
    std::fstream outf("../output.txt", std::ofstream::out);

    if (!inf && !inpf)
    {
        std::cerr << "Oh shit";
    }

    while (inf)
    {
        std::string str;
        getline (inf, str);
        std::cout << str << std::endl;
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] == '{')
            {
                std::string sl;
                inpf >> sl;

                if (str[i + 1] == '*')
                {
                    outf << sl;
                }
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
