echo "compiling..."
g++ -std=c++17 timeit_manual_test.cpp timeit.cpp -o test.out
echo "compiled"

echo "running..."
echo
./test.out
echo
echo "ran..."

echo "deleting executable..."
rm test.out
echo "deleted executable"
