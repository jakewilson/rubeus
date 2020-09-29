#include <initializer_list>
#include <string>
#include <vector>

class CommandView
{
public:
    CommandView(std::initializer_list<int>);
    ~CommandView() {}

    void render();

private:
    // TODO this should be vector<RubeusCommand>
    std::vector<int> m_commands;
};
