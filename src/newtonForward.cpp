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