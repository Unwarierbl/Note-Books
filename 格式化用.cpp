#ifdef WRITE_IN_VSCODE
#    include <iostream>
#endif

using namespace std;

#define SQUARE(x) (x * x)

int main()
{
    cout << SQUARE(2 + 3) << endl;

    cout << SQUARE(veryExpensiveFunctionCallToComputeNumber()) << endl;

    cout << ((veryExpensiveFunctionCallToComputeNumber()) *
             (veryExpensiveFunctionCallToComputeNumber()))
         << endl;

    return 0;
}