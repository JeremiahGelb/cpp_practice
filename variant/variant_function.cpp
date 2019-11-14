#include <iostream>
#include <variant>
#include <functional>

float float_to_float(float x) 
{ 
    std::cout << "float_to_float called with: " << x << std::endl;
    return x;
}

int int_to_int(int x)
{
    std::cout << "int_to_int called with: "<< x << std::endl;
    return x;
}

void void_to_void()
{
    std::cout << "void_to_void called" << std::endl;
}

std::variant<std::monostate, float, int> 
invoke(std::variant<std::function<float(float)>, std::function<int(int)>, std::function<void(void)>> function,
       std::variant<std::monostate, float, int> arg)
{
    std::variant<std::monostate, float, int> return_value; // defaults to empty

    switch(function.index()) {
    case 0:
        // float to float
        std::cout << "in case 0 of invoke" << std::endl;
        return_value = (std::get<0>(function))(std::get<float>(arg));
        break;
    case 1:
        // int to int
        std::cout << "in case 1 of invoke" << std::endl;
        return_value = (std::get<1>(function))(std::get<int>(arg));
        break;
    case 2:
        // void to void
        std::cout << "in case 2 of invoke" << std::endl;
        (std::get<2>(function))();
        break;
    }

    return return_value;
}

void print_return_value(std::variant<std::monostate, float, int> return_value)
{
    // more elegant ways to do this on cpp reference see std::visit
    // std::visit([](auto arg){ std::cout << arg << std::endl; }, return_value); // Doesn't work with std::monostate

    switch(return_value.index()){
        case 0:
            std::cout << "return value was 'empty'" << std::endl;
            break;
        case 1:
            std::cout << "ret was a float: " << std::get<1>(return_value) << std::endl;
            break;
        case 2:
            std::cout << "ret was an int: " << std::get<2>(return_value) << std::endl;
            break;
    }
}

int main()
{
    std::function<float(float)> f1 = float_to_float;
    std::function<int(int)> f2 = int_to_int;
    std::function<void(void)> f3 = void_to_void;

    std::variant<std::monostate, float, int> return_value;
    std::variant<std::monostate, float, int> param;
    std::variant<std::function<float(float)>, std::function<int(int)>, std::function<void(void)>> function;

    std::cout << "-------------------------------------" << std::endl;
    param = float(1.23);
    return_value = invoke(f1, param);
    print_return_value(return_value);

    std::cout << "-------------------------------------" << std::endl;
    param = 1;
    return_value = invoke(f2, param);
    print_return_value(return_value);

    std::cout << "-------------------------------------" << std::endl;
    param = std::monostate{};
    return_value = invoke(f3, param);
    print_return_value(return_value);

    return EXIT_SUCCESS;
}