#include "timeit.hpp"

#include <cassert>
// TODO: use a 

int main(){
    auto empty_lambda = []{};
    timeit(empty_lambda, "empty_lambda");

    auto counting_to_one_million = []
    {
        constexpr auto one_million = 1'000'000;
        for(auto i = 0; i < one_million; i++){
            ;
        }
    };
    timeit(counting_to_one_million, "counting_to_one_million");


    auto capture = 1;
    auto lambda_with_captures = [&capture]
    {
        capture++; 
    };
    timeit(lambda_with_captures, "lambda_with_captures");
    assert(capture == 2);


    auto time_it = [counting_to_one_million]
    {
        timeit([counting_to_one_million]{counting_to_one_million();}, "counting_to_one_million");
    };
    timeit(time_it, "timeit([counting_to_one_million]{counting_to_one_million();}, \"counting_to_one_million\")");

    return EXIT_SUCCESS;
}