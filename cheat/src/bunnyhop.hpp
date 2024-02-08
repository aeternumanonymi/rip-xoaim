// bunnyhop.hpp

#ifndef BUNNYHOP_HPP
#define BUNNYHOP_HPP

class c_bunnyhop
{
public:
    c_bunnyhop() = default;
    ~c_bunnyhop() = default;

public:
    void execute();

private:
    void send_input(bool key_down);
};

#endif