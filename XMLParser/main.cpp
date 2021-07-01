#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "pugixml.hpp"
const int CAGE_LENGTH = 20;
const char SYMBOL = '*';
int main()
{
    pugi::xml_document doc;
    if (!doc.load_file("input.xml"))
    {
        std::cout << "Error loading file input.xml!" << std::endl;
        return -1;
    }
    pugi::xml_node tools = doc.child("store");
    for (pugi::xml_node it = tools.first_child(); it; it = it.next_sibling())
    {
        std::vector<std::string> attribute_names;
        std::vector<std::vector<std::string> > attribute_info;
        for (pugi::xml_node ait = it.first_child(); ait; ait = ait.next_sibling())
        {
            int counter = 0;
            for (pugi::xml_node info = ait.first_child(); info; info = info.next_sibling())
            {
                if (ait == it.first_child())
                {
                    attribute_names.push_back(std::string(info.name()));
                    attribute_info.resize(attribute_info.size() + 1);
                }
                attribute_info[counter].push_back(std::string(info.child_value()));
                ++counter;
            }
        }
        std::cout << "name: " << it.attribute("name").value() << std::endl;
        int length = (attribute_info[0].size() + 1) * (CAGE_LENGTH + 2) + 1;
        for (int i = 0; i < attribute_info.size(); ++i)
        {
            std::cout << std::string(length, SYMBOL) << std::endl;
            std::cout << SYMBOL << ' ' << std::setw(CAGE_LENGTH) << std::left << attribute_names[i];
            for (int j = 0; j < attribute_info[i].size(); ++j)
            {
                std::cout << SYMBOL << ' ' << (i == 1? std::setw(CAGE_LENGTH) : std::setw(CAGE_LENGTH+attribute_info[i][j].size()/2)) << std::left << attribute_info[i][j];
            }
            std::cout << SYMBOL << std::endl;
        }
        std::cout << std::string(length, SYMBOL) << std::endl << std::endl;
    }
    return 0;
}
