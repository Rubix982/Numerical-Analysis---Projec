/*
*   NEWTON FORWARD DIFFERENCE FOMRULA 3.12
*
*   The Newton forward-difference formula, is constructed by making use of the forward
*   difference notation  introduced in Aitken’s 2 method.
*
*   INPUT: Numbers X0, X1, ... , XN ; values f(X0), f(X1), ... , f(XN)
*           as F(0,0), F(1,0), ... , F(N,0).
*
*   OUTPUT: The numbers F(0,0), F(1,0), ... ,F(N,N), where
*           Pn(X) = F(X0) + sigma(k=1,n){sCK * aitken^k~f(X0)}
*
*   F(i,i) is f[x0, x1, ... ,xi]
*
*/

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <thread>
#include <ctime>
#include <sstream>
#include <pthread.h>
#include <cmath>

//* ### TYPDEFs
typedef unsigned long long ull;
typedef long double ld;

//* ### HELPER FUNCTION
/*
*   @params void - no input required
*   @returns void - data will be stored in inputBuffer
*           which is a global variable
*/
static inline void
getInput(void);

/*
*   @params void - no input required
*   @returns void - data will be stored in inputBuffer
*           which is a global variable
*/
static inline void *
getInputFromFile(void * dummy);

/*
*   @params void - no input required
*   @returns void - data will be stored in inputBuffer
*           which is a global variable
*/
static inline void *
getInputFromUser(void * dummy);

/*
*   @params void - no input required
*   @returns void - data will be stored in inputBuffer
*           which is a global variable
*/
static inline void
calculateForwardDifferences(void);

/*
*   @params ull n - n should be greater than k
*           ull k - k should be less than n
*           Both should be positive, but it's unsigned already.
*           Large positive values may produce overflow
*   @returns ull - final result
*
*/
static inline ld
Choose(ld n, ull k);

/*
*   @params ull n - n is any positive number
*           Large positive values may produce overflow
*   @returns ull - final result
*
*/
static inline ull
factorial(ull n);

/*
*   @params void - no input required
*   @returns void - data will be stored in outputBuffer
*           which is a global variable
*/
static inline void
throwOutput(void);

/*
*   @params void - no input required
*   @returns void - data will be stored in outputBuffer
*           which is a global variable
*/
static inline void
display(void);

//* ### GLOBAL VARIABLE
/// Path for the input
std::string INPUT = "../data/newtonDifference_in.txt";

/// Path for the output
std::string OUTPUT = "../data/newtonForward_out.txt";

/// Stringstream buffer to hold the input string
std::stringstream inputBuffer;

/// Stringstream to hold the output string
std::stringstream outputBuffer;

/// number of inputs from input file
ull numOfInputs = 0;

/// Contains the divided difference formulass
ld ** F = nullptr;

/// Contains the values for which Y was calculated
ld * X = nullptr;

/// Final result forumlated as output
ld Pn_X = 0.0f;

/// Input from the user
ld X_input = 0.0f;

int main(int argc, char const *argv[])
{

    getInput();

    calculateForwardDifferences();
    // display();

    throwOutput();

    return 0;
}

static inline void
getInput(void)
{

    // Create parallel threads to handle multiprocessing
    pthread_t threadInputFromFile, threadInputFromUser;

    pthread_create(&threadInputFromFile, NULL, getInputFromFile, NULL);
    pthread_create(&threadInputFromUser, NULL, getInputFromUser, NULL);

    pthread_join(threadInputFromFile, NULL);
    pthread_join(threadInputFromUser, NULL);

    return ;
}

static inline void *
getInputFromFile(void * dummy)
{
    std::cout << "[NEWTON_FORWARD_INPUT_FILE] Taking input from respective input"
                    "file first ... \n";

    std::ifstream __Infile(INPUT);
    std::string __tempBuffer("");
    std::string __delimiter(" ");

    while ( std::getline(__Infile, __tempBuffer) )
        numOfInputs++;

    // std::cout << numOfInputs << "\n";

    F = new ld*[numOfInputs]{nullptr};
    X = new ld[numOfInputs];
    for ( ull i = 0 ; i < numOfInputs ; ++i )
        F[i] = new ld[numOfInputs]{0.0f};

    __Infile.close();
    __Infile.open(INPUT);

    // Get the datd and extract the values from them
    for ( ull x = 0, y = 0; std::getline(__Infile, __tempBuffer) ; ++x, ++y )
    {

        // # FOR X
        // Find the position of the __delimiter,
        size_t pos = __tempBuffer.find(__delimiter);

        // Extract the token
        std::string token = __tempBuffer.substr(0, pos);

        // Convert token to ld, then store in X array
        X[x] = std::stod(token);

        // Remove the token that was extracted
        __tempBuffer.erase(0, __delimiter.length() + token.length());

        // # FOR F(X)
        // Store the current string as a ld in the 1st column of F
        F[y][0] = std::stod(__tempBuffer);
    }

    __Infile.close();
    return nullptr;
}

static inline void *
getInputFromUser(void * dummy)
{

    std::cout << "[NEWTON_FORWARD_INPUT_USER] Taking input from user for "
            "the values of \'x\' ... \n";

    std::cin >> X_input;

    std::cout << "[NEWTON_FORWARD_INPUT_USER] Input from user received"
        " as " << X_input << "\n";

    return nullptr;
}

static inline void
calculateForwardDifferences(void)
{

    /// Calculate the respective values of F
    for ( ull i = 1 ; i < numOfInputs ; ++i )
        for ( ull j = 1; j <= i ; j++ )
            F[i][j] = (F[i][j-1] - F[i-1][j-1]) / (X[i] - X[i-j]);

    /*
        The equation below requires the use of's'. The book uses 's' without
        clarifying why it exists and for what intents, exactly.

        However, the below excerpt from page 126 of 'Numerical Analysis', by
        Richard L.Burden, Douglas J.Faires, Annette M.Burden, 10E, provides
        some clarification here,

        "
        Newton's divided-difference formula can be expressed in a simplified
        form when the nodes are arranged consecutively with equal spacing. In
        this case, we introduce the notation h= X(i+1) - X(i), for each
        i = 0, 1, ... , n-1 and let X = X(0) + s*h. Then the difference X - X(i)
        is X - X(i) = (s - i)*h. So, Eq(3.10) becomes

            Pn(X) = ...
        "

        Last part omitted since not needed to explain this part

        Since,
            => X = X(0) + s*h
            => X - X(0) = s*h
            => s = ( X - X(0) ) / h --------------- ( A )

        Where h is the value of the equal difference.
        It is not guranted that the result of A is always an integer, thus
        the final result will be ceiled in code

    */

    // Thus
    ld s = ( X_input - X[0] ) / ( X[1] - X[0] );
    std::cout << s << "\n";

    ld sumResult = 0.0f;
    for ( ull k = 1 ; k < numOfInputs ; ++k )
    {
        ld temp = 1.0f;
        for ( ull i = 1 ; i < k ; ++i )
            temp *= ( s - i + 1);
        temp /= factorial(k);
        sumResult += (temp * F[k][k]);
    }

    Pn_X = F[0][0] + sumResult;
}

static inline ld
Choose(ld n, ull k)
{
    if ( k == 0 or n <= 1E-1   )/* base case */
        return 1.0f;
    else                            /* recursive case */
        return Choose(n-1, k-1) +   /* take */
                Choose(n-1, k);     /* not take */
}

static inline ull
factorial(ull n)
{
    if (n <= 1) return 1;                   /* base case */
    else        return n*factorial(n-1);    /* recursive case */
}

static inline void
throwOutput(void)
{
    std::cout << "[NEWTON_FORWARD_OUTPUT] Throwing output to the  respective output"
                    " file ... ";

    std::ofstream __Outfile(OUTPUT);
    __Outfile << "Thus, Pn(X) = " << Pn_X << "\n";
    __Outfile.close();

    return ;
}

static inline void
display(void)
{
    for ( ull i = 0 ; i < numOfInputs ; ++i )
    {
        for ( ull j = 0 ; j < numOfInputs ; ++j )
            std::cout << F[i][j] << " ";
        std::cout << "\n";
    }

    std::cout << "Pn(X) := " << Pn_X << "\n";

    return ;
}