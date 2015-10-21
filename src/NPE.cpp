

#include "NPE.hpp"

NPE::NPE()
{

}

NPE::NPE(std::string fileName)
{
    tree.import_module_list(fileName);
    std::string temp = tree.get_module_names();

    if(!expression.empty())
    {
        expression.clear();
    }
    expression.push_back(temp[0]);
    for(unsigned int i = 1; i < temp.size(); ++i)
    {
        expression.push_back(temp[i]);
        expression.push_back("V");
    }
}
